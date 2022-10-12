/**
 * @file lib/DatasetGenerator.cpp
 * @author Guilherme Inacio Goncalves <ggoncalves@iprj.uer.br>
 * @copyright Copyright 2022, Guilherme Inacio Goncalves. All rights reserved.
 *
 * This file is part of CPS (Calorimetry Pulse Simulator).
 *
 * CPS is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or any later version.
 *
 * CPS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * CPS. If not, see <https://www.gnu.org/licenses/>.
 */
#include "DatasetGenerator.h"
#include <stdlib.h>

using namespace cps;

DatasetGenerator::DatasetGenerator() :
  m_randomEngine(),
  m_pulseGenerator(nullptr),
  m_noiseMean(0),
  m_noiseStdDev(0),
  m_samplingRate(0),
  m_occupancy(0),
  m_eventsScheme()
{}

void DatasetGenerator::SetSamplingRate(double samplingRate) {
  m_samplingRate = samplingRate;
}

void DatasetGenerator::SetOccupancy(double occupancy) {
  m_occupancy = occupancy;
}

void DatasetGenerator::SetNoiseParams(double noiseMean, double noiseStdDev) {
  m_noiseMean = noiseMean;
  m_noiseStdDev = noiseStdDev;
}

void DatasetGenerator::SetPulseGenerator(const PulseGenerator* pulseGenerator) {
  m_pulseGenerator = pulseGenerator;
}

void DatasetGenerator::SetEventsScheme(std::vector<EventSchemeBlock> eventsScheme) {
  m_eventsScheme = eventsScheme;
}

const ContinuousDataset* DatasetGenerator::GenerateContinuousDataset(unsigned int nEvents) const {
  auto events = GenerateEvents(nEvents);
  return SampleEvents(events);
}

const SlicedDataset* DatasetGenerator::GenerateSlicedDataset(unsigned int nSlices, unsigned int sliceSize) const {
  const unsigned int nEvents = nSlices * sliceSize;
  auto continuousDataset = GenerateContinuousDataset(nEvents);

  std::vector<std::vector<double>> slicedTime(nSlices);
  std::vector<std::vector<double>> slicedSamples(nSlices);
  std::vector<std::vector<double>> slicedAmpltiudes(nSlices);
  std::vector<std::vector<double>> slicedPhases(nSlices);

  for (unsigned int i = 0; i < nSlices; i++) {
    std::vector<double> time(sliceSize);
    std::vector<double> samples(sliceSize);
    std::vector<double> amplitudes(sliceSize);
    std::vector<double> phases(sliceSize);
    for (unsigned int j = 0; j < sliceSize; j++) {
      time[j] = continuousDataset->time[i * sliceSize + j];
      samples[j] = continuousDataset->samples[i * sliceSize + j];
      amplitudes[j] = continuousDataset->amplitudes[i * sliceSize + j];
      phases[j] = continuousDataset->phases[i * sliceSize + j];
    }
    slicedTime[i] = time;
    slicedSamples[i] = samples;
    slicedAmpltiudes[i] = amplitudes;
    slicedPhases[i] = phases;
  }

  delete continuousDataset;
  return new SlicedDataset { slicedTime, slicedSamples, slicedAmpltiudes, slicedPhases };
}

const std::vector<AnalogPulse*> DatasetGenerator::GenerateEvents(unsigned int nEvents) const {
  std::vector<AnalogPulse*> pulses(nEvents, nullptr);

  unsigned int n = 0;
  unsigned int blockIndex = 0;
  unsigned int innerBlockIndex = 0;

  while(n < nEvents) {
    double probability = ((double) rand() / (RAND_MAX));
    bool hasSignal = probability <= m_occupancy;
    if (m_eventsScheme.size() > 0) {
      if (innerBlockIndex >= m_eventsScheme[blockIndex].m_size - 1) {
        blockIndex = (blockIndex + 1) % m_eventsScheme.size();
        innerBlockIndex = 0;
      } else {
        innerBlockIndex++;
      }
      if (m_eventsScheme[blockIndex].m_type == EventSchemeBlock::NOT_ALLOWED_EVENTS) {
        hasSignal = false;
      }
    }
    if (hasSignal) pulses[n] = m_pulseGenerator->GeneratePulse();
    n++;
  }

  return pulses;
}

const ContinuousDataset* DatasetGenerator::SampleEvents(std::vector<AnalogPulse*> pulses) const {
  unsigned int nEvents = pulses.size();

  std::vector<double> time(nEvents, 0);
  std::vector<double> samples(nEvents, m_pulseGenerator->GetPedestal());
  std::vector<double> amplitudes(nEvents, 0);
  std::vector<double> phases(nEvents, 0);

  for (unsigned int n = 0; n < nEvents; n++) {
    double currentTime = n * m_samplingRate;

    time[n] = currentTime;
    samples[n] += GenerateNoise();

    auto pulse = pulses[n];
    if (!pulse) continue;

    amplitudes[n] = pulse->GetAmplitude();
    phases[n] = pulse->GetPhase();

    double fromTime = pulse->GetPulseShape()->GetTMin();
    double toTime = pulse->GetPulseShape()->GetTMax();

    for (int t = fromTime; t <= toTime; t+=m_samplingRate) {
      int i = (t + currentTime) / m_samplingRate;
      if (i < 0) continue;
      if (i >= nEvents) break;
      samples[i] += (pulse->GetSample(t) - pulse->GetPedestal());
    }

    delete pulses[n];
  }

  pulses.clear();

  return new ContinuousDataset{
    time = time,
    samples = samples,
    amplitudes = amplitudes,
    phases = phases,
  };
}

double DatasetGenerator::GenerateNoise() const {
  if (m_noiseMean == 0 && m_noiseStdDev == 0) return 0;
  std::normal_distribution<double> distribution(m_noiseMean, m_noiseStdDev);
  return distribution(m_randomEngine);
}

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

DatasetGenerator& DatasetGenerator::SetSamplingRate(double samplingRate) {
  m_samplingRate = samplingRate;
  return *this;
}

DatasetGenerator& DatasetGenerator::SetOccupancy(double occupancy) {
  m_occupancy = occupancy;
  return *this;
}

DatasetGenerator& DatasetGenerator::SetNoiseParams(double noiseMean, double noiseStdDev) {
  m_noiseMean = noiseMean;
  m_noiseStdDev = noiseStdDev;
  return *this;
}

DatasetGenerator& DatasetGenerator::SetPulseGenerator(const PulseGenerator* pulseGenerator) {
  m_pulseGenerator = pulseGenerator;
  return *this;
}

DatasetGenerator& DatasetGenerator::SetEventsScheme(std::vector<EventSchemeBlock> eventsScheme) {
  m_eventsScheme = eventsScheme;
  return *this;
}

const ContinuousDataset* DatasetGenerator::GenerateContinuousDataset(unsigned int nEvents) const {
  auto events = GenerateEvents(nEvents);
  return SampleEvents(events);
}

const SlicedDataset* DatasetGenerator::GenerateSlicedDataset(unsigned int nSlices, unsigned int sliceSize) const {
  const unsigned int nEvents = nSlices * sliceSize;
  auto continuousDataset = GenerateContinuousDataset(nEvents);

  std::vector<std::vector<double>> slicedSamples(nSlices);
  std::vector<std::vector<double>> slicedAmpltiudes(nSlices);
  std::vector<std::vector<double>> slicedPhases(nSlices);

  for (unsigned int i = 0; i < nSlices; i++) {
    std::vector<double> samples(sliceSize);
    std::vector<double> ampltiudes(sliceSize);
    std::vector<double> phases(sliceSize);
    for (unsigned int j = 0; j < sliceSize; j++) {
      samples[j] = continuousDataset->samples[i * sliceSize + j];
      ampltiudes[j] = continuousDataset->amplitudes[i * sliceSize + j];
      phases[j] = continuousDataset->phases[i * sliceSize + j];
    }
    slicedSamples[i] = samples;
    slicedAmpltiudes[i] = ampltiudes;
    slicedPhases[i] = phases;
  }

  delete continuousDataset;
  return new SlicedDataset { slicedSamples, slicedAmpltiudes, slicedPhases };
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

  std::vector<double> samples(nEvents, m_pulseGenerator->GetPedestal());
  std::vector<double> ampltiudes(nEvents, 0);
  std::vector<double> phases(nEvents, 0);

  for (unsigned int n = 0; n < nEvents; n++) {
    samples[n] += GenerateNoise();

    auto pulse = pulses[n];
    if (!pulse) continue;

    ampltiudes[n] = pulse->GetAmplitude();
    phases[n] = pulse->GetPhase();

    double fromTime = pulse->GetPulseShape()->GetTMin();
    double toTime = pulse->GetPulseShape()->GetTMax();
    double currentTime = n * m_samplingRate;

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
    samples = samples,
    ampltiudes = ampltiudes,
    phases = phases,
  };
}

double DatasetGenerator::GenerateNoise() const {
  if (m_noiseMean == 0 && m_noiseStdDev == 0) return 0;
  std::normal_distribution<double> distribution(m_noiseMean, m_noiseStdDev);
  return distribution(m_randomEngine);
}

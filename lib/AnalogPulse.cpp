#include "AnalogPulse.h"
#include <cmath>

AnalogPulse::AnalogPulse(
    const IPulseShape* pulseShape,
    double amplitude,
    double pedestal,
    double phase,
    double deformationLevel,
    double noiseMean,
    double noiseStdDev
    ):
  m_pulseShape(pulseShape),
  m_amplitude(amplitude),
  m_pedestal(pedestal),
  m_phase(phase),
  m_deformationLevel(deformationLevel),
  m_noiseMean(noiseMean),
  m_noiseStdDev(noiseStdDev),
  m_generator()
{}

AnalogPulse::AnalogPulse(const AnalogPulse& source):
  m_pulseShape(source.m_pulseShape),
  m_amplitude(source.m_amplitude),
  m_phase(source.m_phase),
  m_pedestal(source.m_pedestal),
  m_deformationLevel(source.m_deformationLevel),
  m_noiseMean(source.m_noiseMean),
  m_noiseStdDev(source.m_noiseStdDev),
  m_generator()
{}

bool AnalogPulse::operator==(const AnalogPulse& rhs) const {
  return m_pulseShape == rhs.m_pulseShape
    && m_amplitude == rhs.m_amplitude
    && m_pedestal == rhs.m_pedestal
    && m_phase == rhs.m_phase
    && m_deformationLevel == rhs.m_deformationLevel
    && m_noiseMean == rhs.m_noiseMean
    && m_noiseStdDev == rhs.m_noiseStdDev;
}

bool AnalogPulse::operator!=(const AnalogPulse& rhs) const {
  return !(*this == rhs);
}

double AnalogPulse::operator[](unsigned int index) {
  return GetSample(index);
}

AnalogPulse::iterator::iterator(const AnalogPulse& ref):
  m_ref(&ref),
  m_index(0)
{}

AnalogPulse::iterator::iterator(const AnalogPulse& ref, unsigned int index):
  m_ref(&ref),
  m_index(index)
{}

AnalogPulse::iterator::iterator(const iterator& source):
  m_ref(source.m_ref),
  m_index(source.m_index)
{}

AnalogPulse::iterator& AnalogPulse::iterator::operator++() {
  m_index++;
  return *this;
}

AnalogPulse::iterator AnalogPulse::iterator::operator++(int) {
  iterator tmp(*this);
  ++(*this);
  return tmp;
}

bool AnalogPulse::iterator::operator==(iterator other) const {
  return m_ref == other.m_ref && m_index == other.m_index;
}

bool AnalogPulse::iterator::operator!=(iterator other) const {
  return !(*this == other);
}

const double AnalogPulse::iterator::operator*() {
  return m_ref->GetSample(m_index);
}

double AnalogPulse::GetSample(unsigned int timeIndex) const {
  int adjustedTimeIndex = GetIndexWithPhase(timeIndex);
  if (adjustedTimeIndex < 0 || adjustedTimeIndex >= m_pulseShape->GetTimeSeries().size()) {
    return 0;
  }

  double shapeSample = m_pulseShape->GetTimeSeries()[adjustedTimeIndex].second;
  double deformation = GenerateDeformation(shapeSample);
  double noise       = GenerateNoise();
  double sample      = m_amplitude * (shapeSample + deformation) + m_pedestal + noise;
  return sample;
}

int AnalogPulse::GetIndexWithPhase(unsigned int timeIndex) const {
  int phaseIndexOffset = m_phase / m_pulseShape->GetResolution();
  return timeIndex + phaseIndexOffset;
}

double AnalogPulse::GenerateDeformation(double shapeSample) const {
  if (m_deformationLevel == 0) return 0;
  double stdDev = m_deformationLevel * std::abs(shapeSample);
  std::normal_distribution<double> distribution(0, stdDev);
  return distribution(m_generator);
}

double AnalogPulse::GenerateNoise() const {
  if (m_noiseMean == 0 && m_noiseStdDev == 0) return 0;
  std::normal_distribution<double> distribution(m_noiseMean, m_noiseStdDev);
  return distribution(m_generator);
}

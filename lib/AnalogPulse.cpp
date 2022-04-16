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

double AnalogPulse::GetSample(const double& time) const {
  double timeWithPhaseDeviation = time + m_phase;
  double shapeSample            = m_pulseShape->GetY(timeWithPhaseDeviation);
  double deformation            = GenerateDeformation(shapeSample);
  double noise                  = GenerateNoise();
  return m_amplitude * (shapeSample + deformation) + m_pedestal + noise;
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

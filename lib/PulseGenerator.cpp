#include "PulseGenerator.h"

PulseGenerator::PulseGenerator(const IPulseShape* pulseShape) :
  m_generator(),
  m_pulseShape(pulseShape),
  m_nSamples(0),
  m_samplingRate(0),
  m_startSamplingAtTime(0),
  m_pedestal(0),
  m_deformationLevel(0),
  m_noiseMean(0),
  m_noiseStdDev(0),
  m_amplitudeDistribution(RandomDistribution::UNIFORM_REAL_DISTRIBUTION),
  m_amplitudeDistributionParams({0, 1023}),
  m_phaseDistribution(RandomDistribution::NO_DISTRIBUTION)
{}

AnalogPulse PulseGenerator::GeneratePulse() const {
  double amplitude = GenerateRandomNumber(m_amplitudeDistribution, m_amplitudeDistributionParams);
  double phase = GenerateRandomNumber(m_phaseDistribution, m_phaseDistributionParams);
  return GeneratePulse(amplitude, phase);
}

AnalogPulse PulseGenerator::GeneratePulse(double amplitude, double phase) const {
  return AnalogPulse(m_pulseShape, amplitude, m_pedestal, phase, m_deformationLevel, m_noiseMean, m_noiseStdDev);
}

PulseGenerator& PulseGenerator::SetNSamples(int nSamples) {
  m_nSamples = nSamples;
  return *this;
}

PulseGenerator& PulseGenerator::SetSamplingRate(double samplingRate) {
  m_samplingRate = samplingRate;
  return *this;
}

PulseGenerator& PulseGenerator::SetStartSamplingAtTime(double startSamplingAtTime) {
  m_startSamplingAtTime = startSamplingAtTime;
  return *this;
}

PulseGenerator& PulseGenerator::SetPedestal(double pedestal) {
  m_pedestal = pedestal;
  return *this;
}

PulseGenerator& PulseGenerator::SetDeformationLevel(double deformationLevel) {
  m_deformationLevel = deformationLevel;
  return *this;
}

PulseGenerator& PulseGenerator::SetNoiseParams(double noiseMean, double noiseStdDev) {
  m_noiseMean = noiseMean;
  m_noiseStdDev = noiseStdDev;
  return *this;
}

PulseGenerator& PulseGenerator::SetAmplitudeDistribution(RandomDistribution distribution, const std::vector<double> & params) {
  m_amplitudeDistribution = distribution;
  m_amplitudeDistributionParams = std::vector<double>(params);
  return *this;
}

PulseGenerator& PulseGenerator::SetPhaseDistribution(RandomDistribution distribution, const std::vector<double> & params) {
  m_phaseDistribution = distribution;
  m_phaseDistributionParams = std::vector<double>(params);
  return *this;
}

double PulseGenerator::GenerateRandomNumber(RandomDistribution distribution, const std::vector<double> & params ) const {
  switch (distribution) {
    case NORMAL_DISTRIBUTION:
      {
        std::normal_distribution<double> distribution(params[0], params[1]);
        return distribution(m_generator);
      }
    case EXPONENTIAL_DISTRIBUTION:
      {
        std::exponential_distribution<double> distribution(params[0]);
        return distribution(m_generator);
      }
    case UNIFORM_REAL_DISTRIBUTION:
      {
        std::uniform_real_distribution<double> distribution(params[0], params[1]);
        return distribution(m_generator);
      }
    case UNIFORM_INT_DISTRIBUTION:
      {
        std::uniform_int_distribution<double> distribution(params[0], params[1]);
        return distribution(m_generator);
      }
    default:
      return 0;
  }

}

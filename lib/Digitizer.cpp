#include "Digitizer.h"

using namespace cps;

Digitizer::Digitizer() :
  m_nSamples(0),
  m_samplingRate(0),
  m_startSamplingAtTime(0)
{}

Digitizer::Digitizer(unsigned int nSamples, double samplingRate, double startSamplingAtTime) :
  m_nSamples(nSamples),
  m_samplingRate(samplingRate),
  m_startSamplingAtTime(startSamplingAtTime)
{}

Digitizer& Digitizer::SetNSamples(unsigned int nSamples) {
  m_nSamples = nSamples;
  return *this;
}

Digitizer& Digitizer::SetSamplingRate(double samplingRate) {
  m_samplingRate = samplingRate;
  return *this;
}

Digitizer& Digitizer::SetStartSamplingAtTime(double startSamplingAtTime) {
  m_startSamplingAtTime = startSamplingAtTime;
  return *this;
}

std::vector<double> Digitizer::Digitize(const AnalogPulse* pulse) const {
  std::vector<double> digitalSamples;
  for (unsigned int n = 0; n < m_nSamples; n++) {
    double time = m_startSamplingAtTime + (n * m_samplingRate);
    double sample = pulse->GetSample(time);
    digitalSamples.push_back(sample);
  }
  return digitalSamples;
}

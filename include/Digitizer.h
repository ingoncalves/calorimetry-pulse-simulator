#ifndef DIGITIZER_H
#define DIGITIZER_H

#include "AnalogPulse.h"
#include <vector>

class Digitizer
{
  public:
    Digitizer();
    Digitizer(unsigned int nSamples, double samplingRate, double startSamplingAtTime = 0);
    virtual ~Digitizer() = default;

    std::vector<double> Digitize(const AnalogPulse * pulse) const;
    // getters
    unsigned int GetNSamples() const { return m_nSamples; }
    double       GetSamplingRate() const { return m_samplingRate; }
    double       GetStartSamplingAtTime() const { return m_startSamplingAtTime; }
    // setters
    Digitizer& SetNSamples(unsigned int nSamples);
    Digitizer& SetSamplingRate(double samplingRate);
    Digitizer& SetStartSamplingAtTime(double startSamplingAtTime);

  private:
    /*! Number of samples to be generated */
    unsigned int m_nSamples;
    /*! Sampling rate */
    double m_samplingRate;
    /*! Time coordinate of the pulse shape when the sampling starts */
    double m_startSamplingAtTime;
};

#endif /* DIGITIZER_H */

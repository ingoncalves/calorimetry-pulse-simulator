#ifndef DIGITIZER_H
#define DIGITIZER_H

#include "IDigitizer.h"
#include "AnalogPulse.h"
#include <vector>

namespace cps {
/**
 * @class Digitizer
 * @brief A digitizer that converts analog pulses to digital pulses.
 *
 * This class converts analog pulses to digital pulses. The digitizer has a
 * resolution (sampling rate), which is the time between samples. The digitizer
 * also has a starting time, which is the time on the signal from which
 * digitization will begin.
 */
class Digitizer : public IDigitizer
  {
  public:
    Digitizer(); //!< Constructor
    Digitizer(unsigned int nSamples, double samplingRate, double startSamplingAtTime = 0); //!< Constructor
    virtual ~Digitizer() = default; //!< Destructor

    virtual std::vector<double> Digitize(const AnalogPulse * pulse) const; //!< Digitizes the given pulse

    // getters
    unsigned int GetNSamples() const { return m_nSamples; } //!< Returns the number of samples
    double       GetSamplingRate() const { return m_samplingRate; } //!< Returns the sampling rate
    double       GetStartSamplingAtTime() const { return m_startSamplingAtTime; } //!< Returns the time at which digitization will begin
    // setters
    Digitizer& SetNSamples(unsigned int nSamples); //!< Sets the number of samples
    Digitizer& SetSamplingRate(double samplingRate); //!< Sets the sampling rate
    Digitizer& SetStartSamplingAtTime(double startSamplingAtTime); //!< Sets the time at which digitization will begin

  private:
    unsigned int m_nSamples; //!< The number of samples to be generated
    double m_samplingRate; //!< The sampling rate
    double m_startSamplingAtTime; //!< The time coordinate of the pulse shape when the sampling starts
  };
}

#endif /* DIGITIZER_H */

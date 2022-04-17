#ifndef ANALOG_PULSE_H
#define ANALOG_PULSE_H

#include "IPulseShape.h"
#include <random>
#include <iterator>

namespace cps {
class AnalogPulse
  {
  public:
    AnalogPulse(
      const IPulseShape* pulseShape = 0,
      double amplitude = 1,
      double pedestal = 0,
      double phase = 0,
      double deformationLevel = 0,
      double noiseMean = 0,
      double noiseStdDev = 0
    );
    AnalogPulse(const AnalogPulse& source);
    virtual ~AnalogPulse() = default;

    // operators
    bool operator==(const AnalogPulse& rhs) const;
    bool operator!=(const AnalogPulse& rhs) const;

    // getters
    double GetSample(const double& time) const;
    double GetAmplitude() const { return m_amplitude; }
    double GetPhase() const { return m_phase; }
    double GetPedestal() const { return m_pedestal; }
    double GetDeformationLevel() const { return m_deformationLevel; }
    double GetNoiseMean() const { return m_noiseMean; }
    double GetNoiseStdDev() const { return m_noiseStdDev; }

  private:
    /*! Pulse shape */
    const IPulseShape* m_pulseShape;
    /*! Pulse amplitude */
    double m_amplitude;
    /*! Constant value added to each sample */
    double m_pedestal;
    /*! Pulse phase */
    double m_phase;
    /*! Value between 0.0 and 1.0 that represents the amount of deformation applied to each sample  */
    double m_deformationLevel;
    /*! Normal distribution mean of the noise */
    double m_noiseMean;
    /*! Normal distribution standard deviation of the noise */
    double m_noiseStdDev;
    /*! Default random engine */
    mutable std::default_random_engine m_generator;

    double GenerateDeformation(double shapeSample) const;
    double GenerateNoise() const;
  };
}

#endif /* ANALOG_PULSE_H */

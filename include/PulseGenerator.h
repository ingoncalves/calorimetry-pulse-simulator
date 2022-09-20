#ifndef PULSE_GENERATOR_H
#define PULSE_GENERATOR_H

#include "AnalogPulse.h"
#include "IPulseShape.h"
#include <vector>
#include <random>

namespace cps {
/**
 * @class PulseGenerator
 * @brief A pulse generator that generates analog pulses.
 *
 * This class generates analog pulses. The pulse generator has a pulse shape,
 * which is the mathematical function that describes the shape of the pulse. The
 * pulse generator also uses random distributions to generate values for the
 * following pulse properties:
 *  - amplitude;
 *  - phase;
 *  - deformation;
 *  - noise.
 */
class PulseGenerator
  {
  public:
    enum RandomDistribution {
      NO_DISTRIBUTION, //!< No distribution
      NORMAL_DISTRIBUTION, //!< Normal distribution
      EXPONENTIAL_DISTRIBUTION, //!< Exponential distribution
      UNIFORM_INT_DISTRIBUTION, //!< Uniform integer distribution
      UNIFORM_REAL_DISTRIBUTION //!< Uniform real distribution
    };

    PulseGenerator(const IPulseShape* pulseShape); //!< Constructor
    virtual ~PulseGenerator() = default; //!< Destructor

    // getters
    double              GetPedestal() const { return m_pedestal; } //!< Returns the pulse pedestal
    double              GetDeformationLevel() const { return m_deformationLevel; } //!< Returns the pulse deformation level
    double              GetNoiseMean() const { return m_noiseMean; } //!< Returns the mean of the gaussian noise added to the pulse
    double              GetNoiseStdDev() const { return m_noiseStdDev; } //!< Returns the standard deviation of the gaussian noise added to the pulse
    RandomDistribution  GetAmplitudeDistribution() const { return m_amplitudeDistribution; } //!< Returns the amplitude distribution
    std::vector<double> GetAmplitudeDistributionParams() const { return m_amplitudeDistributionParams; } //!< Returns the amplitude distribution parameters
    RandomDistribution  GetPhaseDistribution() const { return m_phaseDistribution; } //!< Returns the phase distribution
    std::vector<double> GetPhaseDistributionParams() const { return m_phaseDistributionParams; } //!< Returns the phase distribution parameters
    // setters
    PulseGenerator&     SetPedestal(double pedestal); //!< Sets the pulse pedestal
    PulseGenerator&     SetDeformationLevel(double deformationLevel); //!< Sets the pulse deformation level
    PulseGenerator&     SetNoiseParams(double noiseMean, double noiseStdDev); //!< Sets the noise parameters
    PulseGenerator&     SetAmplitudeDistribution(RandomDistribution distribution, const std::vector<double> & params); //!< Sets the amplitude distribution
    PulseGenerator&     SetPhaseDistribution(RandomDistribution distribution, const std::vector<double> & params); //!< Sets the phase distribution
    AnalogPulse*        GeneratePulse() const; //!< Generates a pulse
    AnalogPulse*        GeneratePulse(double amplitude, double phase) const; //!< Generates a pulse with the given amplitude and phase

  private:
    const IPulseShape* m_pulseShape; //!< The pulse shape
    double m_pedestal; //!< The pulse pedestal, a constant value added to each sample
    double m_deformationLevel; //!< The pulse deformation level, a value between 0.0 and 1.0 that represents the amount of deformation applied to each sample
    double m_noiseMean; //!< The mean of the gaussian noise added to the pulse
    double m_noiseStdDev; //!< The standard deviation of the gaussian noise added to the pulse
    RandomDistribution m_amplitudeDistribution; //!< The amplitude distribution type
    std::vector<double> m_amplitudeDistributionParams; //!< The amplitude distribution parameters
    RandomDistribution m_phaseDistribution; //!< The phase distribution type
    std::vector<double> m_phaseDistributionParams; //!< The phase distribution parameters
    mutable std::default_random_engine m_generator; //!< The random number generator

    double GenerateRandomNumber(RandomDistribution distribution, const std::vector<double> & params) const; //!< Generates a random number according to the given distribution and parameters
  };
}

#endif /* PULSE_GENERATOR_H */

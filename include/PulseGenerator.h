#ifndef PULSE_GENERATOR_H
#define PULSE_GENERATOR_H

#include "AnalogPulse.h"
#include "IPulseShape.h"
#include <vector>
#include <random>

class PulseGenerator
{
  public:
    enum RandomDistribution {
      NO_DISTRIBUTION,
      NORMAL_DISTRIBUTION,
      EXPONENTIAL_DISTRIBUTION,
      UNIFORM_INT_DISTRIBUTION,
      UNIFORM_REAL_DISTRIBUTION
    };

    PulseGenerator(const IPulseShape* pulseShape);
    virtual ~PulseGenerator() = default;

    // getters
    int                 GetNSamples() const { return m_nSamples; }
    double              GetSamplingRate() const { return m_samplingRate; }
    double              GetStartSamplingAtTime() const { return m_startSamplingAtTime; }
    double              GetPedestal() const { return m_pedestal; }
    double              GetDeformationLevel() const { return m_deformationLevel; }
    double              GetNoiseMean() const { return m_noiseMean; }
    double              GetNoiseStdDev() const { return m_noiseStdDev; }
    RandomDistribution  GetAmplitudeDistribution() const { return m_amplitudeDistribution; }
    std::vector<double> GetAmplitudeDistributionParams() const { return m_amplitudeDistributionParams; }
    RandomDistribution  GetPhaseDistribution() const { return m_phaseDistribution; }
    std::vector<double> GetPhaseDistributionParams() const { return m_phaseDistributionParams; }
    //                  setters
    PulseGenerator&     SetNSamples(int nSamples);
    PulseGenerator&     SetSamplingRate(double samplingRate);
    PulseGenerator&     SetStartSamplingAtTime(double startSamplingAtTime);
    PulseGenerator&     SetPedestal(double pedestal);
    PulseGenerator&     SetDeformationLevel(double deformationLevel);
    PulseGenerator&     SetNoiseParams(double noiseMean, double noiseStdDev);
    PulseGenerator&     SetAmplitudeDistribution(RandomDistribution distribution, const std::vector<double> & params);
    PulseGenerator&     SetPhaseDistribution(RandomDistribution distribution, const std::vector<double> & params);
    AnalogPulse         GeneratePulse() const;
    AnalogPulse         GeneratePulse(double amplitude, double phase) const;

  private:
    /*! Pulse shape */
    const IPulseShape* m_pulseShape;
    /*! Number of samples to be generated */
    int m_nSamples;
    /*! Sampling rate */
    double m_samplingRate;
    /*! Time coordinate of the pulse shape when the sampling starts */
    double m_startSamplingAtTime;
    /*! Constant value added to each sample */
    double m_pedestal;
    /*! Value between 0.0 and 1.0 that represents the amount of deformation applied to each sample  */
    double m_deformationLevel;
    /*! Normal distribution mean of the noise */
    double m_noiseMean;
    /*! Normal distribution standard deviation of the noise */
    double m_noiseStdDev;
    /*! Noise PDF */
    RandomDistribution m_amplitudeDistribution;
    /*! Noise PDF params */
    std::vector<double> m_amplitudeDistributionParams;
    /*! Phase PDF */
    RandomDistribution m_phaseDistribution;
    /*! Phase PDF params */
    std::vector<double> m_phaseDistributionParams;
    /*! Default random engine */
    mutable std::default_random_engine m_generator;

    double GenerateRandomNumber(RandomDistribution distribution, const std::vector<double> & params) const;
};

#endif /* PULSE_GENERATOR_H */

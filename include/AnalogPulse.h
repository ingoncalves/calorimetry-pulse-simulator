/**
 * @file include/AnalogPulse.h
 * @author Guilherme Inacio Goncalves <ggoncalves@iprj.uer.br>
 * @copyright Copyright 2022, Guilherme Inacio Goncalves. All rights reserved.
 *
 * This file is part of CPS (Calorimetry Pulse Simulator).
 *
 * CPS is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or any later version.
 *
 * CPS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * CPS. If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef ANALOG_PULSE_H
#define ANALOG_PULSE_H

#include "IPulseShape.h"
#include <random>
#include <iterator>

namespace cps {
/**
 * @class AnalogPulse
 * @brief An analog pulse built from a pulse shape.
 *
 * This class builds an analog pulse from a pulse shape. A pulse has the following properties:
 * - pulse shape: a mathematical function that describes the shape of the pulse;
 * - amplitude: the height of the pulse above the baseline;
 * - phase: the time offset of the pulse from the start of the pulse series;
 * - pedestal: the pulse baseline value;
 * - deformation level: the amount of random deformation of the pulse shape;
 * - noise: the gaussian noise added to the pulse to simulate the effects of electronics.
 */
class AnalogPulse
  {
  public:
    AnalogPulse(
      const IPulseShape* pulseShape = 0, //!< The pulse shape
      double amplitude = 1, //!< The pulse amplitude
      double pedestal = 0, //!< The pulse pedestal
      double phase = 0, //!< The pulse phase
      double deformationLevel = 0, //!< The pulse deformation level between 0 and 1
      double noiseMean = 0, //!< The mean of the gaussian noise added to the pulse
      double noiseStdDev = 0 //!< The standard deviation of the gaussian noise added to the pulse
    );
    AnalogPulse(const AnalogPulse& source);
    virtual ~AnalogPulse() = default;

    // operators
    bool operator==(const AnalogPulse& rhs) const;
    bool operator!=(const AnalogPulse& rhs) const;

    // getters
    double GetSample(const double& time) const; //!< Returns the pulse amplitude at the given time
    double GetAmplitude() const { return m_amplitude; } //!< Returns the pulse amplitude
    double GetPhase() const { return m_phase; } //!< Returns the pulse phase
    double GetPedestal() const { return m_pedestal; } //!< Returns the pulse pedestal
    double GetDeformationLevel() const { return m_deformationLevel; } //!< Returns the pulse deformation level
    double GetNoiseMean() const { return m_noiseMean; } //!< Returns the mean of the gaussian noise added to the pulse
    double GetNoiseStdDev() const { return m_noiseStdDev; } //!< Returns the standard deviation of the gaussian noise added to the pulse
    const IPulseShape* GetPulseShape() const { return m_pulseShape; } //!< Returns the pulse shape

  private:
    const IPulseShape* m_pulseShape; //!< The pulse shape
    double m_amplitude; //!< The pulse amplitude
    double m_pedestal; //!< The pulse pedestal, a constant value added to each sample
    double m_phase; //!< The pulse phase, the time offset of the pulse from the start of the pulse series
    double m_deformationLevel; //!< The deformation level is a value between 0.0 and 1.0 that represents the amount of deformation applied to each sample
    double m_noiseMean; //!< The mean of the gaussian noise added to the pulse
    double m_noiseStdDev; //!< The standard deviation of the gaussian noise added to the pulse
    mutable std::default_random_engine m_generator; //!< The random number generator

    double GenerateDeformation(double shapeSample) const; //!< Generates a random deformation of the given pulse shape sample
    double GenerateNoise() const; //!< Generates a random noise sample
  };
}

#endif /* ANALOG_PULSE_H */

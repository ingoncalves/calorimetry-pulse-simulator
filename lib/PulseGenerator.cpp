/**
 * @file lib/PulseGenerator.cpp
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
#include "PulseGenerator.h"

using namespace cps;

PulseGenerator::PulseGenerator(const IPulseShape* pulseShape) :
  m_generator(),
  m_pulseShape(pulseShape),
  m_pedestal(0),
  m_deformationLevel(0),
  m_noiseMean(0),
  m_noiseStdDev(0),
  m_amplitudeDistribution(RandomDistribution::UNIFORM_REAL_DISTRIBUTION),
  m_amplitudeDistributionParams({0, 1023}),
  m_phaseDistribution(RandomDistribution::NO_DISTRIBUTION)
{}

AnalogPulse* PulseGenerator::GeneratePulse() const {
  double amplitude = GenerateRandomNumber(m_amplitudeDistribution, m_amplitudeDistributionParams);
  double phase = GenerateRandomNumber(m_phaseDistribution, m_phaseDistributionParams);
  return GeneratePulse(amplitude, phase);
}

AnalogPulse* PulseGenerator::GeneratePulse(double amplitude, double phase) const {
  return new AnalogPulse(m_pulseShape, amplitude, m_pedestal, phase, m_deformationLevel, m_noiseMean, m_noiseStdDev);
}

void PulseGenerator::SetPedestal(double pedestal) {
  m_pedestal = pedestal;
}

void PulseGenerator::SetDeformationLevel(double deformationLevel) {
  m_deformationLevel = deformationLevel;
}

void PulseGenerator::SetNoiseParams(double noiseMean, double noiseStdDev) {
  m_noiseMean = noiseMean;
  m_noiseStdDev = noiseStdDev;
}

void PulseGenerator::SetAmplitudeDistribution(RandomDistribution distribution, const std::vector<double> & params) {
  m_amplitudeDistribution = distribution;
  m_amplitudeDistributionParams = std::vector<double>(params);
}

void PulseGenerator::SetPhaseDistribution(RandomDistribution distribution, const std::vector<double> & params) {
  m_phaseDistribution = distribution;
  m_phaseDistributionParams = std::vector<double>(params);
}

double PulseGenerator::GenerateRandomNumber(RandomDistribution distribution, const std::vector<double> & params) const {
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
        std::uniform_int_distribution<long> distribution(params[0], params[1]);
        return distribution(m_generator);
      }
    default:
      return 0;
  }

}

/**
 * @file lib/Digitizer.cpp
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

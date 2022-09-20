/**
 * @file docs/examples/root/main.C
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
R__ADD_INCLUDE_PATH(/usr/local/include)
R__LOAD_LIBRARY(/usr/local/lib/libcps.dylib)

#include <iostream>
#include <cps/TextFilePulseShape.h>
#include <cps/AnalogPulse.h>
#include <cps/Digitizer.h>

using namespace cps;

// ROOT macro
int main() {
  std::cout << "Calo Pulse Simulator - Example ROOT Macro" << std::endl;

  const char* SHAPE_PATH = "../../../tests/fixtures/unipolar-pulse-shape.dat";

  const TextFilePulseShape* pulseShape = new TextFilePulseShape(SHAPE_PATH);

  double amplitude = 1022.9;
  double pedestal = 15.3;
  double phase = 0.5;
  double deformationLevel = 0.2;
  double noiseMean = 0.01;
  double noiseStdDev = 0.1;

  AnalogPulse* analogPulse = new AnalogPulse(
    pulseShape,
    amplitude,
    pedestal,
    phase,
    deformationLevel,
    noiseMean,
    noiseStdDev
  );

  Digitizer digitizer(7, 25, -75);
  std::vector<double> digitalSamples = digitizer.Digitize(analogPulse);
  for (int i = 0; i < digitalSamples.size(); i++) {
    std::cout << digitalSamples[i] << std::endl;
  }

  return 0;
}

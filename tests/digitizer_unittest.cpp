/**
 * @file tests/digitizer_unittest.cpp
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
#include <gtest/gtest.h>
#include <vector>
#include "TextFilePulseShape.h"
#include "AnalogPulse.h"
#include "Digitizer.h"

#ifndef PULSE_SHAPE_FILE_PATH
#define PULSE_SHAPE_FILE_PATH "tests/fixtures/unipolar-pulse-shape.dat"
#endif

using namespace cps;

TEST(Digitizer, NSamples) {
  Digitizer digitizer;
  // default value
  EXPECT_EQ(digitizer.GetNSamples(), 0);
  // new value
  unsigned int nSamples = 7;
  EXPECT_EQ(digitizer.SetNSamples(nSamples).GetNSamples(), nSamples);
}

TEST(Digitizer, SamplingRate) {
  Digitizer digitizer;
  // default value
  EXPECT_EQ(digitizer.GetSamplingRate(), 0.0);
  // new value
  double samplingRate = 25.0;
  EXPECT_EQ(digitizer.SetSamplingRate(samplingRate).GetSamplingRate(), samplingRate);
}

TEST(Digitizer, StartSamplingAtTime) {
  Digitizer digitizer;
  // default value
  EXPECT_EQ(digitizer.GetStartSamplingAtTime(), 0.0);
  // new value
  double startSampligAtTime = -25.0;
  EXPECT_EQ(digitizer.SetStartSamplingAtTime(startSampligAtTime).GetStartSamplingAtTime(), startSampligAtTime);
}

TEST(Digitizer, Digitize) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  AnalogPulse* analogPulse = new AnalogPulse(pulseShape);

  unsigned int nSamples = 7;
  double samplingRate = 25.0;
  double startSampligAtTime = -75.0;
  Digitizer digitizer(nSamples, samplingRate, startSampligAtTime);

  std::vector<double> digitalSamples = digitizer.Digitize(analogPulse);
  EXPECT_EQ(digitalSamples.size(), nSamples);

  double expectedSamplesTime[] = {-75.0, -50.0, -25.0, 0.0, 25.0, 50.0, 75.0};
  for (int i = 0; i < nSamples; i++) {
    EXPECT_EQ(digitalSamples[i], analogPulse->GetSample(expectedSamplesTime[i]));
  }
}

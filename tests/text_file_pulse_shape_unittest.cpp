/**
 * @file tests/text_file_pulse_shape_unittest.cpp
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
#include "TextFilePulseShape.h"

using namespace cps;

const char * PULSE_SHAPE_FILE_PATH = "tests/fixtures/unipolar-pulse-shape.dat";

TEST(TextFilePulseShapeTest, GetResolution) {
  TextFilePulseShape pulseShape(PULSE_SHAPE_FILE_PATH);
  EXPECT_EQ(pulseShape.GetResolution(), 0.5);
}

TEST(TextFilePulseShapeTest, GetSize) {
  TextFilePulseShape pulseShape(PULSE_SHAPE_FILE_PATH);
  EXPECT_EQ(pulseShape.GetSize(), 401);
}

TEST(TextFilePulseShapeTest, GetTimeSeries) {
  TextFilePulseShape pulseShape(PULSE_SHAPE_FILE_PATH);
  std::vector<double> timeSeries = pulseShape.GetTimeSeries();
  EXPECT_EQ(timeSeries.size(), 401);
  EXPECT_EQ(timeSeries[0], -75.5);
  EXPECT_EQ(timeSeries[400], 124.5);
}

TEST(TextFilePulseShapeTest, GetYSeries) {
  TextFilePulseShape pulseShape(PULSE_SHAPE_FILE_PATH);
  std::vector<double> ySeries = pulseShape.GetYSeries();
  EXPECT_EQ(ySeries.size(), 401);
  EXPECT_EQ(ySeries[0], 0.0);
  EXPECT_NEAR(ySeries[400], 0.0018547, 1.0e-7);
}

TEST(TextFilePulseShapeTest, GetTMin) {
  TextFilePulseShape pulseShape(PULSE_SHAPE_FILE_PATH);
  EXPECT_EQ(pulseShape.GetTMin(), -75.5);
}

TEST(TextFilePulseShapeTest, GetTMax) {
  TextFilePulseShape pulseShape(PULSE_SHAPE_FILE_PATH);
  EXPECT_EQ(pulseShape.GetTMax(), 124.5);
}

TEST(TextFilePulseShapeTest, GetY) {
  TextFilePulseShape pulseShape(PULSE_SHAPE_FILE_PATH);
  EXPECT_EQ(  pulseShape.GetY(-75.5),   0.0);
  EXPECT_EQ(  pulseShape.GetY(0),       1.0);
  EXPECT_NEAR(pulseShape.GetY(124.5), 0.0018547, 1.0e-7);

  // edge cases
  EXPECT_EQ(  pulseShape.GetY(-200), 0.0);
  EXPECT_NEAR(pulseShape.GetY(200), 0.0018547, 1.0e-7);
}

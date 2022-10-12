/**
 * @file tests/dataset_generator_unittest.cpp
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
#include "PulseGenerator.h"
#include "DatasetGenerator.h"

#ifndef PULSE_SHAPE_FILE_PATH
#define PULSE_SHAPE_FILE_PATH "tests/fixtures/unipolar-pulse-shape.dat"
#endif

using namespace cps;

TEST(DatasetGenerator, PulseGenerator) {
  DatasetGenerator datasetGenerator;
  // default value
  EXPECT_EQ(datasetGenerator.GetPulseGenerator(), nullptr);
  // new value
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  const PulseGenerator* pulseGenerator = new PulseGenerator(pulseShape);
  EXPECT_EQ(datasetGenerator.SetPulseGenerator(pulseGenerator).GetPulseGenerator(), pulseGenerator);
}

TEST(DatasetGenerator, NoiseParams) {
  DatasetGenerator datasetGenerator;
  // default value
  EXPECT_EQ(datasetGenerator.GetNoiseMean(), 0);
  EXPECT_EQ(datasetGenerator.GetNoiseStdDev(), 0);
  // new value
  double noiseMean = 1.0;
  double noiseStdDev = 3.5;
  datasetGenerator.SetNoiseParams(noiseMean, noiseStdDev);
  EXPECT_EQ(datasetGenerator.GetNoiseMean(), noiseMean);
  EXPECT_EQ(datasetGenerator.GetNoiseStdDev(), noiseStdDev);
}

TEST(DatasetGenerator, SamplingRate) {
  DatasetGenerator datasetGenerator;
  // default value
  EXPECT_EQ(datasetGenerator.GetSamplingRate(), 0.0);
  // new value
  double samplingRate = 25.0;
  EXPECT_EQ(datasetGenerator.SetSamplingRate(samplingRate).GetSamplingRate(), samplingRate);
}

TEST(DatasetGenerator, Occupancy) {
  DatasetGenerator datasetGenerator;
  // default value
  EXPECT_EQ(datasetGenerator.GetOccupancy(), 0.0);
  // new value
  double occupancy = 0.5;
  EXPECT_EQ(datasetGenerator.SetOccupancy(occupancy).GetOccupancy(), occupancy);
}

TEST(DatasetGenerator, GenerateContinuousDataset) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  const PulseGenerator* pulseGenerator = new PulseGenerator(pulseShape);
  DatasetGenerator datasetGenerator = DatasetGenerator()
    .SetSamplingRate(25.0)
    .SetOccupancy(0.05)
    .SetNoiseParams(0, 0)
    .SetPulseGenerator(pulseGenerator);

  unsigned int nEvents = 100;
  auto dataset = datasetGenerator.GenerateContinuousDataset(nEvents);
  EXPECT_EQ(dataset->time.size(), nEvents);
  EXPECT_EQ(dataset->samples.size(), nEvents);
  EXPECT_EQ(dataset->amplitudes.size(), nEvents);
  EXPECT_EQ(dataset->phases.size(), nEvents);
}

TEST(DatasetGenerator, EventScheme) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  const PulseGenerator* pulseGenerator = new PulseGenerator(pulseShape);
  DatasetGenerator datasetGenerator = DatasetGenerator()
    .SetSamplingRate(25.0)
    .SetOccupancy(1.0)
    .SetNoiseParams(0, 0)
    .SetPulseGenerator(pulseGenerator)
    .SetEventsScheme({ DatasetGenerator::AllowedEventsBlock(5), DatasetGenerator::NotAllowedEventsBlock(25) });

  unsigned int nEvents = 100;
  auto dataset = datasetGenerator.GenerateContinuousDataset(nEvents);
  EXPECT_EQ(dataset->time.size(), nEvents);
  EXPECT_EQ(dataset->samples.size(), nEvents);
  EXPECT_EQ(dataset->amplitudes.size(), nEvents);
  EXPECT_EQ(dataset->phases.size(), nEvents);

  for (int i = 0; i < nEvents; i++) {
    std::cout << dataset->samples[i] << "\t" << dataset->amplitudes[i] << std::endl;
  }
}

TEST(DatasetGenerator, GenerateSlicedDataset) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  const PulseGenerator* pulseGenerator = new PulseGenerator(pulseShape);
  DatasetGenerator datasetGenerator = DatasetGenerator()
    .SetSamplingRate(25.0)
    .SetOccupancy(0.05)
    .SetNoiseParams(0, 0)
    .SetPulseGenerator(pulseGenerator);

  unsigned int nSlices = 100;
  unsigned int sliceSize = 7;
  auto dataset = datasetGenerator.GenerateSlicedDataset(nSlices, sliceSize);
  EXPECT_EQ(dataset->time.size(), nSlices);
  EXPECT_EQ(dataset->time[0].size(), sliceSize);
  EXPECT_EQ(dataset->samples.size(), nSlices);
  EXPECT_EQ(dataset->samples[0].size(), sliceSize);
  EXPECT_EQ(dataset->amplitudes.size(), nSlices);
  EXPECT_EQ(dataset->amplitudes[0].size(), sliceSize);
  EXPECT_EQ(dataset->phases.size(), nSlices);
  EXPECT_EQ(dataset->phases[0].size(), sliceSize);
}

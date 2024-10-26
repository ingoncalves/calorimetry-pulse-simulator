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
#include <iomanip>
#include <gtest/gtest.h>
#include "TextFilePulseShape.h"
#include "PulseGenerator.h"
#include "DatasetGenerator.h"

#ifndef PULSE_SHAPE_FILE_PATH
#define PULSE_SHAPE_FILE_PATH "tests/fixtures/unipolar-pulse-shape.dat"
#endif

using namespace cps;

void PrintDataset(const ContinuousDataset* dataset) {
  std::cout <<
    std::setw(15) << "time" <<
    std::setw(15) << "sample" <<
    std::setw(15) << "amplitude" <<
    std::setw(15) << "phase" <<
    std::setw(15) << "noise" << std::endl;

  for (int i = 0; i < dataset->time.size(); i++) {
    std::cout <<
      std::setw(15) << dataset->time[i] <<
      std::setw(15) << dataset->samples[i] <<
      std::setw(15) << dataset->amplitudes[i] <<
      std::setw(15) << dataset->phases[i] <<
      std::setw(15) << dataset->noise[i] << std::endl;
  }
}

TEST(DatasetGenerator, PulseGenerator) {
  DatasetGenerator datasetGenerator;
  // default value
  EXPECT_EQ(datasetGenerator.GetPulseGenerator(), nullptr);
  // new value
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  const PulseGenerator* pulseGenerator = new PulseGenerator(pulseShape);
  datasetGenerator.SetPulseGenerator(pulseGenerator);
  EXPECT_EQ(datasetGenerator.GetPulseGenerator(), pulseGenerator);
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
  datasetGenerator.SetSamplingRate(samplingRate);
  EXPECT_EQ(datasetGenerator.GetSamplingRate(), samplingRate);
}

TEST(DatasetGenerator, Occupancy) {
  DatasetGenerator datasetGenerator;
  // default value
  EXPECT_EQ(datasetGenerator.GetOccupancy(), 0.0);
  // new value
  double occupancy = 0.5;
  datasetGenerator.SetOccupancy(occupancy);
  EXPECT_EQ(datasetGenerator.GetOccupancy(), occupancy);
}

TEST(DatasetGenerator, GenerateContinuousDataset) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  const PulseGenerator* pulseGenerator = new PulseGenerator(pulseShape);
  DatasetGenerator datasetGenerator = DatasetGenerator();
  datasetGenerator.SetSamplingRate(25.0);
  datasetGenerator.SetOccupancy(0.05);
  datasetGenerator.SetNoiseParams(0, 0.5);
  datasetGenerator.SetPulseGenerator(pulseGenerator);

  unsigned int nEvents = 100;
  auto dataset = datasetGenerator.GenerateContinuousDataset(nEvents);
  EXPECT_EQ(dataset->time.size(), nEvents);
  EXPECT_EQ(dataset->samples.size(), nEvents);
  EXPECT_EQ(dataset->amplitudes.size(), nEvents);
  EXPECT_EQ(dataset->phases.size(), nEvents);
  EXPECT_EQ(dataset->noise.size(), nEvents);

  PrintDataset(dataset);
}

TEST(DatasetGenerator, EventScheme) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  const PulseGenerator* pulseGenerator = new PulseGenerator(pulseShape);
  DatasetGenerator datasetGenerator = DatasetGenerator();
  datasetGenerator.SetSamplingRate(25.0);
  datasetGenerator.SetOccupancy(1.0);
  datasetGenerator.SetNoiseParams(0, 0.5);
  datasetGenerator.SetPulseGenerator(pulseGenerator);
  datasetGenerator.SetEventsScheme({ DatasetGenerator::AllowedEventsBlock(5), DatasetGenerator::NotAllowedEventsBlock(25) });

  unsigned int nEvents = 100;
  auto dataset = datasetGenerator.GenerateContinuousDataset(nEvents);
  EXPECT_EQ(dataset->time.size(), nEvents);
  EXPECT_EQ(dataset->samples.size(), nEvents);
  EXPECT_EQ(dataset->amplitudes.size(), nEvents);
  EXPECT_EQ(dataset->phases.size(), nEvents);
  EXPECT_EQ(dataset->noise.size(), nEvents);

  PrintDataset(dataset);
}

TEST(DatasetGenerator, GenerateSlicedDataset) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  const PulseGenerator* pulseGenerator = new PulseGenerator(pulseShape);
  DatasetGenerator datasetGenerator = DatasetGenerator();
  datasetGenerator.SetSamplingRate(25.0);
  datasetGenerator.SetOccupancy(0.05);
  datasetGenerator.SetNoiseParams(0, 0);
  datasetGenerator.SetPulseGenerator(pulseGenerator);

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
  EXPECT_EQ(dataset->noise.size(), nSlices);
  EXPECT_EQ(dataset->noise[0].size(), sliceSize);
}

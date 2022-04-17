#include <gtest/gtest.h>
#include "TextFilePulseShape.h"
#include "PulseGenerator.h"

#ifndef PULSE_SHAPE_FILE_PATH
#define PULSE_SHAPE_FILE_PATH "tests/fixtures/unipolar-pulse-shape.dat"
#endif

using namespace cps;

const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);

TEST(PulseGenerator, Pedestal) {
  PulseGenerator pulseGenerator(pulseShape);
  // default value
  EXPECT_EQ(pulseGenerator.GetPedestal(), 0.0);
  // new value
  double pedestal = 50;
  EXPECT_EQ(pulseGenerator.SetPedestal(pedestal).GetPedestal(), pedestal);
}

TEST(PulseGenerator, DeformationLevel) {
  PulseGenerator pulseGenerator(pulseShape);
  // default value
  EXPECT_EQ(pulseGenerator.GetDeformationLevel(), 0.0);
  // new value
  double deformationLevel = 0.1;
  EXPECT_EQ(pulseGenerator.SetDeformationLevel(deformationLevel).GetDeformationLevel(), deformationLevel);
}

TEST(PulseGenerator, NoiseParams) {
  PulseGenerator pulseGenerator(pulseShape);
  // default value
  EXPECT_EQ(pulseGenerator.GetNoiseMean(), 0);
  EXPECT_EQ(pulseGenerator.GetNoiseStdDev(), 0);
  // new value
  double noiseMean = 1.0;
  double noiseStdDev = 3.5;
  pulseGenerator.SetNoiseParams(noiseMean, noiseStdDev);
  EXPECT_EQ(pulseGenerator.GetNoiseMean(), noiseMean);
  EXPECT_EQ(pulseGenerator.GetNoiseStdDev(), noiseStdDev);
}

TEST(PulseGenerator, AmplitudeDistribution) {
  PulseGenerator pulseGenerator(pulseShape);
  // default value
  EXPECT_EQ(pulseGenerator.GetAmplitudeDistribution(), PulseGenerator::UNIFORM_REAL_DISTRIBUTION);
  EXPECT_EQ(pulseGenerator.GetAmplitudeDistributionParams(), std::vector<double>({0, 1023}));
  // new value
  auto distribution = PulseGenerator::UNIFORM_INT_DISTRIBUTION;
  auto params = std::vector<double>{80, 90};
  pulseGenerator.SetAmplitudeDistribution(distribution, params);
  EXPECT_EQ(pulseGenerator.GetAmplitudeDistribution(), distribution);
  EXPECT_EQ(pulseGenerator.GetAmplitudeDistributionParams(), params);
}

TEST(PulseGenerator, PhaseDistribution) {
  PulseGenerator pulseGenerator(pulseShape);
  // default value
  EXPECT_EQ(pulseGenerator.GetPhaseDistribution(), PulseGenerator::NO_DISTRIBUTION);
  // new value
  auto distribution = PulseGenerator::UNIFORM_INT_DISTRIBUTION;
  auto params = std::vector<double>{-4, 4};
  pulseGenerator.SetPhaseDistribution(distribution, params);
  EXPECT_EQ(pulseGenerator.GetPhaseDistribution(), distribution);
  EXPECT_EQ(pulseGenerator.GetPhaseDistributionParams(), params);
}

TEST(PulseGenerator, GeneratePulse) {
  PulseGenerator pulseGenerator = PulseGenerator(pulseShape)
    .SetAmplitudeDistribution(PulseGenerator::UNIFORM_INT_DISTRIBUTION, {80, 90})
    .SetPhaseDistribution(PulseGenerator::UNIFORM_INT_DISTRIBUTION, {-4, 4});

  AnalogPulse* analogPulse;

  // deterministic values
  double deterministicAmplitude = 500;
  double deterministicPhase = 1.0;
  analogPulse = pulseGenerator.GeneratePulse(500, 1.0);
  EXPECT_EQ(analogPulse->GetSample(-1.0), deterministicAmplitude);

  // random values
  analogPulse = pulseGenerator.GeneratePulse();
  EXPECT_GE(analogPulse->GetAmplitude(), 80);
  EXPECT_LE(analogPulse->GetAmplitude(), 90);
  EXPECT_GE(analogPulse->GetPhase(), -4);
  EXPECT_LE(analogPulse->GetPhase(), 4);
}

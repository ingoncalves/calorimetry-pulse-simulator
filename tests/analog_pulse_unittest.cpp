#include <gtest/gtest.h>
#include "TextFilePulseShape.h"
#include "AnalogPulse.h"

#ifndef PULSE_SHAPE_FILE_PATH
#define PULSE_SHAPE_FILE_PATH "tests/fixtures/unipolar-pulse-shape.dat"
#endif

using namespace cps;

TEST(AnalogPulse, Construction) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);

  double amplitude = 1022.9;
  double pedestal = 15.3;
  double phase = 0.5;
  double deformationLevel = 0.2;
  double noiseMean = 0.01;
  double noiseStdDev = 0.1;

  AnalogPulse analogPulse(
      pulseShape,
      amplitude,
      pedestal,
      phase,
      deformationLevel,
      noiseMean,
      noiseStdDev
      );

  EXPECT_EQ(analogPulse.GetAmplitude(), amplitude);
  EXPECT_EQ(analogPulse.GetPhase(), phase);
  EXPECT_EQ(analogPulse.GetNoiseMean(), noiseMean);
  EXPECT_EQ(analogPulse.GetNoiseStdDev(), noiseStdDev);
  EXPECT_EQ(analogPulse.GetPedestal(), pedestal);
  EXPECT_EQ(analogPulse.GetDeformationLevel(), deformationLevel);
  EXPECT_EQ(analogPulse.GetPulseShape(), pulseShape);
}

TEST(AnalogPulse, GetSample) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  AnalogPulse analogPulse(pulseShape);
  EXPECT_EQ(analogPulse.GetSample(0), pulseShape->GetY(0));
}

TEST(AnalogPulse, Amplitude) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  double amplitude = 1023.0;
  AnalogPulse analogPulse(pulseShape, amplitude);
  EXPECT_EQ(analogPulse.GetSample(0), amplitude * pulseShape->GetY(0));
}

TEST(AnalogPulse, Pedestal) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  double pedestal = 50;
  AnalogPulse analogPulse(pulseShape, 1, pedestal);
  EXPECT_EQ(analogPulse.GetSample(-75.5), pedestal + pulseShape->GetY(-75.5));
}

TEST(AnalogPulse, Phase) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  AnalogPulse analogPulse;

  double positivePhase = 1.0;
  analogPulse = AnalogPulse(pulseShape, 1, 0, positivePhase);
  EXPECT_EQ(analogPulse.GetSample(0), pulseShape->GetY(1.0));

  double negativePhase = -1.0;
  analogPulse = AnalogPulse(pulseShape, 1, 0, negativePhase);
  EXPECT_EQ(analogPulse.GetSample(0), pulseShape->GetY(-1.0));
}

TEST(AnalogPulse, DeformationLevel) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  AnalogPulse analogPulse;
  double deformationLevel;

  deformationLevel = 0.0;
  analogPulse = AnalogPulse(pulseShape, 1, 0, 0, deformationLevel);
  EXPECT_EQ(analogPulse.GetSample(0), pulseShape->GetY(0));

  deformationLevel = 0.5;
  analogPulse = AnalogPulse(pulseShape, 1, 0, 0, deformationLevel);
  EXPECT_NE(analogPulse.GetSample(0), pulseShape->GetY(0));
  double tolerance = deformationLevel * pulseShape->GetYSeries()[151];
  EXPECT_NEAR(analogPulse.GetSample(0), pulseShape->GetY(0), 4 * tolerance);
}

TEST(AnalogPulse, Noise) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  AnalogPulse analogPulse;
  double noiseMean, noiseStdDev;

  noiseMean = 0.0;
  noiseStdDev = 0.0;
  analogPulse = AnalogPulse (pulseShape, 1, 0, 0, 0, noiseMean, noiseStdDev);
  EXPECT_EQ(analogPulse.GetSample(0), pulseShape->GetY(0));

  noiseMean = 10.0;
  noiseStdDev = 0.0;
  analogPulse = AnalogPulse(pulseShape, 1, 0, 0, 0, noiseMean, noiseStdDev);
  EXPECT_EQ(analogPulse.GetSample(0), noiseMean + pulseShape->GetY(0));

  noiseMean = 10.0;
  noiseStdDev = 1.0;
  analogPulse = AnalogPulse(pulseShape, 1, 0, 0, 0, noiseMean, noiseStdDev);
  EXPECT_NEAR(analogPulse.GetSample(0), noiseMean + pulseShape->GetY(0), 4 * noiseStdDev);
}

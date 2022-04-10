#include <gtest/gtest.h>
#include "TextFilePulseShape.h"
#include "AnalogPulse.h"

#ifndef PULSE_SHAPE_FILE_PATH
#define PULSE_SHAPE_FILE_PATH "tests/fixtures/unipolar-pulse-shape.dat"
#endif

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
}

TEST(AnalogPulse, Amplitude) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  double amplitude = 1023.0;
  AnalogPulse analogPulse(pulseShape, amplitude);
  EXPECT_EQ(analogPulse[151], amplitude * pulseShape->GetTimeSeries()[151].second);
}

TEST(AnalogPulse, Pedestal) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  double pedestal = 50;
  AnalogPulse analogPulse(pulseShape, 1, pedestal);
  EXPECT_EQ(analogPulse[0], pedestal + pulseShape->GetTimeSeries()[0].second);
}

TEST(AnalogPulse, Phase) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  AnalogPulse analogPulse;

  double positivePhase = 1.0;
  analogPulse = AnalogPulse(pulseShape, 1, 0, positivePhase);
  EXPECT_EQ(analogPulse[151], pulseShape->GetTimeSeries()[153].second);

  double negativePhase = -1.0;
  analogPulse = AnalogPulse(pulseShape, 1, 0, negativePhase);
  EXPECT_EQ(analogPulse[151], pulseShape->GetTimeSeries()[149].second);
}

TEST(AnalogPulse, DeformationLevel) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  double deformationLevel;

  deformationLevel = 0.0;
  AnalogPulse analogPulse1(pulseShape, 1, 0, 0, deformationLevel);
  EXPECT_EQ(analogPulse1[151], pulseShape->GetTimeSeries()[151].second);

  deformationLevel = 0.5;
  AnalogPulse analogPulse2(pulseShape, 1, 0, 0, deformationLevel);
  EXPECT_NE(analogPulse2[151], pulseShape->GetTimeSeries()[151].second);
  double tolerance = deformationLevel * pulseShape->GetTimeSeries()[151].second;
  EXPECT_NEAR(analogPulse2[151], pulseShape->GetTimeSeries()[151].second, 4 * tolerance);
}

TEST(AnalogPulse, Noise) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  double noiseMean, noiseStdDev;

  noiseMean = 0.0;
  noiseStdDev = 0.0;
  AnalogPulse analogPulse1(pulseShape, 1, 0, 0, 0, noiseMean, noiseStdDev);
  EXPECT_EQ(analogPulse1[151], pulseShape->GetTimeSeries()[151].second);

  noiseMean = 10.0;
  noiseStdDev = 0.0;
  AnalogPulse analogPulse2(pulseShape, 1, 0, 0, 0, noiseMean, noiseStdDev);
  EXPECT_EQ(analogPulse2[151], noiseMean + pulseShape->GetTimeSeries()[151].second);

  noiseMean = 10.0;
  noiseStdDev = 1.0;
  AnalogPulse analogPulse3(pulseShape, 1, 0, 0, 0, noiseMean, noiseStdDev);
  EXPECT_NEAR(analogPulse3[151], noiseMean + pulseShape->GetTimeSeries()[151].second, 4 * noiseStdDev);
}

TEST(AnalogPulse, Iterator) {
  const TextFilePulseShape* pulseShape = new TextFilePulseShape(PULSE_SHAPE_FILE_PATH);
  double amplitude = 1023.0;
  AnalogPulse analogPulse(pulseShape, amplitude);
  AnalogPulse::iterator it;

  it = analogPulse.begin();
  EXPECT_EQ(*it, amplitude * pulseShape->GetTimeSeries()[0].second);

  // incremental
  ++it;
  EXPECT_EQ(*it, amplitude * pulseShape->GetTimeSeries()[1].second);

  // end
  it = analogPulse.end();
  EXPECT_EQ(*it, amplitude * pulseShape->GetTimeSeries()[pulseShape->GetSize()-1].second);
}

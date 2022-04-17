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

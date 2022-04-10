#include <gtest/gtest.h>
#include "TextFilePulseShape.h"

const char * PULSE_SHAPE_FILE_PATH = "tests/fixtures/unipolar-pulse-shape.dat";

TEST(TextFilePulseShapeTest, GetResolution) {
  TextFilePulseShape pulseShape(PULSE_SHAPE_FILE_PATH);
  EXPECT_EQ(pulseShape.GetResolution(), 0.5);
}

TEST(TextFilePulseShapeTest, GetOrigin) {
  TextFilePulseShape pulseShape(PULSE_SHAPE_FILE_PATH);
  EXPECT_EQ(pulseShape.GetOrigin(), 151);
}

TEST(TextFilePulseShapeTest, GetSize) {
  TextFilePulseShape pulseShape(PULSE_SHAPE_FILE_PATH);
  EXPECT_EQ(pulseShape.GetSize(), 401);
}

TEST(TextFilePulseShapeTest, GetTimeSeries) {
  TextFilePulseShape pulseShape(PULSE_SHAPE_FILE_PATH);
  std::vector<std::pair<float,float>> timeSeries = pulseShape.GetTimeSeries();

  EXPECT_EQ(timeSeries.size(), 401);

  EXPECT_EQ(timeSeries[0].first, -75.5);
  EXPECT_EQ(timeSeries[0].second, 0.0);

  EXPECT_EQ(timeSeries[400].first, 124.5);
  EXPECT_NEAR(timeSeries[400].second, 0.0018547, 1.0e-7);
}

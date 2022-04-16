#include <gtest/gtest.h>
#include "TextFilePulseShape.h"

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

TEST(TextFilePulseShapeTest, GetY) {
  TextFilePulseShape pulseShape(PULSE_SHAPE_FILE_PATH);
  EXPECT_EQ(  pulseShape.GetY(-75.5),   0.0);
  EXPECT_EQ(  pulseShape.GetY(0),       1.0);
  EXPECT_NEAR(pulseShape.GetY(124.5), 0.0018547, 1.0e-7);

  // edge cases
  EXPECT_EQ(  pulseShape.GetY(-200), 0.0);
  EXPECT_NEAR(pulseShape.GetY(200), 0.0018547, 1.0e-7);
}

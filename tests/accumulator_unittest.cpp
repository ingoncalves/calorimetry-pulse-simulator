#include <gtest/gtest.h>
#include "algorithms/Accumulator.h"

using namespace cps;

TEST(AccumulatorTest, firstNumber) {
  Accumulator a;
  EXPECT_EQ(a.getNextValue(), 0);
}

TEST(AccumulatorTest, secondNumber) {
  Accumulator a;
  a.getNextValue();
  EXPECT_EQ(a.getNextValue(), 1);
}

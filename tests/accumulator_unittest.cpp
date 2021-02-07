#include <gtest/gtest.h>
#include "algorithms/Accumulator.h"

TEST(AccumulatorTest, firstNumber) {
  Accumulator a;
  EXPECT_EQ(a.getNextValue(), 0);
}

TEST(AccumulatorTest, secondNumber) {
  Accumulator a;
  a.getNextValue();
  EXPECT_EQ(a.getNextValue(), 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

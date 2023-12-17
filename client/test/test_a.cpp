#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}


// The keyinput must be detected with an sample rate of 4ms
// The following test must validate that a key input will be detected withing
// a 4ms (+threshold) frame



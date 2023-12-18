#include <gtest/gtest.h>

#include <circular_buffer.hpp>

TEST(SharedSuite, CircularBufferDoesNotGrowAboveMaxSizeTest) {

    CircularBuffer<int> circular_buffer(3);

    circular_buffer.push(0);
    circular_buffer.push(1);
    circular_buffer.push(2);
    circular_buffer.push(3);
    circular_buffer.push(4);
    
    EXPECT_EQ(circular_buffer.size(), 3);
}

TEST(SharedSuite, CircularBufferThrowAwayTheRightContentIfGrowAboveMaxSizeTest) {

    CircularBuffer<int> circular_buffer(3);

    circular_buffer.push(0);
    circular_buffer.push(1);
    circular_buffer.push(2);
    circular_buffer.push(3);
    circular_buffer.push(4);
    
    EXPECT_EQ(circular_buffer.front(), 2);
    EXPECT_EQ(circular_buffer.back(), 4);
}

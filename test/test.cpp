#include <gtest/gtest.h>

TEST(TestCase, TestName){
    ASSERT_EQ(0, 1) << "Test Failed";
}
#include <gtest/gtest.h>

// 测试宏：TEST(测试套件名, 测试用例名)
TEST(HelloTest, BasicAssertions) {
    // EXPECT_* 系列断言失败时，测试会继续执行
    EXPECT_STRNE("hello", "world");
    // ASSERT_* 系列断言失败时，测试会立即停止
    ASSERT_EQ(7 * 6, 42);
}
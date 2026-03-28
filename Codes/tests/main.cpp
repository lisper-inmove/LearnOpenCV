#include <gtest/gtest.h>
#include <ch04.h>

// 测试宏：TEST(测试套件名, 测试用例名)
TEST(OpenCVTest, Mean)
{
    ch04::cvMeanTest();
}

TEST(OpenCVTest, meanStdDev)
{
    ch04::cvMeanStdDevTest();
}

TEST(OpenCVTest, cvCalcHistTest)
{
    ch04::cvCalcHistTest();
}

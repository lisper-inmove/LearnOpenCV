#include "pch.h"
#include "tester.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

/**
 * 第七章: 二值分析
 *
 * 常用二值化方法如下:
 *  1. 基于全局阈值得到的二值图像 threshold
 *  2. 基于自适应得到的二值图像 adaptiveThreshold
 *  3. 基于边缘检测得到的二值图像 Canny
 *  4. 基于像素值范围得到的二值图像 inRange
 * */

namespace cvtest::tester {
TEST_F(Tester, BinaryTest) {}

} // namespace cvtest::tester

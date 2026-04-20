#include "pch.h"
#include "tester.h"
#include "gtest/gtest.h"
#include <array>
#include <cstdlib>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <sys/wait.h>

/**
 * 第四章: 卷积操作
 * */

namespace cvtest::tester {
TEST_F(Tester, ThresholdTest) {
  /**
   * 阈值化分割
   * double cv::threshold(
   *  InputArray src,
   *  OutputArray dst,
   *  double thresh,
   *  double maxval,
   *  int type
   * )
   * 1. src, dst: 输入与输出，支持 CV_8U, CV_32F
   * 2. thresh: 阈值
   * 3. maxval: 最大值，CV_8U时为255，CV_32F时为1.0
   * 4. type: opencv支持5种阈值化方法
   *  4.1 THRESH_BINARY: 二值化
   *      将阈值T与每个像素值进行比较，大于阈值的赋为maxval，其余赋值为0
   *  4.2 THRESH_BINARY_INV: 二值化反
   *      将阈值T与每个像素值进行比较，大于阈值的赋为0，其余赋值为maxval
   *  4.3 THRESH_TRUNC: 阈值截断
   *      将阈值T与每个像素值进行比较，大于阈值的赋为T，其余赋值为0
   *  4.4 THRESH_TOZERO: 阈值取0
   *      将阈值T与每个像素值进行比较，将不大于阈值的赋为0
   *  4.5 THRESH_TOZERO_INV: 阈值取0反
   *      将阈值T与每个像素值进行比较，将大于阈值的赋为0
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat binary, gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);
  cv::imshow("Source Image", image);
  cv::imshow("Gray Image", gray);
  cv::imshow("Binary", binary);
  cv::waitKey(30000);
  cv::destroyAllWindows();
}

TEST_F(Tester, OTSUMethod) {
  /**
   * 全局阈值计算: 大津法
   * 基于图像的灰度直方图，通过计算最小类内方差来寻找阈值T
   * */
}

TEST_F(Tester, TriangleMethod) {
  /**
   * 全局阈值计算: 三角法
   * */
}

} // namespace cvtest::tester

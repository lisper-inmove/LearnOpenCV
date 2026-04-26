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
   * 适用于双峰直方图的图像
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat binary, gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  // THRESH_OTSU 表示用大津法来获取阈值
  cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
  cv::imshow("Source Image", image);
  cv::imshow("Gray Image", gray);
  cv::imshow("Binary", binary);
  cv::waitKey(30000);
  cv::destroyAllWindows();
}

TEST_F(Tester, TriangleMethod) {
  /**
   * 全局阈值计算: 三角法
   * 适用于有单峰直方图的图像
   * 如果大波峰在较暗的一侧，需要翻转直方图，然后用255减去翻转之后求得的值
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat binary, gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  // THRESH_TRIANGLE 表示用三角法来获取阈值
  cv::threshold(gray, binary, 127, 255,
                cv::THRESH_BINARY | cv::THRESH_TRIANGLE);
  cv::imshow("Source Image", image);
  cv::imshow("Gray Image", gray);
  cv::imshow("Binary", binary);
  cv::waitKey(30000);
  cv::destroyAllWindows();
}

TEST_F(Tester, AdaptiveThresholdTest) {
  /**
   * 自适应阈值计算
   * 分为均值自适应与高斯自适应
   *
   * 全局自适应对光照一致的图像有很好的二值化效果，但是当光照不一致时，全局阈值会破坏图像原有的信息
   * 自适应阈值并不会真正产生一个局部阈值，而是先对输入的图像进行模糊处理，然后使用原图减去模糊图像得到一个差值图像，
   * 再使用常量阈值C来与每个差值进行比较，大于-C的则赋值为白色，否则为0
   *
   * void cv;:adaptiveThreshold(
   *  InputArray src,
   *  OUtputArray dst,
   *  double maxValue,
   *  int adaptiveMethod,
   *  int thresholdType,
   *  int blockSize,
   *  double C
   * )
   * maxValue 满足条件时前景图像的灰度值，通常为255
   * adaptiveMethod: ADAPTIVE_THRESH_MEAN_C, ADAPTIVE_THRESH_GAUSSIAN_C
   * thresholdType: ThresholdTest里提到的5种方式
   * blockSize: 卷积核的大小
   * C: 局部阈值。
   *  第一步是做模糊处理，然后用原图减去模糊之后的图像，得到的值与C做对比
   *  如果src > blur - C，赋值为 maxValue的值
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat binary, gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  cv::adaptiveThreshold(gray, binary, 200, cv::ADAPTIVE_THRESH_MEAN_C,
                        cv::THRESH_BINARY, 5, 10);
  cv::imshow("Source Image", image);
  cv::imshow("Gray Image", gray);
  cv::imshow("Binary", binary);
  cv::waitKey(30000);
  cv::destroyAllWindows();
}

TEST_F(Tester, InRangeBinary) {
  /**
   * 用inRange函数实现二值化。检查每个像素是否落在上下边界区间内，并将结果输出为二值图像
   * 如果图像是多通道的，每个通道条件必须同时满足
   * void cv::inRange(
   *   InputArray src,  // 输入图像
   *   InputArray loweb, // 下边界
   *   InputArray upperb, // 上边界
   *   OutputArray dst
   * )
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat hsv, mask;
  cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
  inRange(hsv, cv::Scalar(20, 43, 46), cv::Scalar(23, 255, 255), mask);
  cv::Mat result;
  cv::bitwise_and(image, image, result, mask);
  imshow("Source", image);
  imshow("Mask", mask);
  cv::imshow("Region extract", result);
  cv::waitKey(30000);
  cv::destroyAllWindows();
}

} // namespace cvtest::tester

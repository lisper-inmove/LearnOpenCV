#include "pch.h"
#include "tester.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace cvtest::tester {
TEST_F(Tester, BinaryTest) {
  /**
   * 二值图
   * double cv::threshold(
   *  InputArray src,
   *  OutputArray dst,
   *  double thresh,
   *  double maxval,
   *  int type
   * )
   * */
  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
  cv::Mat binary;

  // 大津法和三角法都是基于直方图数据全局计算阈值的方法
  // THRESH_OTSU 表示大津法
  // THRESH_TRIANGLE 表示三角法
  cv::threshold(image, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
  // cv::threshold(image, binary, 120, 200, cv::THRESH_BINARY);
  cv::imshow("Source", image);
  cv::imshow("Binary", binary);
  cv::waitKey();
  cv::destroyAllWindows();
}

TEST_F(Tester, AdaptiveBinaryTest) {
  /**
   * 自适应阈值计算
   * void cv::adaptiveThreshold(
   *  InputArray src,
   *  OutputArray dst,
   *  double maxValue,
   *  int adaptiveMethod,
   *  int thresholdType,
   *  int blockSize,
   *  double c
   * )
   * */
  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  cv::cvtColor(image, image, cv::COLOR_RGBA2GRAY);
  cv::Mat binaryMean, binaryGaussian;
  cv::adaptiveThreshold(image, binaryMean, 255, cv::ADAPTIVE_THRESH_MEAN_C,
                        cv::THRESH_BINARY, 25, 10);
  cv::adaptiveThreshold(image, binaryGaussian, 255,
                        cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 25,
                        10);
  cv::imshow("Source", image);
  cv::imshow("Mean Binary", binaryMean);
  cv::imshow("Gaussian Binary", binaryGaussian);
  cv::waitKey();
  cv::destroyAllWindows();
}

} // namespace cvtest::tester

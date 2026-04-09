#include "pch.h"
#include "tester.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

/**
 * 第三章: 图像直方图
 * */

namespace cvtest::tester {
TEST_F(Tester, HistMeanTest) {
  /**
   * 均值与方差
   * Scalar cv::mean(
   *  InputArray src,
   *  Inputarray mask = noArray()
   * )
   *
   * void cv::meanStdDev(
   *  InputArray src,
   *  OutputArray mean,
   *  OutputArray stddev,
   *  InputArray mask = noArray()
   * )
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Scalar mean = cv::mean(image);
  std::cout << "Mean " << mean << "\n";

  cv::Mat mat1, mat2;
  cv::meanStdDev(image, mat1, mat2);
  std::cout << "Mean " << mat1 << "\n";
  std::cout << "Std " << mat2 << "\n";
}
} // namespace cvtest::tester

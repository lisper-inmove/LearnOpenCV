#include "pch.h"
#include "tester.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace cvtest::tester {
TEST_F(Tester, BlurTest) {

  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);

  {
    /**
     * 均值模糊
     * void cv::blur(
     *  InputArray src,
     *  OutputArray dst,
     *  Size ksize,
     *  Point anchor = Point(-1, -1),
     *  int boardType = BORDER_DEFAULT
     * )
     * */
    cv::Mat result7x7 = cv::Mat::ones(7, 7, CV_8UC1);
    cv::Mat result15x15 = cv::Mat::ones(15, 15, CV_8UC1);
    std::cout << result7x7 << std::endl;
    cv::blur(image, result7x7, cv::Size(7, 7));
    cv::blur(image, result15x15, cv::Size(15, 15));

    cv::namedWindow("OpenCV Window", cv::WINDOW_AUTOSIZE);
    cv::imshow("OpenCV Window", image);
    cv::imshow("Result 7x7", result7x7);
    cv::imshow("Result 15x15", result15x15);
    cv::waitKey(0);
    cv::destroyAllWindows();
  }
}

TEST_F(Tester, GaussianBlurTest) {

  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  {
    /**
     * 高斯模糊
     * void cv::GaussianBlur(
     *  InputArray src,
     *  OutputArray dst,
     *  Size ksize, // 必须设置为奇数
     *  double sigmaX,
     *  double sigma Y = 0,
     *  int borderType = BORDER_DEFAULT
     * )
     * ksize 不为 Size(0, 0)时，根据ksize计算sigmaX
     * 当 ksize为Size(0, 0)时，根据sigmaX计算ksize
     * */
    cv::Mat result_size10;
    cv::Mat result_sigma15;
    cv::GaussianBlur(image, result_size10, cv::Size(11, 11), 0, 0);
    cv::GaussianBlur(image, result_sigma15, cv::Size(0, 0), 15, 0);
    cv::imshow("Gaussian-10x10", result_size10);
    cv::imshow("Gaussian-sigma15", result_sigma15);
    cv::waitKey(0);
    cv::destroyAllWindows();
  }
}

TEST_F(Tester, MedianBlurTest) {

  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  {
    /**
     * 中值模糊
     *  void cv::medianBlur(
     *    InputArray src,
     *    OutputArray dst,
     *    int ksize // 必须是大于1的奇数
     *  )
     * */
    cv::Mat result;
    cv::medianBlur(image, result, 21);
    cv::imshow("Median Blur", result);
    cv::waitKey();
    cv::destroyAllWindows();
  }
}

TEST_F(Tester, Filter2DTest) {

  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  {
    /**
     * 自定义滤波
     * void cv::filter2D(
     *  InputArray src,
     *  OutputArray dst,
     *  int ddepth,
     *  InputArray kernel,
     *  Point anchor = Point(-1, -1),
     *  double delta = 0,
     *  int borderType = BORDER_DEFAULT
     * )
     * */
    cv::Mat result;
    cv::Mat kernel = cv::Mat::ones(cv::Size(25, 25), CV_32FC1);
    kernel = kernel / (25 * 25);
    cv::filter2D(image, result, -1, kernel);
    cv::imshow("Filter2D", result);
    cv::waitKey();
    cv::destroyAllWindows();
  }
}

TEST_F(Tester, HorizontalBlurTest) { /* 水平垂直模糊*/

  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  // 垂直模糊
  cv::Mat k = cv::Mat::ones(cv::Size(1, 25), CV_32FC1);
  k = k / (25 * 1);
  cv::Mat result;
  cv::filter2D(image, result, -1, k);
  cv::imshow("Horizotnal Blur", result);
  cv::waitKey();
  cv::destroyAllWindows();
}

TEST_F(Tester, VerticalBlurTest) { /* 水平垂直模糊*/

  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  // 水平模糊
  cv::Mat k = cv::Mat::ones(cv::Size(25, 1), CV_32FC1);
  k = k / (25 * 1);
  cv::Mat result;
  cv::filter2D(image, result, -1, k);
  cv::imshow("Vertical Blur", result);
  cv::waitKey();
  cv::destroyAllWindows();
}

TEST_F(Tester, DiognalTest) { /* 对角线模糊*/

  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  cv::Mat k = cv::Mat::eye(cv::Size(25, 25), CV_32FC1);
  k = k / (25);
  cv::Mat result;
  cv::filter2D(image, result, -1, k, cv::Point(-1, -1), 0, 4);
  cv::imshow("Diognal Blur", result);
  cv::waitKey();
  cv::destroyAllWindows();
}
} // namespace cvtest::tester

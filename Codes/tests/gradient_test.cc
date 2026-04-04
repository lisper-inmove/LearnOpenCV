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
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

namespace cvtest::tester {
TEST_F(Tester, GradientTest) {
  /**
   * a0, a1, a2
   * a7, M,  a3
   * a6, a5, a4
   *
   * M_x = (a2 + ca3 + a4) - (a0 + ca7 + a6)
   * M_y = (a6 + ca5 + a4) - (a0 + ca1 + a2)
   *
   * 当c = 1时，Prewitt算子，OpenCV没有提供Prewitt算子，用filter2D模拟
   *   M_x = -1 0 1     M_y = -1 -1 -1
   *         -1 0 1            0  0  0
   *         -1 0 1           -1 -1 -1
   * 当c = 2时，Sobel算子
   *   M_x = -1 0 1     M_y = -1 -2 -1
   *         -2 0 2            0  0  0
   *         -1 0 1            1  2  1
   * 基于Sobel的增强卷积核, Scharr算子
   *   M_x = -3  0 3     M_y = -3 -10 -3
   *         -10 0 10           0   0  0
   *         -3  0 3            3  10  3
   * */
}

TEST_F(Tester, SobelTest) {
  /**
   * void cv::Sobel(
   *  InputArray src,
   *  OutputArray dst,
   *  int ddepth,
   *  int dx,           // dx, dy 1表示1阶，2表示2阶
   *  int dy,
   *  int ksize = 3,    // 奇数
   *  double scale = 1,
   *  double delta = 0,
   *  int borderType = BORDER_TYPE
   * )
   * */
  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  cv::Mat gradx, grady;
  cv::Sobel(image, gradx, CV_32F, 1, 0);
  cv::Sobel(image, grady, CV_32F, 0, 1);
  cv::imshow("OpenCV Window", image);
  cv::imshow("gradx", gradx);
  cv::imshow("grady", grady);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

TEST_F(Tester, ScharrTest) {
  /**
   * void cv::Scharr(
   *  InputArray src,
   *  OutputArray dst,
   *  int ddepth,
   *  int dx,           // dx, dy 1表示1阶，2表示2阶
   *  int dy,
   *  int ksize = 3,    // 奇数
   *  double scale = 1,
   *  double delta = 0,
   *  int borderType = BORDER_TYPE
   * )
   * */
  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  cv::Mat gradx, grady;
  cv::Scharr(image, gradx, CV_32F, 1, 0);
  cv::Scharr(image, grady, CV_32F, 0, 1);
  cv::imshow("OpenCV Window", image);
  cv::imshow("gradx", gradx);
  cv::imshow("grady", grady);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

TEST_F(Tester, LaplacianTest) {
  /** 拉普拉斯算子
   * kernel = 0 -1 0
   *         -1 4 -1
   *          0 -1 0
   * 8_kernel = -1 -1 -1   从四领域扩展到八领域
   *            -1  8 -1
   *            -1 -1 -1
   * void cv::Laplacian(
   *  InputArray src,
   *  OutputArray dst,
   *  int ddepth,
   *  int ksize = 1,  // 必须是正奇数
   *  double scale = 1,
   *  double delta = 0,
   *  int borderType = BORDER_DEFAULT
   * )
   *
   * 图像锐化，使用卷积核 0 -1 0   可以看作是  0 0 0    0 -1  0
   *                      -1 5 -1              0 1 0 + -1  4 -1
   *                      0 -1 0               0 0 0    0 -1  0
   * */

  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  cv::Mat lap_img, sharpen_img;
  cv::Laplacian(image, lap_img, CV_32F, 3, 1.0, 0.0, 4);
  cv::normalize(lap_img, lap_img, 0, 1.0, cv::NORM_MINMAX);

  cv::Mat k = (cv::Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
  cv::filter2D(image, sharpen_img, -1, k, cv::Point(-1, -1), 0, 4);
  cv::imshow("Source", image);
  imshow("Laplacian", lap_img);
  imshow("Sharpen", sharpen_img);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

TEST_F(Tester, CalculateSharpen) {
  /** 计算图像锐度
   * */

  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  cv::Mat sharpen_img;

  cv::Mat k = (cv::Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
  cv::filter2D(image, sharpen_img, -1, k, cv::Point(-1, -1), 0, 4);

  int sum1 = sharpenValue(image);
  int sum2 = sharpenValue(sharpen_img);

  std::string text1 = std::to_string(sum1);
  std::string text2 = std::to_string(sum2);

  cv::Point org(50, 80);
  int fontFace = cv::FONT_HERSHEY_SIMPLEX;
  double fontScale = 1.0;
  cv::Scalar color(0, 255, 0);
  int thickness = 2;
  int lineType = cv::LINE_8;

  cv::putText(image, text1, org, fontFace, fontScale, color, thickness,
              lineType);
  cv::putText(sharpen_img, text2, org, fontFace, fontScale, color, thickness,
              lineType);

  imshow("Source", image);
  imshow("Sharpen", sharpen_img);
  cv::waitKey(0);
  cv::destroyAllWindows();
}
} // namespace cvtest::tester

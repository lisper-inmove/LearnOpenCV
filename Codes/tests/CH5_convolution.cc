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
TEST_F(Tester, BlurTest) {
  /**
   *  均值模糊: 求和，再求均值
   *  void cv::blur(
   *    InputArray src,
   *    OutputArray dst,
   *    Size ksize,
   *    // 锚点，(-1, -1)表示中心
   *    Point anchor = Point(-1, -1),
   *    int borderType = BORDER_DEFAULT
   *  )
   *  borderType: 以下是用一维举例例子，假设锚点为中心，
   *              ksize为5，也就是 [1 1 C 1 1]
   *  BORDER_CONSTANT: 用常量值填充 ii|abcdefgh|ii
   *                   (当锚点在a时，a的左侧会填充一些常量值)
   *  BORDER_REPLICATE: 边界复制 aa|abcdefgh|hh
   *  BORDER_REFLECT: 边界反射 ba|abcdefgh|hg
   *  BORDER_WRAP(OpenCV4已不再支持): 边界换行，尾接头，头接尾 hg|abcdefgh|ab
   *  BORDER_REFLECT_101: cb|abcdefgh|gf 默认值
   *  BORDER_TRANSPARENT(OpenCV4已不再支持):
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);
  cv::Mat blur7x7, blur15x15;
  cv::blur(gray, blur7x7, cv::Size(7, 7));
  cv::blur(gray, blur15x15, cv::Size(15, 15));
  cv::imshow("Source", image);
  cv::imshow("Gray", gray);
  cv::imshow("Blur 7x7", blur7x7);
  cv::imshow("Blur 15x15", blur15x15);
  cv::waitKey(10000);
  cv::destroyAllWindows();
}

TEST_F(Tester, GaussianBlurTest) {
  /**
   * 高斯模糊: 均值模糊没有考虑像素点之间的空间位置关系
   * void cv::GaussianBlur(
   *  InputArray src,
   *  OutputArray dst,
   *  Size ksize,
   *  double sigmaX, // 水平方向的标准差
   *  double sigmaY = 0, // 垂直方向的标准差
   *  int borderType = BORDER_DEFAULT
   * )
   * 当ksize不为0时，根据ksize计算
   * 当ksize为0时，根据sigmaX计算 ksize
   * sigmaX = 0.3 * ((Size - 1) * 0.5 - 1) + 0.8
   * sigmaY默认为0，表示与sigmaX相同
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat gray, resultSize11, resultSigma15;
  cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);
  cv::GaussianBlur(image, resultSize11, cv::Size(11, 11), 0);
  cv::GaussianBlur(image, resultSigma15, cv::Size(0, 0), 15);
  cv::imshow("Source", image);
  cv::imshow("Gray", gray);
  cv::imshow("Blur Size 11x11", resultSize11);
  cv::imshow("Blur sigmaX 15", resultSigma15);
  cv::waitKey(10000);
  cv::destroyAllWindows();
}

TEST_F(Tester, MedianBlurTest) {
  /**
   * 均值模糊: 根据卷积核，对窗口中的所有像素值排序，取中值作为锚点值
   * void cv::medianBlur(
   *   InputArray src,
   *   OutputArray dst,
   *   int ksize  // 必须是大于1的奇数
   * )
   *
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat gray, result;
  cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);
  cv::medianBlur(gray, result, 11);
  cv::imshow("Source", image);
  cv::imshow("Gray", gray);
  cv::imshow("Median Blur", result);
  cv::waitKey(10000);
  cv::destroyAllWindows();
}

TEST_F(Tester, Filter2DTest) {
  /**
   * 自定义滤波
   * void cv::medianBlur(
   *  InputArray src,
   *  OutputArray dst,
   *  int ddepth,
   *  InputArray kernel,
   *  Point anchor = Point(-1, -1),
   *  double delta = 0,
   *  int borderType = BORDER_DEFAULT
   * )
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat gray, result;
  cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);
  cv::Mat kl = cv::Mat::ones(cv::Size(25, 25), CV_32FC1);
  kl = kl / (25 * 25);
  cv::filter2D(gray, result, -1, kl);
  cv::imshow("Source", image);
  cv::imshow("Gray", gray);
  cv::imshow("Filter2D", result);
  cv::waitKey(10000);
  cv::destroyAllWindows();
}

TEST_F(Tester, VerticalBlurTest) {
  /**
   * 垂直模糊，用 cv::Mat::ones(Size(25, 1))调用filter2D
   * */
}

TEST_F(Tester, HorizontalBlurTest) {
  /**
   * 水平模糊，用 cv::Mat::ones(Size(1, 25))调用filter2D
   * */
}

TEST_F(Tester, DiagonalBlurTest) {
  /**
   * 对角线模糊，用 cv::Mat::eye(Size(1, 25))调用filter2D
   * */
}

TEST_F(Tester, GradientTest) {
  /**
   * 梯度提取
   * 假设有如下的卷积核
   * a0, a1, a2
   * a7, M,  a3
   * a6, a5, a4
   *
   * M_x = (a2 + c*a3 + a4) - (a0 + c*a7 + a6)
   * M_y = (a6 + c*a5 + a4) - (a0 + c*a1 + a2)
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

TEST_F(Tester, PrewittTest) {
  /**
   * Prewitt 算子
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  cv::Mat prewittX = (cv::Mat_<float>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
  cv::Mat prewittY = (cv::Mat_<float>(3, 3) << -1, -1, -1, 0, 0, 0, 1, 1, 1);
  cv::Mat gradX, gradY;
  // 计算不同的卷积
  cv::filter2D(image, gradX, CV_32F, prewittX);
  cv::filter2D(image, gradY, CV_32F, prewittY);

  // 计算梯度幅值
  cv::Mat magnitude;
  cv::magnitude(gradX, gradY, magnitude); // 欧几里得距离sqrt(x^2 + y^2)
  // cv::Mat magnitude = abs(gradX) + abs(gradY) // 绝对近似

  // 归一化到[0, 255]
  cv::Mat result;
  cv::normalize(magnitude, result, 0, 255, cv::NORM_MINMAX, CV_8U);

  // 生成二值边缘
  cv::Mat binary;
  double thresh = 50;
  cv::threshold(result, binary, thresh, 255, cv::THRESH_BINARY);

  cv::imshow("Soruce Image", image);
  cv::imshow("Gray Image", gray);
  cv::imshow("Prewitt X", gradX);
  cv::imshow("Prewitt Y", gradY);
  cv::imshow("Result", result);
  cv::imshow("Binary", result);
  cv::waitKey(10000);
  cv::destroyAllWindows();
}

TEST_F(Tester, SobelTest) {
  /**
   * Sobel算子
   * void cv::Sobel(
   *   InputArray src,
   *   OutputArray dst
   *   int ddepth, // 输出图像的深度
   *   int dx, // x方向的阶数
   *   int dy, // y方向的阶数
   *   int ksize = 3,
   *   double scale = 1,
   *   double delta = 0,
   *   int borderType = BORDER_DEFAULT
   * )
   * */
  cv::Mat image = cv::imread(filepath_);

  cv::Mat gray;
  cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  cv::Mat blurred;
  cv::GaussianBlur(gray, blurred, cv::Size(3, 3), 0);

  cv::Mat gradX, gradY;
  cv::Mat absGradX, absGradY;

  int ddepth = CV_16S;
  int ksize = 3;

  cv::Sobel(blurred, gradX, ddepth, 1, 0, ksize);
  cv::Sobel(blurred, gradY, ddepth, 0, 1, ksize);

  cv::convertScaleAbs(gradX, absGradX);
  cv::convertScaleAbs(gradY, absGradY);

  cv::Mat grad;
  cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, grad);

  cv::imshow("Source Image", image);
  cv::imshow("Gray Image", gray);
  cv::imshow("X Grad", absGradX);
  cv::imshow("Y Grad", absGradY);
  cv::imshow("Sobel Result", grad);
  cv::waitKey(15000);
  cv::destroyAllWindows();
}

TEST_F(Tester, SobelBookTest) {
  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  cv::Mat gradx, grady;
  cv::Sobel(image, gradx, CV_32F, 1, 0);
  cv::Sobel(image, grady, CV_32F, 0, 1);
  cv::normalize(gradx, gradx, 0, 1.0, cv::NORM_MINMAX);
  cv::normalize(grady, grady, 0, 1.0, cv::NORM_MINMAX);
  cv::imshow("OpenCV Window", image);
  cv::imshow("gradx", gradx);
  cv::imshow("grady", grady);
  cv::waitKey(0);
  cv::destroyAllWindows();

  // cv::Mat image = cv::imread(filepath_);

  // cv::Mat gray;
  // cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  // cv::Mat gradX, gradY;

  // int ksize = 3;

  // cv::Sobel(image, gradX, -1, 1, 0, ksize);
  // cv::Sobel(image, gradY, -1, 0, 1, ksize);

  // cv::normalize(gradX, gradX, 0, 1.0, cv::NORM_MINMAX);
  // cv::normalize(gradY, gradY, 0, 1.0, cv::NORM_MINMAX);

  // cv::imshow("Source Image", image);
  // cv::imshow("Gray Image", gray);
  // cv::imshow("X Grad", gradX);
  // cv::imshow("Y Grad", gradY);
  // cv::waitKey(15000);
  // cv::destroyAllWindows();
}

TEST_F(Tester, ScharrTest) {
  /**
   * Sobel算子
   * void cv::Scharr(
   *   InputArray src,
   *   OutputArray dst
   *   int ddepth, // 输出图像的深度
   *   int dx, // x方向的阶数
   *   int dy, // y方向的阶数
   *   int ksize = 3,
   *   double scale = 1,
   *   double delta = 0,
   *   int borderType = BORDER_DEFAULT
   * )
   * */
  cv::Mat image = cv::imread(filepath_);

  cv::Mat gray;
  cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  cv::Mat blurred;
  cv::GaussianBlur(gray, blurred, cv::Size(3, 3), 0);

  cv::Mat gradX, gradY;
  cv::Mat absGradX, absGradY;

  int ddepth = CV_16S;
  int ksize = 3;

  cv::Scharr(blurred, gradX, ddepth, 1, 0, ksize);
  cv::Scharr(blurred, gradY, ddepth, 0, 1, ksize);

  cv::convertScaleAbs(gradX, absGradX);
  cv::convertScaleAbs(gradY, absGradY);

  cv::Mat grad;
  cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, grad);

  cv::imshow("Source Image", image);
  cv::imshow("Gray Image", gray);
  cv::imshow("X Grad", absGradX);
  cv::imshow("Y Grad", absGradY);
  cv::imshow("Sobel Result", grad);
  cv::waitKey(15000);
  cv::destroyAllWindows();
}

TEST_F(Tester, MarginDetectTest) {
  /**
   * 边缘发现
   * 基于梯度图像进一步处理之后就值得到边缘图像，该过程称为边缘发现
   *
   * 梯度幅值(L2): G = sqrt(G_x ^ 2 + G_y ^ 2)
   *     G_x, G_y就是前面的 gradX和gradY
   *     theta(x, y) = arctan(G_y(x, y) / G_x(x, y))
   *
   * 1. 非最大抑制:
   * 如果当前像素点的梯度值小于两侧像素梯度值，就将当前像素点的值设置为0
   *             否则，保留
   *
   * 2. 双阈值连接
   *   1. 设定两个阈值
   *   你需要定义高低两个阈值：maxVal（高阈值）和 minVal（低阈值）。
   *   强边缘像素：任何梯度值 > maxVal 的点，被认定为 “确定边缘”，会被立刻保留。
   *   弱边缘像素：梯度值介于 minVal 和 maxVal 之间的点，被标记为
   *               “待定边缘”，暂不判决。
   *   非边缘像素：梯度值 < minVal 的点，被直接丢弃。
   *
   *   2. 执行滞后连接
   *   这是算法的关键，它基于一个朴素的观察：真正的边缘通常是连续的。
   *   算法以所有 “确定边缘” 像素为起点，沿着边缘的方向进行追踪。
   *   在追踪过程中，如果一个 “待定边缘”
   *   像素恰好位于某个“确定边缘”像素的路径上（即它们是连通的），那么这个“待定边缘”像素就被“拯救”了，升级为最终边缘的一部分。
   *   反之，那些孤立存在、没有连接到任何“确定边缘”的“待定边缘”像素，则被认为是噪声或无关细节，最终被丢弃。
   *
   * void cv::Canny(
   *   InputArray image,
   *   OutputArray edges,
   *   double threshold1, // L
   *   double threshold2, // H
   *   int aperturSize = 3, // 计算梯度时，sobel卷积核大小
   *   bool L2gradient = false // 默认使用L1计算， M = |G_x| + |G_y|
   * )
   *
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat gray, edges;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  int lowThreshold = 50;
  int highThreshold = 100;
  cv::Canny(gray, edges, lowThreshold, highThreshold);
  cv::imshow("Source Image", image);
  cv::imshow("Gray", gray);
  cv::imshow("Edges", edges);
  cv::waitKey(30000);
  cv::destroyAllWindows();
}

TEST_F(Tester, RemoveJYNoise) {
  /**
   * 去除椒盐噪声
   */
  cv::Mat image = cv::imread(jyNoisePath_, cv::IMREAD_COLOR);
  cv::Mat median_denoise, mean_denoise;
  // 中值模糊去噪
  medianBlur(image, median_denoise, 5);
  // 均值模糊去噪
  blur(image, mean_denoise, cv::Size(5, 5));
  cv::imshow("Source", image);
  cv::imshow("median denoise", median_denoise);
  cv::imshow("mean denoise", mean_denoise);
  cv::waitKey(15000);
  cv::destroyAllWindows();
}

TEST_F(Tester, GaussianBilateralFilter) {
  /**
   * 边缘保留滤波（高斯双边滤波函数）: 基于两个高斯核生成权重，完成图像滤波
   *      其中一个为空间权重，另一个是值域权重
   *      空间权重只考虑了 x, y 两个维度
   *      值域权重则考虑了 r, g, b 的影响
   * void cv::bilateralfilter(
   *  InputArray src,
   *  OutputArray dst,
   *  int d, // 滤波过程中像素邻域直径
   *  // 如果邻居像素的颜色值与中心像素的颜色值相差 < sigmaColor
   *       这个邻居被认为是相似的，它会获得较高的权重，对最终结果有较大影响。
   *  double sigmaColor, // 颜色差异
   *  //
   * 坐标空间上的标准差。值越大，表示距离更远的像素也会参与计算，模糊范围越大。
   *  double sigmaSpace, // d为0时有效,表示中心位置差异,越远权重越低
   *  int borderType = BORDER_DEFAULT
   * )
   * */
  cv::Mat image = cv::imread(gsNoisePath_, cv::IMREAD_COLOR);
  cv::Mat denoise, cartoon;
  cv::bilateralFilter(image, denoise, 7, 80, 10);
  cv::bilateralFilter(image, cartoon, 0, 150, 30);
  cv::imshow("Source", image);
  cv::imshow("denoise", denoise);
  cv::imshow("cartoon", cartoon);
  cv::waitKey(15000);
  cv::destroyAllWindows();
}

TEST_F(Tester, LaplacianTest) {
  /**
   * 拉普拉斯算子，可以同时得到两个方向的梯度信息
   *       0 -1  0       -1 -1 -1
   *      -1  4 -1       -1  8 -1
   *       0 -1  0       -1 -1 -1
   * 左侧为拉普拉斯算子，右侧为8邻域拉普拉斯算子
   * 它的数学表达式为: L(x, y) = ∂^2f/∂x^2 + ∂^2f/∂y^2
   * 也就是同时求取两个方向的二阶导
   * X轴方向: ∂^2f/∂x^2 = 2f(x, y) - f(x+1, y) - f(x-1, y)
   * Y轴方向: ∂^2f/∂y^2 = 2f(x, y) - f(x, y-1) - f(x, y+1)
   * 两个式子合起来就是左侧的算子.
   *
   * 拉普拉斯锐化： 0 0 0        0  -1   0      0  -1   0
   *                0 1 0   +   -1   4  -1 =   -1   5  -1
   *                0 0 0        0  -1   0      0  -1   0
   * 等号左边是原图 + 拉普拉斯算子 。右侧就是用于锐化的拉普拉斯算子
   * void cv::Laplacian(
   *   InputArray src,
   *   OutputArray dst,
   *   int ddepth,
   *   int ksize = 1,
   *   double scale = 1.0,
   *   double delta = 0,
   *   int borderType = BORDER_DEFAULT
   * )
   */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat lapImg, sharpenImg, gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  cv::Laplacian(gray, lapImg, CV_32F, 3, 1.0, 0.0, 4);
  cv::normalize(lapImg, lapImg, 0, 1.0, cv::NORM_MINMAX);

  cv::Mat k = (cv::Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
  cv::filter2D(image, sharpenImg, -1, k, cv::Point(-1, -1), 0, 4);

  cv::Mat sharpenGray;
  cv::cvtColor(sharpenImg, sharpenGray, cv::COLOR_BGR2GRAY);

  int sum = calculateLaplacianSum(sharpenImg);
  std::cout << "Sharpen Laplacian improve sum " << sum << "\n";
  sum = calculateLaplacianSum(gray);
  std::cout << "Source Laplacian improve sum " << sum << "\n";

  cv::imshow("Source Image", image);
  cv::imshow("Laplacian Image", lapImg);
  cv::imshow("Sharpen Image", sharpenImg);

  cv::waitKey(30000);
  cv::destroyAllWindows();
}

} // namespace cvtest::tester

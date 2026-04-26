#include "pch.h"
#include "tester.h"
#include "gtest/gtest.h"
#include <array>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

/**
 * 第四章: 图像直方图
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

  cv::Scalar scalar1, scalar2;
  cv::meanStdDev(image, scalar1, scalar2);
  std::cout << "Scalar Mean " << scalar1 << "\n";
  std::cout << "Scalar Std " << scalar2 << "\n";

  cv::Mat mat1, mat2;
  cv::meanStdDev(image, mat1, mat2);
  std::cout << "Mat Mean " << mat1 << "\n";
  std::cout << "Mat Std " << mat2 << "\n";
}

TEST_F(Tester, HistogramImageDisplayTest) {
  /**
   * 直方图的计算
   * void cv::calcHist(
   *  const Mat* images,        // 输入图像，通道数和类型一致
   *  int nimages,              // 图像数量
   *  const int* channels,      // 需要计算的通道索引
   *  InputArray mask,          // 掩膜图像
   *  OutputArray hist,         // 输出
   *  int dims,                 // 直方图的维度
   *  const int* histSize,      // 每个维度的区间
   *  const float** ranges,     // 每个维度像素取值范围
   *  bool uniform = true,      // 边界数据处理方式
   *  bool accumulate = false   // 是否计算累计直方图
   * )
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  cv::Mat grayHist;
  int graySize = 256;
  float grayRange[] = {0, 256};
  const float *grayHistRange = {grayRange};
  int channels[] = {0};
  cv::calcHist(&gray, 1, channels, cv::Mat(), grayHist, 1, &graySize,
               &grayHistRange);
  drawHistogram1D(grayHist, "1D Hist", 256);
  drawColorHistogram3Channel(image);
  drawDetailedHistogram(image);
}

TEST_F(Tester, EqualizehistTest) {
  /**
   * 直方图均衡化
   * void cv::equalizeHist(
   *  InputArray src,
   *  OutputArray dst
   * )
   * src: 必须是 CV_8U的单通道图像
   * dst: 输出，与src类型保持一致
   *
   * 对于彩色图像，先转成 HSV 色彩空间，然后 对 V 进行均衡化，最后再merge
   * */
  cv::Mat image = cv::imread(filepath_);
  cv::Mat gray, dst, claheDst;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  cv::equalizeHist(gray, dst);

  // 对比度限制的自适应直方图均衡化
  cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
  clahe->setClipLimit(4.0); // 限制对比度,值越大，对比度越明显
  // 网格，表示把原图分成大小为 8*8 的多个小块，算法在每个小块内独立做均衡化
  clahe->setTilesGridSize(cv::Size(8, 8));
  clahe->apply(gray, claheDst);

  cv::imshow("Source", image);
  cv::imshow("EqualizedHist-Gray", dst);
  cv::imshow("EqualizedHist-Gray-clahe", claheDst);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

TEST_F(Tester, HistCompareTest) {
  /**
   * 直方图比较
   * double cv::compareHist(
   *  InputArray h1,
   *  InputArray h2,
   *  int method
   * )
   * method: 直方图相似性比较方法
   * 1. 相关性相似比较 (HIST_CMP_CORREL)
   * 2. 卡方相似性比较 (HIST_CMP_CHISQR)
   * 3. 交叉相似性 (HISTCMP_INTERSECT)
   * 4. 巴氏距离 (HISTCMP_BHATTACHARYYA)
   * 5. 海林格距离 (HISTCMP_HELLINGER) 与巴氏距离一样
   * 6. 可变卡方相似 (HISTCMP_CHISQR_ALT)
   * 7. 基于KL散度相似比较 (HISTCMP_KL_DIV)
   * */
  cv::Mat image1 = cv::imread(filepath_);
  cv::Mat image2 = cv::imread(ricePath_);
  cv::Mat hsv1, hsv2;
  cv::cvtColor(image1, hsv1, cv::COLOR_BGR2HSV);
  cv::cvtColor(image2, hsv2, cv::COLOR_BGR2HSV);

  int hBins = 60;
  int sBins = 64;
  int histSize[] = {hBins, sBins};
  float hRanges[] = {0, 180};
  float sRanges[] = {0, 256};
  const float *ranges[] = {hRanges, sRanges};
  int channels[] = {0, 1};
  cv::Mat hist1, hist2, hist3, hist4;
  calcHist(&hsv1, 1, channels, cv::Mat(), hist1, 2, histSize, ranges, true,
           false);
  calcHist(&hsv2, 1, channels, cv::Mat(), hist2, 2, histSize, ranges, true,
           false);
  cv::normalize(hist1, hist1, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
  cv::normalize(hist2, hist2, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
  std::string methods[] = {"HISTCMP_CORREL", "HISTCMP_CHISQR",
                           "HISTCMP_INTERSECT", "HISTCMP_BHATTACHARYYA"};
  for (int i = 0; i < 4; i++) {
    int compareMethod = i;
    double src1Src2 = cv::compareHist(hist1, hist2, compareMethod);
    std::cout << "Method " << methods[i] << " " << src1Src2 << "\n";
  }
}

TEST_F(Tester, HistBackProjectTest) {
  /**
   * 直方图反向投影
   * void cv::calcBackProject(
   *  const Mat *images,          // 一张或多张输入图像
   *  int nimages,                // 一共有几张图像
   *  const int *channels,        // 不同图像的通道索引
   *  InputArray hist,            // 直方图数据
   *  OutputArray backProject,    // 输出
   *  const float **ranges,       // 通道取值范围
   *  double scale = 1,           // 是否对输出结果进行缩放
   *  bol uniform = true          // 对边界数据的处理
   * )
   * */
  cv::Mat hsv1, tpl;
  cv::Mat image1 = cv::imread(grape_);
  cv::Mat imageTpl = cv::imread(grapeTpl_);
  cv::cvtColor(image1, hsv1, cv::COLOR_BGR2HSV);
  cv::cvtColor(imageTpl, tpl, cv::COLOR_BGR2HSV);

  int hBins = 32;
  int sBins = 32;
  int histSize[] = {hBins, sBins};
  float hRanges[] = {0, 180};
  float sRanges[] = {0, 256};
  const float *ranges[] = {hRanges, sRanges};
  int channels[] = {0, 1};
  cv::Mat hist1;
  calcHist(&tpl, 1, channels, cv::Mat(), hist1, 2, histSize, ranges, true,
           false);
  cv::normalize(hist1, hist1, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());
  cv::MatND backproj;
  cv::calcBackProject(&hsv1, 1, channels, hist1, backproj, ranges, 1.0);
  cv::imshow("Source", image1);
  cv::imshow("BackProj", backproj);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

} // namespace cvtest::tester

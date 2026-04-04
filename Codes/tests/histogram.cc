#include "pch.h"
#include "tester.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>

namespace cvtest::tester {
// 直方图测试
TEST_F(Tester, HistogramTest) {
  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);

  // 均值 与 方差
  // std::cout << "src " << image << std::endl;
  cv::Scalar ret = cv::mean(image);
  std::cout << "mean " << ret << std::endl;
  cv::Scalar mean, std;
  cv::meanStdDev(image, mean, std);
  std::cout << "meanStdDev " << std << std::endl;

  /**
   * void cv::calcHist(
   *  const Mat* images,              // 输入图像，一张或多张，通道与类型一致
   *  int nimages,                    // 图像数量
   *  const int* channels,            // 不同图像的通道索引
   *  InputArray mask,
   *  OutputArray hist,               // 输出直方图
   *  int dims,                       // 正数 ，不能大于 CV_MAX_DIMS
   *  const int* histSize,  // 直方图大小,可以理解为X轴上的直方图的取值范围
   *  cont float** ranges, // 通道取值范围
   *  bool uniform = true, // 边界数据处理方式,false不处理
   *  bool accumulate = false // 是否计算累计直方图
   * )
   * */
  {
    int bins = 32;
    int histSize[] = {bins};
    float rgbRanges[] = {0, 256};
    const float *ranges[] = {rgbRanges};
    int channels[] = {0};
    cv::Mat hist;
    cv::calcHist(&image, 1, channels, cv::Mat(), hist, 1, histSize, ranges,
                 true, false);
    std::cout << "hist " << hist << std::endl;

    cv::Mat histImage = cv::Mat::zeros(cv::Size(800, 500), CV_8UC3);
    int padding = 50;
    int hist_w = histImage.cols - 2 * padding;
    int hist_h = histImage.rows - 2 * padding;
    int bin_w = cvRound((double)hist_w / bins);
    cv::normalize(hist, hist, 0, hist_h, cv::NORM_MINMAX);
    int base_h = hist_h + padding;
    for (int i = 1; i < bins; i++) {
      cv::line(
          histImage,
          cv::Point(bin_w * (i - 1) + padding,
                    base_h - cvRound(hist.at<float>(i - 1))),
          cv::Point(bin_w * i + padding, base_h - cvRound(hist.at<float>(i))),
          cv::Scalar(255, 255, 255), 2, 8, 0);
    }
  }

  /**
   * 全局直方图均衡化,所有数据都会受影响
   * void cv::equalizeHist(
   *  InputArray src,
   *  OutputArray dst
   * )
   *
   * 自适应均衡化
   * */

  /**
   * 直方图比较
   *  根据归一化之后的两个直方图进行相似性比较，从而得到两幅图之间的相似度
   * double cv::compareHist(
   *  InputArray h1,
   *  InputArray h2,
   *  int method
   * )
   * method: 相关性相似比较 (HISTCMP_CORREL)
   * */

  /**
   * 直方图反射投影
   * void cv::calcBackProject(
   *  const Mat *images, // 输入图像
   *  int nimages, // 输入图像数量
   *  const int *channels, // 不同图像的通道索引
   *  InputArray hist, // 输入的模板直方图数据
   *  OutputArray backProject, // 反向投影之后的输出
   *  const float** ranges, // 通道取值范围
   *  double scale = 1, // 是否对数据缩放
   *  bool uniform = true // 边界数据处理方式
   * )
   * */
}
} // namespace cvtest::tester

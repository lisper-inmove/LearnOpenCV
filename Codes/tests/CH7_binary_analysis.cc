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
 * 第七章: 二值分析
 * */

namespace cvtest::tester {
TEST_F(Tester, BinaryMethodCompareTest) {
  /**
   * 常见的二值化方法
   * 1. 基于全局阈值(threshold)得到二值函数
   * 2. 自适应阈值(adaptiveThreshold)
   * 3. Canny
   * 4. inRange
   * */
}

TEST_F(Tester, ConnectedComponentLabelingTest) {
  /**
   * 连通组件标记
   * 扫描图像的每个像素，将位置相邻且值相同的像素点归为相同的组，最终得到图像中所有像素的连通组件
   * int cv::connectedComponents(
   *  InputArray image,
   *  OutputArray labels,          // 输出的标记，其中前景标记为0
   *  int connectivity = 8,        // 连通域，默认8连通
   *  int ltype = CV_32S           // 输出的label类型
   * )
   *
   * int cv:connectedComponentsWithStats(
   *  InputArray image,
   *  OutputArray labels,         // 统计信息
   *  OutputArray stats,
   *  OutputArray centroids,      // 每个连通组件的中心坐标
   *  int connectivity,
   *  int ltype,
   *  int ccltype
   * )
   * 统计信息包含以下内容
   * CC_STAT_LEFT: 连通组件外接矩形左上角坐标x
   * CC_STAT_TOP: 连通组件外接矩形左上角坐标y
   * CC_STAT_WIDTH: 连通组件外接矩形的宽度
   * CC_STAT_HEIGHT: 连通组件外接矩形的高度
   * CC_STAT_AREA: 连通组件外接矩形面积（像素总和）
   * */
  cv::Mat image = cv::imread(ricePath_);
  cv::Mat binary, gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
  cv::Mat centeroids, labels, stats;
  int nums = cv::connectedComponentsWithStats(binary, labels, stats, centeroids,
                                              8, CV_32S);
  cv::cvtColor(binary, binary, cv::COLOR_GRAY2BGR);
  cv::Scalar green(0, 255, 0);
  cv::Scalar blue(0, 0, 255);
  for (int i = 0; i < nums; i++) {
    int x = centeroids.at<double>(i, 0);
    int y = centeroids.at<double>(i, 1);
    int left = stats.at<int>(i, cv::CC_STAT_LEFT);
    int top = stats.at<int>(i, cv::CC_STAT_TOP);
    int width = stats.at<int>(i, cv::CC_STAT_WIDTH);
    int height = stats.at<int>(i, cv::CC_STAT_HEIGHT);
    int area = stats.at<int>(i, cv::CC_STAT_AREA);
    cv::Point center(x, y);
    cv::Rect box(left, top, width, height);
    cv::rectangle(binary, box, green, 2, 8, 0);
    cv::circle(binary, center, 2, blue, 2, 8, 0);
  }
  cv::imshow("Source Image", image);
  cv::imshow("Connected Components", binary);
  cv::waitKey(30000);
  cv::destroyAllWindows();
}

} // namespace cvtest::tester

#include "pch.h"
#include "tester.h"
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace cvtest::tester {
TEST_F(Tester, ConnectedComponentTest) {
  /**
   * 连通组件标记
   * int cv::connectedComponents(
   *  InputArray image,
   *  OutputArray labels,
   *  int connectivity = 8,
   *  int ltype = CV_32S
   * )
   * */
  cv::Mat image = cv::imread(ricePath_, cv::IMREAD_COLOR);
  cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
  cv::Mat labels, binaryGaussian;
  cv::Mat labelsDisplay;

  cv::adaptiveThreshold(image, binaryGaussian, 255,
                        cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 25,
                        10);
  cv::connectedComponents(binaryGaussian, labels);

  double minVal, maxVal;
  cv::minMaxLoc(labels, &minVal, &maxVal);
  labels.convertTo(labelsDisplay, CV_8U, 255.0 / maxVal);

  cv::Mat labelsColor;
  cv::applyColorMap(labelsDisplay, labelsColor, cv::COLORMAP_JET);

  cv::imshow("Source", image);
  cv::imshow("Labels", labelsDisplay);
  cv::imshow("LabelsColor", labelsColor);
  cv::waitKey();
  cv::destroyAllWindows();
}

TEST_F(Tester, ConnectedComponentWithStatsTest) {
  /**
   * 带信息的连通组件标记
   * int cv::connectedComponentsWithStats(
   *  InputArray image,
   *  OutputArray labels,
   *  OutputArray stats,
   *  OutputArray centroids,
   *  int connectivity,
   *  int ltype,
   *  int ccltype
   * )
   * */
  cv::Mat image = cv::imread(ricePath_, cv::IMREAD_COLOR);
  cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
  cv::Mat labels, binary;
  cv::Mat labelsDisplay;
  cv::Mat centeroids, stats;

  cv::threshold(image, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
  int nums = cv::connectedComponentsWithStats(binary, labels, stats, centeroids,
                                              8, CV_32S);

  cv::cvtColor(binary, binary, cv::COLOR_GRAY2BGR);
  for (int i = 0; i < nums; i++) {
    int x = centeroids.at<double>(i, 0);
    int y = centeroids.at<double>(i, 1);
    int left = stats.at<int>(i, cv::CC_STAT_LEFT);
    int top = stats.at<int>(i, cv::CC_STAT_TOP);
    int width = stats.at<int>(i, cv::CC_STAT_WIDTH);
    int height = stats.at<int>(i, cv::CC_STAT_HEIGHT);
    // int area = stats.at<int>(i, cv::CC_STAT_AREA);
    cv::Rect box(left, top, width, height);
    cv::rectangle(binary, box, cv::Scalar(0, 255, 0), 2, 8, 0);
    cv::circle(binary, cv::Point(x, y), 2, cv::Scalar(0, 0, 255), 2, 8, 0);
  }
  cv::imshow("Source", image);
  cv::imshow("Labels", binary);
  cv::waitKey();
  cv::destroyAllWindows();
}

} // namespace cvtest::tester

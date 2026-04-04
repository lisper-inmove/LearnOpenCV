#include "tester.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace cvtest::tester {
void Tester::SetUp() {}

void Tester::TearDown() {}

int Tester::sharpenValue(cv::Mat &image) {
  /**
   * 计算图像的锐度，锐度越大，图像越清晰
   * */
  cv::Mat gray;
  int h = image.rows;
  int w = image.cols;
  float sum = 0;
  cv::cvtColor(image, gray, cv::COLOR_RGBA2GRAY);
  for (int row = 1; row < h - 1; row++) {
    for (int col = 1; col < w - 1; col++) {
      int dx = gray.at<uchar>(row, col) * 2 - gray.at<uchar>(row, col + 1) -
               gray.at<uchar>(row, col - 1);
      int dy = gray.at<uchar>(row, col) * 2 - gray.at<uchar>(row + 1, col) -
               gray.at<uchar>(row - 1, col);
      sum += (abs(dx) + abs(dy));
    }
  }
  return sum;
}
} // namespace cvtest::tester

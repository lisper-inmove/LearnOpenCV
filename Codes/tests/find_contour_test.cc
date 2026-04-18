#include "pch.h"
#include "tester.h"
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/operations.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

namespace cvtest::tester {
TEST_F(Tester, FindConttourTest) {
  /**
   * 轮廓发现
   * void cv::findContours(
   *  InputArray src,
   *  OutputArrayOfArrays contours, // 所有轮廓
   *  OutputArray hierarchy,
   *  int mode,
   *  int method,
   *  Point offset = Point()
   * )
   *
   * 轮廓绘制
   * void cv::drawContours(
   *  InputOutputArray image,
   *  InputArrayOfArrays contours,
   *  int contourIdx,
   *  const Scalar& color,
   *  int thickness = 1,
   *  int lineType = LINE_8,
   *  InputArray hierarchy = noArray(),
   *  int maxLevel = INT_MAX,
   *  Point offset = Point()
   * )
   * */
  cv::Mat gray;
  cv::Mat image = cv::imread(cxPath_, cv::IMREAD_COLOR);
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(gray, contours, hierarchy, cv::RETR_TREE,
                   cv::CHAIN_APPROX_NONE, cv::Point());
  cv::Mat result = cv::Mat::zeros(gray.size(), CV_8UC3);
  cv::drawContours(result, contours, -1, cv::Scalar(0, 0, 255), 2, 8);

  cv::imshow("Source", image);
  cv::imshow("Gray", gray);
  cv::imshow("Result", result);
  cv::waitKey();
  cv::destroyAllWindows();
}

TEST_F(Tester, ConttourMeasureTest) {
  /**
   * 轮廓测量
   *
   * 计算轮廓的面积
   * double cv::contourArea(
   *  InputArray contour,
   *  bool oriented = false
   * )
   *
   * 计算周长
   * double cv::arcLength(
   *  InputArray curve,
   *  bool closed
   * )
   *
   * 外接矩形
   * Rect cv::boundingRect(
   *  InputArray array
   * )
   *
   * */
  cv::Mat gray;
  cv::Mat image = cv::imread(ricePath_, cv::IMREAD_COLOR);
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(gray, contours, hierarchy, cv::RETR_TREE,
                   cv::CHAIN_APPROX_NONE, cv::Point());
  cv::Mat result = cv::Mat::zeros(gray.size(), CV_8UC3);
  cv::drawContours(result, contours, -1, cv::Scalar(0, 0, 255), 2, 8);

  for (auto &contour : contours) {
    cv::Rect box = cv::boundingRect(contour);
    double area = cv::contourArea(contour);
    double arc = cv::arcLength(contour, true);
    cv::putText(result, cv::format("area:%.2f", area), box.tl(),
                cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0, 255, 0), 1, 8);
    cv::putText(result, cv::format("arc:%.2f", arc),
                cv::Point(box.x, box.y + 14), cv::FONT_HERSHEY_PLAIN, 1.0,
                cv::Scalar(0, 255, 0), 1, 8);
  }

  cv::imshow("Source", image);
  cv::imshow("Result", result);
  cv::waitKey();
  cv::destroyAllWindows();
}

TEST_F(Tester, EllipseFitTest) {
  /**
   * 拟合
   *
   * 椭圆拟合
   * RotatedRect cv::fitEllipse (
   *  InputArray points,
   * )
   *
   * 直线拟合
   * void cv::fitLine(
   *  InputArray points,
   *  OutputArray line,
   *  int distType,
   *  double param,
   *  double reps,
   *  double aeps
   * )
   * */
  cv::Mat gray;
  cv::Mat image = cv::imread(stuffPath_, cv::IMREAD_COLOR);
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  cv::Mat edges;
  int t = 80;
  cv::Canny(image, edges, t, t * 2, 3, false);
  cv::Mat k = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3),
                                        cv::Point(-1, -1));
  cv::dilate(edges, edges, k);

  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(edges, contours, hierarchy, cv::RETR_EXTERNAL,
                   cv::CHAIN_APPROX_SIMPLE);

  // 椭圆拟合
  for (auto &contour : contours) {
    if (contour.size() < 5) {
      continue;
    }
    cv::RotatedRect rrt = cv::fitEllipse(contour);
    // cv::Point cp = rrt.center;
    // float a = rrt.size.width;
    // float b = rrt.size.height;
    cv::ellipse(image, rrt, cv::Scalar(0, 0, 255), 2, 8);
  }

  cv::imshow("Source", image);
  cv::waitKey();
  cv::destroyAllWindows();
}

TEST_F(Tester, LineFitTest) {
  /**
   * 拟合
   *
   * 椭圆拟合
   * RotatedRect cv::fitEllipse (
   *  InputArray points,
   * )
   *
   * 直线拟合
   * void cv::fitLine(
   *  InputArray points,
   *  OutputArray line,
   *  int distType,
   *  double param,
   *  double reps,
   *  double aeps
   * )
   * */
  cv::Mat gray;
  cv::Mat image = cv::imread(stuffPath_, cv::IMREAD_COLOR);
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  cv::Mat edges;
  int t = 80;
  cv::Canny(image, edges, t, t * 2, 3, false);
  cv::Mat k = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3),
                                        cv::Point(-1, -1));
  cv::dilate(edges, edges, k);

  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(edges, contours, hierarchy, cv::RETR_EXTERNAL,
                   cv::CHAIN_APPROX_SIMPLE);

  for (auto &contour : contours) {
    cv::Vec4f oneline;
    cv::fitLine(contour, oneline, cv::DIST_L1, 0, 0.01, 0.01);
    float vx = oneline[0];
    float vy = oneline[1];
    float x0 = oneline[2];
    float y0 = oneline[3];
    float k = vy / vx;
    float b = y0 - k * x0;
    int minx = 0, miny = 10000;
    int maxx = 0, maxy = 0;
    for (auto &point : contour) {
      if (miny > point.y) {
        miny = point.y;
      }
      if (maxy < point.y) {
        maxy = point.y;
      }
    }
    maxx = (maxy - b) / k;
    minx = (miny - b) / k;
    cv::line(image, cv::Point(maxx, maxy), cv::Point(minx, miny),
             cv::Scalar(0, 0, 255), 2, 8, 0);
  }

  cv::imshow("Source", image);
  cv::waitKey();
  cv::destroyAllWindows();
}

TEST_F(Tester, ContourApproxTest) {
  /**
   * 轮廓逼近
   * void cv::approxPolyDP(
   *  InputArray curve,
   *  OutputArray approxCurve,
   *  double epsilon,
   *  bool closed
   * )
   * */
  cv::Mat gray;
  cv::Mat image = cv::imread(contoursPath_, cv::IMREAD_COLOR);
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  cv::Mat edges;
  int t = 80;
  cv::Canny(image, edges, t, t * 2, 3, false);
  cv::Mat k = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3),
                                        cv::Point(-1, -1));
  cv::dilate(edges, edges, k);

  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(edges, contours, hierarchy, cv::RETR_EXTERNAL,
                   cv::CHAIN_APPROX_SIMPLE);

  for (auto &contour : contours) {
    std::vector<cv::Point> pts;
    cv::approxPolyDP(contour, pts, 10, true);
    for (auto &point : pts) {
      cv::circle(image, point, 3, cv::Scalar(0, 0, 255), 2, 8, 0);
    }
  }

  cv::imshow("Source", image);
  cv::waitKey();
  cv::destroyAllWindows();
}

TEST_F(Tester, ContourAnalysisTest) {
  /**
   * 轮廓分析
   * 1. 横纵比: 宽度与高度的比值
   *   boundingRect的作用是计算轮廓的最大外接矩形
   *   minAreaRect 计算轮廓最小外接矩形
   *     RotatedRect cv::minAreaRect(InputArray points);
   *
   * 2. 延展度: 轮廓面积与最大外接矩形的比值
   * 3. 实密度: 轮廓面积与最大外接矩形的比值
   * 4. 对象像素均值:
   * 进行轮廓绘制时，将thickness的值设置为-1就能完成轮廓填充，并生成轮廓对象所对应的掩膜
   *    然后用mean函数实现对掩膜区域的均值求解，最终得到每个对象的轮廓所占区域的像素均值
   *
   * */
  cv::Mat gray;
  cv::Mat image = cv::imread(contoursPath_, cv::IMREAD_COLOR);
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  cv::Mat edges;
  int t = 80;
  cv::Canny(image, edges, t, t * 2, 3, false);
  cv::Mat k = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3),
                                        cv::Point(-1, -1));
  cv::dilate(edges, edges, k);

  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(edges, contours, hierarchy, cv::RETR_EXTERNAL,
                   cv::CHAIN_APPROX_SIMPLE);

  for (auto &contour : contours) {
    std::vector<cv::Point> pts;
    cv::approxPolyDP(contour, pts, 10, true);
    for (auto &point : pts) {
      cv::circle(image, point, 3, cv::Scalar(0, 0, 255), 2, 8, 0);
    }
  }

  cv::imshow("Source", image);
  cv::waitKey();
  cv::destroyAllWindows();
}

} // namespace cvtest::tester

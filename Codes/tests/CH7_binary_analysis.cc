#include "pch.h"
#include "tester.h"
#include "gtest/gtest.h"
#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/cvdef.h>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/operations.hpp>
#include <opencv2/core/saturate.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <sys/wait.h>
#include <vector>

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
    // 面积就是像素总和
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

TEST_F(Tester, FindContoursTest) {
  /**
   * 轮廓发现
   * 二值图的连通组件扫描可以发现并定位每个连通组件的位置，
   * 但是无法给出连通组件之间的层级关系，拓扑结构以及各个连通组件的轮廓信息
   * 这个时候就要用到轮廓发现的功能
   *
   * 轮廓发现: 是指提取二值图像中每个对象及其所有子对象的边缘
   *   并对边缘线进行关键点编码与构建对象包含关系的过程
   *
   * void cv::findContours(
   *    InputArray image,
   *    OutputArrayOfArrays contours,  // 所有轮廓的保存
   *    OutputArray hierarchy,         // 轮廓的层级信息保存
   *    int mode,
   *    int method,
   *    Point offset = Point()
   * )
   * hierarchy是一个Vec4i数据结构:
   *  [0]: 同层下个轮廓索引
   *  [1]: 同层上个轮廓索引
   *  [2]: 下层第一个子轮廓索引
   *  [3]: 上层父轮廓索引
   *
   * mode: 获取轮廓信息的方式
   *  RETR_EXTERNAL: 只获取最外层
   *  RETR_TREE: 获取部分轮廓，并按照树形结构组织将拓扑信息输出到hierachy
   *  RETR_LIST: 获取所有轮廓，不建立层次关系
   *  RETR_CCOMP: 组织为两层结构（外层和孔洞）
   *
   * method 每个轮廓点的编码方式
   *  CHAIN_APPROX_NONE: 对所有轮廓点进行编码
   *  CHAIN_APPROX_SIMPLE: 过滤水平，垂直，对角线上的点，只保留顶点
   *  CHAIN_APPROX_TC89_L1: Teh-Chin链近似算法
   *  CHAIN_APPROX_TC89_KCOS: Teh-Chin链近似算法
   * */
}

TEST_F(Tester, DrawContoursTest) {
  /**
   * 轮廓绘制函数
   * void cv::drawContours(
   *  InputOutputArray image,
   *  InputArrayOfArrays contours,
   *  int contourIdx,
   *  const Scalar& color,
   *  int thickness = 1,
   *  int lineType= LINE_8,
   *  InputArray hierarchy = noArray(),
   *  int maxLevel = INT_MAX,
   *  Point offset = Point()
   * )
   * contourIdx: 绘制第几个轮廓,-1表示绘制所有
   * thickness: 线宽,-1表示填充
   * linType: 线段渲染方式，当前LINE_4, LIEN_8, LINE_AA, FILLED
   * maxLevel: 只有当设置了hierachy时才有效。
   *  0: 只绘制当前轮廓
   *  1: 当前轮廓 与它的嵌套轮廓
   *  2~maxLevel 以此类推
   * */
  cv::Mat image, gray;
  image = cv::imread(cxPath_);
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(gray, contours, hierarchy, cv::RETR_TREE,
                   cv::CHAIN_APPROX_SIMPLE, cv::Point());
  cv::Mat result = cv::Mat::zeros(image.size(), image.type());
  cv::drawContours(result, contours, -1, cv::Scalar(0, 255, 0), 2, cv::FILLED);
  cv::imshow("Contours", result);
  cv::waitKey(15000);
  cv::destroyAllWindows();
}

TEST_F(Tester, ContourMeatureTest) {
  /**
   * 轮廓测量
   * double cv::contourArea(
   *  InputArray contour,
   *  bool oriented = false
   * )
   * 测量面积，如果oriented为true，会根据轮廓编码点的顺时针或逆时针方向返回正值或负值
   *
   * double cv::arcLenght(
   *  InputArray curve,
   *  bool closed
   * )
   * 计算一段弧长或者闭合轮廓周长
   *
   * 计算并生成最大外接矩形
   * Rect cv::boundingRect(
   *  InputArray array
   * )
   *
   * 计算并生成最小外接矩形
   * RotatedRect cv::minAreaRect(
   *  InputArray points
   * )
   *
   * 最小外接圆
   * void cv::minEnclosingCircle(
   *  IpnutArray points,
   *  Point2f& center,
   *  float& radius
   * );
   *
   * 轴对齐矩形
   * boundingRect()
   * */
  cv::Mat image, gray;
  image = cv::imread(ricePath_);
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(gray, contours, hierarchy, cv::RETR_TREE,
                   cv::CHAIN_APPROX_SIMPLE, cv::Point());
  cv::Mat result = cv::Mat::zeros(image.size(), image.type());
  cv::drawContours(result, contours, -1, cv::Scalar(0, 255, 0), 2, cv::FILLED);
  cv::Scalar green(0, 255, 0);
  cv::Scalar red(0, 0, 255);
  for (auto &contour : contours) {
    cv::Rect box = cv::boundingRect(contour);
    double area = cv::contourArea(contour);
    double arc = cv::arcLength(contour, true);

    cv::Point2f center;
    float radius;
    cv::minEnclosingCircle(contour, center, radius);
    cv::circle(result, center, radius, red);

    std::cout << "Area: " << area << "\n";
    std::cout << "Arc: " << arc << "\n";
    cv::putText(result, cv::format("Area:%.2f", area), box.tl(),
                cv::FONT_HERSHEY_PLAIN, 1.0, green, 1, 8);
    cv::putText(result, cv::format("Arc:%.2f", area),
                cv::Point(box.x, box.y + 14), cv::FONT_HERSHEY_PLAIN, 1.0,
                green, 1, 8);
  }
  cv::imshow("Contours", result);
  cv::waitKey(15000);
  cv::destroyAllWindows();
}

TEST_F(Tester, MomentsTest) {
  /**
   * 矩，用于计算重心，方向等
   * cv::Moments cv::moments(
   *  Inputarray points,
   *  bool binaryImage = false
   * )
   * */
}

TEST_F(Tester, FitAndApproxTest) {
  /**
   * 轮廓的逼近与拟合
   *
   * 椭圆拟合
   * RotatedRect cv::fitElipse(
   *  InputArray points
   * )
   * points: 输入的点集
   * RotatedRect的输出包含: 拟合之后椭圆的中心位置，长轴与短轴相同时为圆
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
   * points: 输入的点集
   * line: 二维拟合时返回Vec4f，三维时返回Vec6f
   *       (vx, vy, x0, y0)     (vx, vy, vz, x0, y0, z0)
   *       带v的表示方向，不必是单位向量，但是已做归一化
   *
   * distType: 距离计算公式，
   *   DIST_L1 = 1: 标准最小二乘法，距离为欧氏距离的平方
   *   DIST_L2 = 2: 曼哈顿距离（绝对值距离）
   *   DIST_L12 = 4: L1-L2混合度量2 * (sqrt(1 + x^2/2)- 1)
   *   DIST_FAIR = 5:
   *   DIST_WELSCH= 6: C^2 / 2(1 - exp(-(x/C)^2))
   *   DIST_HUBER = 7
   *
   * param: distType为5,6,7时，为公式中的C，设置为0时，会使用默认值
   *
   * reps: 径向精度。
   *   直线位置(x0, y0)的拟合精度。
   *   表示算法停止迭代时，直线在垂直于自身方向上的移动步长必须小于此值
   *
   * aeps: 角度精度
   *    直线方向(vx, vy)的拟合精度。
   *    角度变化的余弦值精度
   *
   * reps和aeps常用值为0.01，只要有一个达标，迭代就会停止
   *
   * 轮廓拟合有时并不能顺利得到轮廓的几何形状信息，需要通过轮廓逼近函数才能实现。
   * void cv::approxPolyDP(
   *  InputArray curve,             // 输入轮廓点集
   *  OutputArray approxCurve,      // 输出点集
   *  double epsilon,               // 逼近精度
   *  bool closed
   * )
   *
   * 道格拉斯-普克算法 (Douglas-Peucker)
   *  1. 将curve的首尾相连
   *  2. 然后计算曲线上所有点到这条直线的距离，找到距离最大的点
   *  3. 判断是否保留:
   *    如果最大距离 <= epsilon: 舍弃中间所有点，用直线段近似
   *    如果最大距离 > epsilon: 保留该点，并以此点为界递归分割曲线为两部分
   *                            重复上述过程
   *  4. 递归处理 对分割后的两段曲线分别重复1~3步
   * */
}

TEST_F(Tester, EllipseFitTest) {
  /**
   * 椭圆拟合测试
   * */

  cv::Mat image = cv::imread(stuffPath_);
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
    if (contour.size() < 5)
      continue;
    cv::RotatedRect rrt = cv::fitEllipse(contour);
    cv::Point cp = rrt.center;
    float a = rrt.size.width;
    float b = rrt.size.height;
    std::cout << "a: " << a << " b: " << b << "\n";
    cv::ellipse(image, rrt, cv::Scalar(0, 0, 255), 2, 8);
  }
  cv::imshow("Contour Fit and Approx", image);
  cv::waitKey(30000);
  cv::destroyAllWindows();
}

TEST_F(Tester, LineFitTest) {
  /**
   * 直线拟合测试
   * */

  cv::Mat image = cv::imread(stuffPath_);
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
    if (contour.size() < 5)
      continue;
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
    for (const auto &pt : contour) {
      if (miny > pt.y) {
        miny = pt.y;
      }
      if (maxy < pt.y) {
        maxy = pt.y;
      }
    }
    maxx = (maxy - b) / k;
    minx = (miny - b) / k;
    cv::line(image, cv::Point(maxx, maxy), cv::Point(minx, miny),
             cv::Scalar(0, 0, 255), 2, 8, 0);
  }
  cv::imshow("Contour Fit and Approx", image);
  cv::waitKey(30000);
  cv::destroyAllWindows();
}

TEST_F(Tester, ApproxPolyDPTest) {
  cv::Mat image = cv::imread(contoursPath_);
  cv::Mat gray, binary;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(binary, contours, hierarchy, cv::RETR_EXTERNAL,
                   cv::CHAIN_APPROX_SIMPLE, cv::Point());
  for (auto &contour : contours) {
    std::vector<cv::Point> pts;
    cv::approxPolyDP(contour, pts, 10, true);
    for (auto &point : pts) {
      cv::circle(image, point, 3, cv::Scalar(0, 0, 255), 1, 8, 0);
    }
  }
  cv::imshow("ApproxPolyDP", image);
  cv::waitKey(30000);
  cv::destroyAllWindows();
}

TEST_F(Tester, ContourAnalysisTest) {
  /**
   * 轮廓分析
   * 1. 横纵比：轮廓外接矩形宽与高的比值，轮廓外接矩形包括 最大和最小两种
   * 2. 延展度: 轮廓面积与最大外接矩形的比值
   * 3. 实密度: 轮廓面积与凸包面积的比值
   * 4. 对象像素均值: 某个轮廓内部所有像素的灰度值（或颜色值）的平均值
   *     在进行轮廓绘制时，将thickness的值设置为-1，就能完成轮廓填充
   *     并生成轮廓对象所对应的掩膜，然后用mean函数实现对掩膜区域的均值求解
   *     最终得到每个对象的轮廓所占区域的像素均值
   * */

  // 二值化，stuffPath_比较复杂所以用Canny做二值化会比较好
  cv::Mat image = cv::imread(stuffPath_);
  cv::Mat edges;
  cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);
  int t = 80;
  cv::Canny(image, edges, t, t * 2, 3, false);

  cv::Mat k = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3),
                                        cv::Point(-1, -1));
  cv::dilate(edges, edges, k);

  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(edges, contours, hierarchy, cv::RETR_EXTERNAL,
                   cv::CHAIN_APPROX_SIMPLE);
  int index = 0;
  for (auto &contour : contours) {
    // 最大外接矩形
    cv::Rect box = cv::boundingRect(contour);
    // 最小外接矩形
    cv::RotatedRect rrt = cv::minAreaRect(contour);
    // 凸包
    std::vector<cv::Point> hulls;
    cv::convexHull(contour, hulls);
    double hullArea = cv::contourArea(hulls);
    double boxArea = box.width * box.height;
    // 轮廓面积
    double area = cv::contourArea(contour);
    // 横纵比
    double aspectRatio = cv::saturate_cast<double>(rrt.size.width) /
                         cv::saturate_cast<double>(rrt.size.height);
    // 延展度
    double extend = area / boxArea;
    // 实密度
    double solidity = area / hullArea;

    // 对象像素均值
    mask.setTo(cv::Scalar(0));
    cv::drawContours(mask, contours, index, cv::Scalar(255), -1);
    cv::Scalar bgra = cv::mean(image, mask);
    cv::putText(image, cv::format("Extend:%.2f", extend), box.tl(),
                cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0, 0, 255), 1, 8);
    cv::putText(image, cv::format("Soldit:%.2f", solidity),
                cv::Point(box.x, box.y + 14), cv::FONT_HERSHEY_PLAIN, 1.0,
                cv::Scalar(0, 0, 255), 1, 8);
    cv::putText(image, cv::format("AspectRatio:%.2f", aspectRatio),
                cv::Point(box.x, box.y + 28), cv::FONT_HERSHEY_PLAIN, 1.0,
                cv::Scalar(0, 0, 255), 1, 8);
    cv::putText(
        image,
        cv::format("Mean:(%d,%d,%d)", (int)bgra[0], (int)bgra[1], (int)bgra[2]),
        cv::Point(box.x, box.y + 42), cv::FONT_HERSHEY_PLAIN, 1.0,
        cv::Scalar(0, 0, 255), 1, 8);
    index++;
  }
  cv::imshow("Contour Analysis", image);
  cv::waitKey(30000);
  cv::destroyAllWindows();
}

TEST_F(Tester, LineDetectionTest) {
  /**
   * 直线检测
   *
   * 霍夫变换: https://zhuanlan.zhihu.com/p/203292567
   *
   * 霍夫直线检测: 用于检测图像中的直线
   * void cv::HoughLines(
   *  InputArray image,            // 必须是8位单通道二值图
   *  OutputArray lines,
   *  double rho,                  // rho 的精度，一般为1
   *  double theta,                // theta的精度，一般 为 CV_PI/180
   *  int threshold,
   *  double srn = 0,
   *  double stn = 0,
   *  double min_theta = 0,       // 直线旋转角度
   *  double max_theta = CV_PI    // 直线旋转角度
   * )
   * lines: 输出结果
   *    如果是 vector<Vec2f>, rho和theta
   *    如果是 vector<Vec3f>, rho，theta和votes
   * threshold: 累加器的阈值，一条直线至少要多少票才能被返回
   * srn, stn: 多尺度霍夫变换的参数。通常保持为0，使用经典算法
   *
   * 概率霍夫直线检测: 主要用于检测图像中的线段,输出线段坐标
   * void cv::HoughLinesP(
   *  InputArray image,
   *  OutputArray lines,
   *  double rho,
   *  double theta,
   *  int threshold,
   *  double minLineLength = 0,   // 拥有最少像素数的直线，小于该值将被舍弃
   *  double maxLineGap = 0       // 同一条线允许的最大断开距离
   * )
   * lines: 输出线段中的两个端点
   * */
  cv::Mat image = cv::imread(sudokuPath_);
  cv::Mat edges;
  cv::Canny(image, edges, 50, 200, 3);
  std::vector<cv::Vec2f> lines;
  cv::HoughLines(edges, lines, 1, CV_PI / 180, 150, 0, 0);
  cv::Mat result1, result2;
  cv::cvtColor(edges, result1, cv::COLOR_GRAY2BGR);
  result2 = result1.clone();
  for (auto &line : lines) {
    float rho = line[0], theta = line[1];
    cv::Point pt1, pt2;
    double a = cos(theta), b = sin(theta);
    double x0 = a * rho, y0 = b * rho;
    pt1.x = cvRound(x0 + 1000 * (-b));
    pt1.y = cvRound(y0 + 1000 * (a));
    pt2.x = cvRound(x0 - 1000 * (-b));
    pt2.y = cvRound(y0 - 1000 * (a));
    cv::line(result1, pt1, pt2, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
  }

  std::vector<cv::Vec4i> linesP;
  cv::HoughLinesP(edges, linesP, 1, CV_PI / 180, 50, 50, 10);
  for (auto &line : linesP) {
    cv::Point p1 = cv::Point(line[0], line[1]);
    cv::Point p2 = cv::Point(line[2], line[3]);
    cv::line(result2, p1, p2, cv::Scalar(0, 0, 255), 2, 8, 0);
  }

  cv::imshow("Source Image", image);
  cv::imshow("HoughLines", result1);
  cv::imshow("HoughLinesP", result2);

  cv::waitKey(30000);
  cv::destroyAllWindows();
}

TEST_F(Tester, HoughCircleTest) {
  /**
   * https://chat.deepseek.com/share/bjt78j4y3x11sn8vym
   *
   * 霍夫圆检测: 先通过梯度信息找出可能的圆心，再对每个圆心验证最佳半径
   * 原理和霍夫直线检测一样，都是转换到霍夫空间
   * void cv::HoughCircles(
   *  InputArray image,         // 必须是8位单通道二值图
   *  OutputArray circles,      // 输出，通常为 vector<Vec3f> (x, y, radius)
   *  int method,
   *  double d,
   *  double minDist,
   *  double param1 = 100,
   *  double param2 = 100,
   *  int minRadius = 0,
   *  int maxRadius = 0
   * )
   *
   * method: 检测方法
   *    HOUGH_GRADIENT
   *    HOUGH_GRADIENT_ALT: 相比原版，它能更好的检测小圆
   * dp: 分辨率比例，累加器分辨率 = 图像分辨率 / dp
   *    dp = 1，累加器与图像尺寸相同，精度高但计算量大且易产生噪声
   *    dp = 2，累加器宽高减半，精度下降但速度提升
   * minDist: 最小圆心距。如果太小，可能被检测出多个相近的圆心
   *                      如果太大，可能漏掉相邻的圆
   *                      经验值，通常设置为图像对角线长度的 1/10到1/8
   * param1: Canny高阈值。
   *         传入内部Canny边缘检测器的高阈值。
   *         低阈值会自动设为param1 /2
   * param2: 圆心累加器阈值
   *         值越小，检测越宽松，假圆越多。反之则有可能漏检
   *         ALT模式取值约为 0.9，越接近1，对圆的完美度要求越高
   * minRadius，maxRadius: 限制待检测圆半径大小，单位为像素
   *    设置为0表示根据图像尺寸自动计算最大半径
   *    如果maxRadius < 0且为梯度模式，则只找圆心，不找半径
   * */
  cv::Mat image = cv::imread(coinsPath_);
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  cv::GaussianBlur(gray, gray, cv::Size(5, 5), 0, 0);
  std::vector<cv::Vec3f> circles;
  cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 2, 15, 200, 100, 25, 60);
  for (auto &circle : circles) {
    cv::Point center = cv::Point(circle[0], circle[1]);
    int radius = circle[2];
    cv::circle(image, center, radius, cv::Scalar(0, 0, 255), 2, 8, 0);
    cv::circle(image, center, 3, cv::Scalar(255, 0, 0), 3, 8, 0);
  }
  cv::imshow("HoughCircles", image);
  cv::waitKey(30000);
  cv::destroyAllWindows();
}

} // namespace cvtest::tester

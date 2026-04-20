#include "pch.h"
#include "tester.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>

/**
 * 第一章: OpenCV 基础操作
 *
 * */

namespace cvtest::tester {
TEST_F(Tester, NamedWindowTest) {
  /**
   * void namedWindow(const String& winname, int flag = WINDOW_AUTOSIZE)
   *   1. winname: 窗口名称
   *   2. flags: 窗口属性
   *     2.1 WINDOW_NORMAL: 用户可以自由调整窗口大小。结合resizeWindow可设定初始
   *     2.2 WINDOW_AUTOSIZE: 窗口自适应
   *     2.3 WINDOW_KEEPRATIO:
   * 与WINDOW_NORMAR一起使用，调整窗口大小时保持图像宽高比 2.4
   * WINDOW_GUI_EXPANDED: 增强型GUI，带工具栏和状态栏
   * */
  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  cv::namedWindow("OpenCV Window", cv::WINDOW_AUTOSIZE);
  cv::imshow("OpenCV Window", image);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

TEST_F(Tester, ReadWriteTest) {
  /**
   * cv::Mat cv::imread(const String& filename, int flags = IMREAD_COLOR);
   * IMREAD_COLOR: 1, 默认值，加载彩色图像，BGR三通道，忽略透明度
   * IMREAD_GRAYSCALE: 0, 以灰度图加载，单通道
   * IMREAD_UNCHANGED: -1, 包含alpha通道，按原样加载
   * IMREAD_ANYDEPTH: 2, 保留16-bit/32-bit尝试，否则转为8-bit
   * IMREAD_ANYCOLOR: 4, 以任何可能的颜色格式读取
   * IMREAD_IGNORE_ORIENTATION: 128, 忽略EXIF中的方向信息
   * 失败时返回空
   *
   * bool cv::imwriet(const String& filename, InputArray img, const
   * std::vector<int>& params = std::vector<int>()); params: 格式为 {paramId1,
   * value1, paramId2, value2...}
   * JPGE: IMWRITE_JPEG_QUANTITY, 0~100，越高质量越好文件越大
   * PNG: IMWRITE_PNG_COMPRESSION, 0~9，压缩级别，默认3，9最小，但最慢
   * PNG: IMWRITE_PNG_STRATEGY, 0~4，压缩策略
   * WEBP: IMWRITE_WEBP_QUALITY, 1~100，质量(默认100)
   * */
  cv::Mat image = cv::imread(filepath_, cv::IMREAD_COLOR);
  cv::namedWindow("OpenCV Window", cv::WINDOW_AUTOSIZE);
  // imread默认类型是 CV_8UC3，显示时用imshow函数即可
  cv::imshow("OpenCV Window", image);
  cv::waitKey(0);
  cv::destroyAllWindows();
  std::vector<int> opts;
  opts.push_back(cv::IMWRITE_PNG_COMPRESSION);
  opts.push_back(9);
  cv::imwrite(savedFilepath_, image);
}

TEST_F(Tester, OpenVideo) {
  cv::VideoCapture cap(videoPath_);
  cv::Mat frame;
  cv::namedWindow("OpenCV Window", cv::WINDOW_AUTOSIZE);

  // 获取视频帧率
  double fps = cap.get(cv::CAP_PROP_FPS);
  int delay = static_cast<int>(1000.0 / fps); // 计算每帧延迟时间(ms)

  // 获取视频信息
  double totalFrames = cap.get(cv::CAP_PROP_FRAME_COUNT);
  double width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  std::cerr << "Video Info:\n";
  std::cerr << "  FPS: " << fps << "\n";
  std::cerr << "  Total Frames: " << totalFrames << "\n";
  std::cerr << "  Resolution: " << width << "x" << height << "\n";
  std::cerr << "  Press 'q' or 'ESC' to quit" << "\n";

  while (true) {
    bool ret = cap.read(frame);
    if (!ret) {
      break;
    }
    cv::imshow("OpenCV Window", frame);
    cv::waitKey(1);
    char key = static_cast<char>(cv::waitKey(delay));
    if (key == 'q' || key == 27) // 27 = ESC
    {
      break;
    }
  }
  cap.release(); // 释放视频资源
  cv::destroyAllWindows();
}

TEST_F(Tester, NormalizeTest) {
  /**
   * 归一化函数
   * void cv::normalize(
   *  InputArray src,
   *  InputOutputArray dst,
   *  double alpha = 1,            // 归一化下限
   *  double beta = 0,             // 范围归一化上限，仅 NORM_MINMAX模式有效
   *  int norm_type = NORM_L2,     // 归一化类型
   *  int dtype = -1,
   *  InputArray mask = noArray()
   * )
   * NORM_MINMAX: 线性拉伸。将数据最小值映射到alpha,将数据最小值映射到beta
   *              图像对比度拉伸、将数据缩放到特定区间如 [0, 1] 或 [0, 255]。
   * NORM_L1: 所有元素的绝对值之和等于alpha。
   *              计算概率分布，确保所有数值加起来为
   * NORM_L2: 所有元素的平方和等于alpah。将向量单位化
   *              将向量单位化（方向不变，长度为 1），常用于特征匹配
   * NORM_INF: 所有元素的最大绝对值等于alpha
   *              按最大值进行缩放，将所有数值压缩到 [0, alpha] 之间。
   * */
  cv::Mat src = (cv::Mat_<float>(1, 3) << 10, 20, 30);
  cv::Mat dst;

  cv::normalize(src, dst);
  std::cout << "src " << src << "\n";
  std::cout << "NORM_L2 normalized dst " << dst << "\n";

  cv::normalize(src, dst, 1, 0.0, cv::NORM_L1);
  std::cout << "src " << src << "\n";
  std::cout << "NORM_L1 normalized dst " << dst << "\n";

  cv::normalize(src, dst, 50, 100, cv::NORM_MINMAX);
  std::cout << "src " << src << "\n";
  std::cout << "NORM_MINMAX normalized dst " << dst << "\n";

  cv::normalize(src, dst, 0, 1, cv::NORM_MINMAX);
  std::cout << "src " << src << "\n";
  std::cout << "NORM_MINMAX(1, 0) normalized dst " << dst << "\n";

  cv::normalize(src, dst, 1, 0, cv::NORM_MINMAX);
  std::cout << "src " << src << "\n";
  std::cout << "NORM_MINMAX(0, 1) normalized dst " << dst << "\n";

  cv::normalize(src, dst, 50, 100, cv::NORM_INF);
  std::cout << "src " << src << "\n";
  std::cout << "NORM_INF normalized dst " << dst << "\n";
}

} // namespace cvtest::tester

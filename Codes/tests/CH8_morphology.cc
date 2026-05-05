#include "tester.h"
#include "gtest/gtest.h"
#include <cmath>
#include <cstdlib>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/cvdef.h>
#include <opencv2/core/cvstd_wrapper.hpp>
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
#include <regex>
#include <string>
#include <sys/wait.h>

/**
 * 第八章: 形态学分析
 * */

namespace cvtest::tester
{
  TEST_F(Tester, MorphologyTest)
  {
    /**
     * OpenCV 中常见的形态学操作包括
     *  腐蚀，膨胀，开闭操作，形态学梯度，黑帽与顶帽，击中/击不中
     *  相比卷积操作，形态学操作计算量更小，速度快
     *
     *  结构元素在形态学操作中至关重要，OpenCV中常见的结构元素如下
     *    矩形结构元素
     *      MORPH_RECT = 0
     *    圆形或者椭圆形
     *      MORPH_ELLIPSE = 2
     *    十字交叉
     *      MORPH_CROSS = 1
     *    垂直 / 水平 Size(1, x) / Size(x, 1)
     *
     * OpenCV中的形态学操作支持二值图，灰度图与彩色图
     * cv::MORPH_ERODE = 0，表示腐蚀操作
     * MORPH_DILATE = 1，膨胀
     * MORPH_OPEN = 2，开
     * MORPH_CLOSE = 3，闭
     * MORPH_GRADIENT = 4，梯度
     * MORPH_TOPHAT = 5，顶帽
     * MORPH_BLACKHAT = 6，黑帽
     * MORPH_HITMISS = 7，击中/击不中
     *
     * 膨胀与腐蚀是最基础的两个操作
     * */
  }

  TEST_F(Tester, DilateErodeTest)
  {
    /**
     * 膨胀与腐蚀
     *
     *  用结构元素内最大像素替换锚定位置的像素值
     * void cv::dilate(
     *  InputArray src,
     *  OutputArray dst,
     *  InputArray kernel,
     *  Point anchor = Point(-1, -1),
     *  int iterations = 1,
     *  int borderType = BORDER_CONSTANT,
     *  const Scalar& borderValue = morphologyDefaultBorderValue()
     * )
     *
     * void cv::erode(
     *  InputArray src,
     *  OutputArray dst,
     *  InputArray kernel,
     *  Point anchor = Point(-1, -1),
     *  int iterations = 1,
     *  int borderType = BORDER_CONSTANT,
     *  const Scalar& borderValue = morphologyDefaultBorderValue()
     * )
     *
     * kernel使用getStructuringElement来创建
     *  Mat cv:getSTructuringElement(
     *   int shape,
     *   Size ksize,
     *   Point anchor = Point(-1, -1)
     *  )
     *  矩形结构元素
     *    MORPH_RECT = 0
     *  圆形或者椭圆形
     *    MORPH_ELLIPSE = 2
     *  十字交叉
     *    MORPH_CROSS = 1
     *
     * 膨胀在一定程度上把相邻的对象连接起来
     * 腐蚀操作会让对象面积变小或者擦除小的对象
     * */
    cv::Mat image = cv::imread(xtPath_);
    cv::Mat dstDilate, dstErode;
    cv::Mat se = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::dilate(image, dstDilate, se);
    cv::erode(image, dstErode, se);

    cv::imshow("Source Image", image);
    cv::imshow("Dilated", dstDilate);
    cv::imshow("Eroded", dstErode);
    cv::waitKey(30000);
    cv::destroyAllWindows();
  }

  TEST_F(Tester, OpenCloseTest)
  {
    /**
     * 开闭操作
     *
     * 开: 腐蚀 + 膨胀，先腐蚀，再膨胀
     * 闭: 膨胀 + 腐蚀，先膨胀，再腐蚀
     *
     * 开操作可以删除二值图中较小的干扰块，解决图像二值化之后噪点过多的问题
     * 闭操作可以填充二值图像对象内部的孔洞，以获得更完整的前景对象
     *
     * void cv::morphologyEx(
     *  InputArray src,
     *  OutputArray dst,
     *  int op,
     *  InputArray kernel,
     *  Point annchor = Point(-1, -1),
     *  int iterations = 1,
     *  int borderType = BORDER_CONSTANT,
     *  const Scalar& borderValue = morphologyDefaultBorderValeu()
     * )
     * op = MORPH_OPEN, MORPH_CLOSE
     * */
    cv::Mat image = cv::imread(morphPath_);
    cv::Mat resultOpen, resultClose;
    cv::Mat seOpen = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::Mat seClose = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));

    // 闭操作
    // cv::erode(image, resultClose, se);
    // cv::dilate(resultOpen, resultClose, se);
    cv::morphologyEx(image, resultClose, cv::MORPH_CLOSE, seClose);

    cv::morphologyEx(image, resultOpen, cv::MORPH_OPEN, seOpen);

    cv::imshow("Source Image", image);
    cv::imshow("Open OP", resultOpen);
    cv::imshow("Close OP", resultClose);
    cv::waitKey(30000);
    cv::destroyAllWindows();
  }

  TEST_F(Tester, MorphGradientTest)
  {
    /**
     * 形态学梯度
     *  不但能快速得到二值图像中各个对象的轮廓
     *  提取对象的边缘，还能在对灰度实现形态学梯度操作之后再进行二值化
     * 包括 基本梯度，内梯度，外梯度
     *
     * 基本梯度: 膨胀 - 腐蚀， morphologyEx, op = MORPH_GRADIENT
     * 内梯度: 原图- 腐蚀
     * 外梯度: 膨胀 - 原图
     * */
    cv::Mat image = cv::imread(filepath_);
    cv::Mat basicGrad, exGrad, inGrad;
    cv::Mat binary;
    cv::Canny(image, binary, 100, 150);
    cv::Mat src = binary.clone();
    cv::Mat eroded, dilated;
    cv::Mat se = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(src, dilated, se);
    cv::erode(src, eroded, se);
    cv::morphologyEx(src, basicGrad, cv::MORPH_GRADIENT, se);
    cv::subtract(dilated, src, exGrad);
    cv::subtract(src, eroded, inGrad);

    cv::imshow("Source Image", image);
    cv::imshow("Basic Grad", basicGrad);
    cv::imshow("Ex Grad", exGrad);
    cv::imshow("In Grad", inGrad);
    cv::waitKey(30000);
    cv::destroyAllWindows();
  }

  TEST_F(Tester, EdgeDetectTest)
  {
    /**
     * 用形态学梯度提取边缘
     * */
    cv::Mat image = cv::imread(filepath_);
    cv::Mat basicGrad, exGrad, inGrad;
    cv::Mat src = image.clone();
    cv::Mat edges, gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::Mat se = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(gray, basicGrad, cv::MORPH_GRADIENT, se);
    cv::threshold(basicGrad, edges, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    cv::imshow("Source Image", image);
    cv::imshow("Basic Grad", basicGrad);
    cv::imshow("Edges", edges);
    cv::waitKey(30000);
    cv::destroyAllWindows();
  }

  TEST_F(Tester, HatTest)
  {
    /**
     * 黑帽与顶帽，用于提取图片中的元素
     *
     * 黑帽: 闭操作结果 - 原图
     * 顶帽: 原图 - 开操作结果
     * morphologyEx的op设置为 MORPH_TOPHAT, MORPH_BLACKHAT
     * */
    cv::Mat image = cv::imread(morphPath_);
    // size越大，能提取的元素越大
    // cv::Mat se = cv::getStructuringElement(cv::MORPH_RECT, size3x3_);
    // cv::Mat se = cv::getStructuringElement(cv::MORPH_RECT, size7x7_);
    cv::Mat se = cv::getStructuringElement(cv::MORPH_RECT, size11x11_);
    cv::Mat gray, binary;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::Mat tophat, blackhat;
    cv::morphologyEx(binary, tophat, cv::MORPH_TOPHAT, se);
    cv::morphologyEx(binary, blackhat, cv::MORPH_BLACKHAT, se);

    cv::imshow("Source Image", image);
    cv::imshow("Tophat", tophat);
    cv::imshow("Blackhat", blackhat);
    cv::waitKey(30000);
    cv::destroyAllWindows();
  }

  TEST_F(Tester, HitTest)
  {
    /**
     * 击中/击不中
     * 实现对象的细化与剪枝
     * */
    cv::Mat image = cv::imread(filepath_);
    cv::Mat binary, gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::Mat se1 = (cv::Mat_<int>(3, 3) << 1, 0, 0, 0, -1, 0, 0, 0, 0);
    cv::Mat se2 = (cv::Mat_<int>(3, 3) << 0, 0, 0, 0, -1, 0, 0, 0, 1);
    cv::Mat h1, h2, result;
    cv::morphologyEx(binary, h1, cv::MORPH_HITMISS, se1);
    cv::morphologyEx(binary, h2, cv::MORPH_HITMISS, se2);
    cv::add(h1, h2, result);
    cv::imshow("Source Image", image);
    cv::imshow("H1", h1);
    cv::imshow("H2", h2);
    cv::imshow("HitMiss", result);
    cv::waitKey(30000);
    cv::destroyAllWindows();
  }

} // namespace cvtest::tester

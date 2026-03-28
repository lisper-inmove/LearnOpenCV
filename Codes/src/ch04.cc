#include "ch04.h"
#include <opencv2/opencv.hpp>

void ch04::ch04Test()
{
    cvMeanTest();
}

/**
 * OpenCV 均值函数
 * Scalar cv::mean (InputArray src, InputArray mask = noArray())
 * @param src 输入图像
 * @param mask 可选掩码
 * @return Scalar 均值向量，包含每个通道的均值，Blue, Green, Red, Alpha
 * @brief 计算图像的均值
 */
void ch04::cvMeanTest()
{
    std::string filepath = "/home/inmove/Desktop/Desktop.jpg";
    cv::Mat image = cv::imread(filepath, cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cerr << "Could not read image: " << filepath << std::endl;
        return;
    }

    cv::Scalar mean = cv::mean(image);
    std::cout << "Mean: " << mean << std::endl;
}

/**
 * OpenCV 均值和标准差函数
 * void cv::meanStdDev (InputArray src, OutputArray mean, OutputArray stddev, InputArray mask = noArray())
 * @brief 计算图像的均值和标准差
 * @details 该函数读取指定路径的图像，计算其每个通道的均值和标准差，并输出结果
 * 均值表示图像像素值的平均水平，标准差表示像素值的离散程度
 */
void ch04::cvMeanStdDevTest()
{
    // 图像文件路径
    std::string filepath = "/home/inmove/Desktop/Desktop.jpg";
    // 读取彩色图像
    cv::Mat image = cv::imread(filepath, cv::IMREAD_COLOR);

    // 检查图像是否成功读取
    if (image.empty())
    {
        std::cerr << "Could not read image: " << filepath << std::endl;
        return;
    }

    // 定义均值和标准差变量
    cv::Scalar mean, std;
    // 计算图像的均值和标准差
    cv::meanStdDev(image, mean, std);
    // 输出均值结果（BGR通道顺序）
    std::cout << "Mean: " << mean << std::endl;
    // 输出标准差结果（BGR通道顺序）
    std::cout << "StdDev: " << std << std::endl;
}

/**
 * OpenCV 直方图计算函数
 * void cv::calcHist(const Mat* images, int nimages, const int* channels, InputArray mask,
 *                   OutputArray hist, int dims, const int* histSize, const float** ranges,
 *                   bool uniform = true, bool accumulate = false)
 * @brief 计算图像的直方图并可视化展示
 * @details 该函数读取指定路径的图像，计算其灰度直方图，并绘制直方图图像进行显示
 * 直方图表示图像中像素强度的分布情况，是图像处理中重要的分析工具
 */
void ch04::cvCalcHistTest()
{
    // 图像文件路径 - 使用绝对路径指向桌面图片
    std::string filepath = "/home/inmove/Desktop/Desktop.jpg";

    // 读取彩色图像
    cv::Mat image = cv::imread(filepath, cv::IMREAD_COLOR);

    // 检查图像是否成功读取
    if (image.empty())
    {
        std::cerr << "错误：无法读取图像文件: " << filepath << std::endl;
        std::cerr << "请确保文件存在且路径正确" << std::endl;
        return;
    }

    // 将彩色图像转换为灰度图像
    // 直方图通常针对单通道图像计算，这里使用灰度图简化分析
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // 定义直方图参数
    int histSize = 256;               // 直方图bin的数量，对应0-255的像素值范围
    float range[] = {0, 256};         // 像素值范围：0到255（256为开区间上限）
    const float *histRange = {range}; // 范围指针，calcHist函数要求的格式

    // 计算灰度直方图
    cv::Mat hist;
    cv::calcHist(&gray,      // 输入图像数组（单个图像）
                 1,          // 图像数量
                 {0},        // 通道索引数组（灰度图只有通道0）
                 cv::Mat(),  // 可选掩码（空矩阵表示使用整个图像）
                 hist,       // 输出的直方图（256x1的浮点矩阵）
                 1,          // 直方图维度（一维直方图）
                 &histSize,  // 每个维度的bin数量
                 &histRange, // 每个维度的取值范围
                 true,       // 直方图是否均匀（等间距bins）
                 false);     // 是否累积（false表示不累积，重新计算）

    // 打印直方图基本信息
    std::cout << "=== 直方图计算完成 ===" << std::endl;
    std::cout << "图像尺寸: " << gray.cols << "x" << gray.rows << std::endl;
    std::cout << "直方图大小（bin数量）: " << hist.total() << std::endl;
    std::cout << "直方图数据类型: " << hist.type() << " (CV_32F)" << std::endl;

    // 打印前10个bin的值（像素值0-9的频率）
    std::cout << "前10个bin的值（像素值0-9）: ";
    for (int i = 0; i < 10 && i < hist.rows; i++)
    {
        std::cout << hist.at<float>(i) << " ";
    }
    std::cout << std::endl;

    // 查找直方图的最大值用于归一化显示
    double maxVal = 0;
    cv::minMaxLoc(hist, nullptr, &maxVal, nullptr, nullptr);
    std::cout << "直方图最大值: " << maxVal << std::endl;

    // 创建直方图可视化图像
    int histWidth = 512;                                  // 直方图图像的宽度
    int histHeight = 400;                                 // 直方图图像的高度
    int binWidth = cvRound((double)histWidth / histSize); // 每个bin的宽度

    // 创建黑色背景的图像用于绘制直方图
    cv::Mat histImage(histHeight, histWidth, CV_8UC3, cv::Scalar(0, 0, 0));

    // 将直方图归一化到图像高度范围内
    cv::Mat normalizedHist;
    cv::normalize(hist, normalizedHist, 0, histImage.rows, cv::NORM_MINMAX);

    // 绘制直方图（使用折线连接每个bin的顶部）
    for (int i = 1; i < histSize; i++)
    {
        // 计算当前bin和前一个bin在图像中的位置
        int x1 = binWidth * (i - 1);
        int y1 = histHeight - cvRound(normalizedHist.at<float>(i - 1));

        int x2 = binWidth * i;
        int y2 = histHeight - cvRound(normalizedHist.at<float>(i));

        // 绘制连接线（使用绿色线条，厚度2像素）
        cv::line(histImage,
                 cv::Point(x1, y1),
                 cv::Point(x2, y2),
                 cv::Scalar(0, 255, 0), // BGR格式：绿色
                 2,                     // 线宽
                 cv::LINE_AA);          // 抗锯齿线条
    }

    // 添加坐标轴和标签
    // 绘制X轴（白色线条）
    cv::line(histImage,
             cv::Point(0, histHeight - 1),
             cv::Point(histWidth - 1, histHeight - 1),
             cv::Scalar(255, 255, 255), 1, cv::LINE_AA);

    // 绘制Y轴（白色线条）
    cv::line(histImage,
             cv::Point(0, 0),
             cv::Point(0, histHeight - 1),
             cv::Scalar(255, 255, 255), 1, cv::LINE_AA);

    // 添加标题文本
    cv::putText(histImage, "Gray Histogram",
                cv::Point(10, 30),
                cv::FONT_HERSHEY_SIMPLEX, 0.7,
                cv::Scalar(255, 255, 255), 2);

    // 添加X轴标签
    cv::putText(histImage, "Pixel Value (0-255)",
                cv::Point(histWidth / 2 - 80, histHeight - 10),
                cv::FONT_HERSHEY_SIMPLEX, 0.5,
                cv::Scalar(255, 255, 255), 1);

    // 添加Y轴标签
    cv::putText(histImage, "Frequency",
                cv::Point(10, histHeight / 2),
                cv::FONT_HERSHEY_SIMPLEX, 0.5,
                cv::Scalar(255, 255, 255), 1);

    // 显示原图和直方图
    // cv::imshow("Original Image", image);
    cv::imshow("Gray Histogram", histImage);

    // 等待按键，0表示无限等待
    std::cout << "按任意键关闭图像窗口..." << std::endl;
    cv::waitKey(0);

    // 关闭所有OpenCV窗口
    cv::destroyAllWindows();

    std::cout << "=== 直方图展示结束 ===" << std::endl;
}

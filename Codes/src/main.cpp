/**
 * @file main.cpp
 * @brief OpenCV示例程序 - 显示图像并应用简单处理
 */

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/**
 * @brief 打印OpenCV版本和构建信息
 */
void printOpenCVInfo() {
    std::cout << "=== OpenCV Information ===" << std::endl;
    std::cout << "OpenCV version: " << CV_VERSION << std::endl;
    std::cout << "OpenCV major version: " << CV_VERSION_MAJOR << std::endl;
    std::cout << "OpenCV minor version: " << CV_VERSION_MINOR << std::endl;
    std::cout << "OpenCV revision: " << CV_VERSION_REVISION << std::endl;

    // 检查是否支持GUI
    std::cout << "GUI support: " << (cv::haveImageReader("test.jpg") ? "Yes" : "No") << std::endl;
    std::cout << "==========================" << std::endl;
}

/**
 * @brief 图像处理示例：灰度转换、模糊、边缘检测
 * @param image 输入图像
 * @return 处理后的图像
 */
cv::Mat processImage(const cv::Mat& image) {
    if (image.empty()) {
        throw std::runtime_error("Cannot process empty image");
    }

    cv::Mat result;
    cv::Mat gray;

    // 转换为灰度图
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // 应用高斯模糊
    cv::Mat blurred;
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 1.5);

    // Canny边缘检测
    cv::Canny(blurred, result, 50, 150);

    return result;
}

/**
 * @brief 主函数
 */
int main(int argc, char** argv) {
    try {
        // 打印OpenCV信息
        printOpenCVInfo();

        // 检查命令行参数
        if (argc < 2) {
            std::cout << "Usage: " << argv[0] << " <image_path>" << std::endl;
            std::cout << "Example: " << argv[0] << " /path/to/image.jpg" << std::endl;
            std::cout << "\nIf no image provided, a test image will be created." << std::endl;

            // 创建测试图像
            std::cout << "\nCreating test image..." << std::endl;
            cv::Mat testImage(480, 640, CV_8UC3, cv::Scalar(100, 150, 200));

            // 在图像上绘制一些形状
            cv::rectangle(testImage, cv::Point(100, 100), cv::Point(300, 200),
                         cv::Scalar(0, 255, 0), 2);
            cv::circle(testImage, cv::Point(400, 300), 50,
                      cv::Scalar(0, 0, 255), -1);
            cv::putText(testImage, "OpenCV Test", cv::Point(50, 50),
                       cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255, 255, 255), 2);

            // 显示原始图像
            cv::imshow("Original Image", testImage);

            // 处理图像
            cv::Mat edges = processImage(testImage);
            cv::imshow("Edge Detection", edges);

            // 等待按键
            std::cout << "Press any key to exit..." << std::endl;
            cv::waitKey(0);

        } else {
            // 读取图像
            std::string imagePath = argv[1];
            std::cout << "Loading image: " << imagePath << std::endl;

            cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
            if (image.empty()) {
                std::cerr << "Error: Could not load image from " << imagePath << std::endl;
                return -1;
            }

            std::cout << "Image loaded successfully!" << std::endl;
            std::cout << "Image size: " << image.cols << " x " << image.rows << std::endl;
            std::cout << "Image channels: " << image.channels() << std::endl;

            // 显示原始图像
            cv::imshow("Original Image", image);

            // 处理图像
            cv::Mat edges = processImage(image);
            cv::imshow("Edge Detection", edges);

            // 保存处理后的图像
            std::string outputPath = "output_edges.jpg";
            cv::imwrite(outputPath, edges);
            std::cout << "Edge detection result saved to: " << outputPath << std::endl;

            // 等待按键
            std::cout << "Press any key to exit..." << std::endl;
            cv::waitKey(0);
        }

        // 销毁所有窗口
        cv::destroyAllWindows();

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}

#include "ch04.h"
#include <opencv2/opencv.hpp>

void ch04::ch04Test()
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

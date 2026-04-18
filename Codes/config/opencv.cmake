message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")

set(OpenCV_DIR "/home/inmove/.opt/opencv-qt/lib/cmake/opencv4")
set(OpenCV_LIB_PATH "/home/inmove/.opt/opencv-qt/lib")

# 查找OpenCV库
find_package(OpenCV REQUIRED)

# 添加头文件路径
include_directories(${OpenCV_INCLUDE_DIRS})

# 打印信息用于调试
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libs: ${OpenCV_LIBS}")
message(STATUS "OpenCV lib path: ${OpenCV_LIB_PATH}")

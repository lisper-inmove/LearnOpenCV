cmake_minimum_required(VERSION 3.16)
project(MyOpenCVProject VERSION 1.0.0 LANGUAGES CXX)

# 设置C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译选项
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # 启用更多警告
    add_compile_options(-Wall -Wextra -Wpedantic)

    # 对于Debug模式，启用调试信息
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
    endif()

    # 对于Release模式，启用优化
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O3 -DNDEBUG)
    endif()
endif()

# 设置OpenCV路径（您自定义的安装路径）
set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../.opt/opencv/lib/cmake/opencv4")
# 如果上面的路径不对，也可以使用绝对路径
# set(OpenCV_DIR "/home/yourusername/.opt/opencv/lib/cmake/opencv4")

# 查找OpenCV库
find_package(OpenCV REQUIRED)

# 打印OpenCV版本信息（用于调试）
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

# 添加可执行文件
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# 添加头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 链接OpenCV库
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
)

# 设置输出目录（可选）
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# 可选：安装规则
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

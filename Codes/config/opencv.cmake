message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")

# 查找OpenCV库
find_package(OpenCV REQUIRED)

# 添加头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 链接OpenCV库
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
)

# 打印信息用于调试
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libs: ${OpenCV_LIBS}")
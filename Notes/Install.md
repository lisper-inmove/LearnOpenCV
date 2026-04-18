# clone
    https://gitee.com/opencv/opencv
    https://gitee.com/Rormen/opencv_contrib
# 安装依赖
    sudo apt install -y \
        build-essential \
        cmake \
        git \
        pkg-config \
        libgtk-3-dev \
        libavcodec-dev \
        libavformat-dev \
        libswscale-dev \
        libv4l-dev \
        libxvidcore-dev \
        libx264-dev \
        libjpeg-dev \
        libpng-dev \
        libtiff-dev \
        libatlas-base-dev \
        gfortran \
        python3-dev \
        python3-numpy \
        libtbbmalloc2 \
        libtbb-dev \
        libdc1394-dev \
        libopenexr-dev \
        libgstreamer-plugins-base1.0-dev \
        libgstreamer1.0-dev
# 安装tool-kit

    https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=24.04&target_type=deb_local

# 编译安装

    1. Ubuntu 24.4
    2. CUDA Driver 13.0
    3. Toolkit: https://developer.nvidia.com/cuda-13-0-0-download-archive?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=24.04&target_type=deb_local
    4. opencv and opencv_contrib 5.0.0

    wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2404/x86_64/cuda-ubuntu2404.pin
    sudo mv cuda-ubuntu2404.pin /etc/apt/preferences.d/cuda-repository-pin-600
    wget https://developer.download.nvidia.com/compute/cuda/12.8.0/local_installers/cuda-repo-ubuntu2404-12-8-local_12.8.0-570.86.10-1_amd64.deb
    sudo dpkg -i cuda-repo-ubuntu2404-12-8-local_12.8.0-570.86.10-1_amd64.deb
    sudo cp /var/cuda-repo-ubuntu2404-12-8-local/cuda-*-keyring.gpg /usr/share/keyrings/
    sudo apt-get update
    sudo apt-get -y install cuda-toolkit-12-8

    cmake -D CMAKE_BUILD_TYPE=RELEASE \
          -D CMAKE_INSTALL_PREFIX=~/opencv_cuda \
          -D CMAKE_CXX_STANDARD=17 \
          -D CMAKE_CXX_STANDARD_REQUIRED=ON \
          -D WITH_CUDA=ON \
          -D WITH_CUDNN=ON \
          -D DBUILD_opencv_cudev=ON \
          -D ENABLE_FAST_MATH=ON \
          -D CUDA_FAST_MATH=ON \
          -D CUDA_ARCH_BIN=8.9 \
          -D CUDA_ARCH_PTX="" \
          -D WITH_CUBLAS=ON \
          -D OPENCV_EXTRA_MODULES_PATH=/home/inmove/nvme1/SourceCodes/opencv_contrib/modules \
          -D BUILD_EXAMPLES=ON \
          -D BUILD_TESTS=OFF \
          -D BUILD_PERF_TESTS=OFF \
          -D OPENCV_GENERATE_PKGCONFIG=ON \
          -D WITH_GTK=ON \
          -D WITH_FFMPEG=ON \
          -D CUDA_CUDA_LIBRARY=/usr/local/cuda-13.2/lib64/stubs/libcuda.so \
          -D CMAKE_CXX_FLAGS="-DCCCL_IGNORE_DEPRECATED_CPP_DIALECT" \
          ..

# 不支持cuda

    cmake -D CMAKE_BUILD_TYPE=RELEASE \
          -D CMAKE_INSTALL_PREFIX=/home/inmove/.opt/opencv \
          -D OPENCV_GENERATE_PKGCONFIG=ON \
          -D WITH_TBB=ON \
          -D BUILD_EXAMPLES=ON \
          -D OPENCV_EXTRA_MODULES_PATH=/home/inmove/nvme1/SourceCodes/opencv_contrib/modules \
          ..

# 支持Qt

    cmake -D CMAKE_BUILD_TYPE=RELEASE \
        -D CMAKE_INSTALL_PREFIX=/home/inmove/.opt/opencv-qt \
        -D OPENCV_GENERATE_PKGCONFIG=ON \
        -D WITH_TBB=ON \
        -D BUILD_EXAMPLES=ON \
        -D CMAKE_PREFIX_PATH="$HOME/nvme1/.Qt/6.11.0/gcc_64" \
        -D WITH_QT=ON \
        -D WITH_GTK=ON \
        -D BUILD_TESTS=OFF \
        -D BUILD_PERF_TESTS=OFF \
        -D OPENCV_GENERATE_PKGCONFIG=ON \
        -D OPENCV_EXTRA_MODULES_PATH=/home/inmove/nvme1/SourceCodes/opencv_contrib/modules \
        ..

# 系统级Qt6开发包

    sudo apt install qt6-base-dev qt6-base-private-dev qt6-core5compat-dev qt6-declarative-dev

    cmake -D CMAKE_BUILD_TYPE=RELEASE \
          -D CMAKE_INSTALL_PREFIX=/home/inmove/.opt/opencv-qt \
          -D WITH_TBB=ON \
          -D WITH_QT=ON \
          -D WITH_GTK=ON \
          -D BUILD_TESTS=OFF \
          -D BUILD_PERF_TESTS=OFF \
          -D OPENCV_GENERATE_PKGCONFIG=ON \
          -D BUILD_opencv_cvv=OFF \
          -D OPENCV_EXTRA_MODULES_PATH=/home/inmove/nvme1/SourceCodes/opencv_contrib/modules \
          ..

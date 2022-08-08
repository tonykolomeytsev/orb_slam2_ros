#!/bin/bash

echo "Installing OpenCV last version ..."
cd ~/catkin_ws/src/orb_slam2_ros/orb_slam2/Thirdparty
git clone --depth 1 --branch 4.4.0 https://github.com/Itseez/opencv.git opencv
git clone --depth 1 --branch 4.4.0 https://github.com/Itseez/opencv_contrib.git opencv_contrib
cd opencv
mkdir build
cd build
cmake \
    -D CMAKE_BUILD_TYPE=RELEASE \
    -D BUILD_TIFF=ON \
    -D WITH_CUDA=OFF \
    -D ENABLE_AVX=OFF \
    -D WITH_OPENGL=OFF \
    -D WITH_OPENCL=OFF \
    -D WITH_IPP=OFF \
    -D WITH_TBB=ON \
    -D BUILD_TBB=ON \
    -D WITH_EIGEN=ON \
    -D WITH_V4L=OFF \
    -D WITH_VTK=OFF \
    -D BUILD_TESTS=OFF \
    -D BUILD_PERF_TESTS=OFF \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_EXTRA_MODULES_PATH=~/catkin_ws/opencv_contrib/modules \
    ..

make -j $(nproc)
make install
ldconfig

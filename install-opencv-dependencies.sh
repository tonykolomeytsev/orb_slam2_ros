#!/bin/bash

opencv_dependencies=(
    libgtk2.0-dev
    libavcodec-dev
    libavformat-dev
    libswscale-dev
    software-properties-common
)

pangolin_dependencies=(
    libglew-dev
    libboost-dev
    libboost-thread-dev
    libboost-filesystem-dev
    ffmpeg
    libavutil-dev
    libpng-dev
)

echo "Installing OpenCV dependencies ..."
apt-get install -y ${opencv_dependencies[@]}

echo "Installing Eigen 3 last version ..."
apt-get install -y libeigen3-dev 


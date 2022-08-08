#!/bin/bash

opencv_dependencies=(
    libgtk2.0-dev
    libavcodec-dev
    libavformat-dev
    libswscale-dev
    software-properties-common
)

echo "Installing OpenCV dependencies ..."
apt-get install -y ${opencv_dependencies[@]}

echo "Installing Eigen 3 last version ..."
apt-get install -y libeigen3-dev 


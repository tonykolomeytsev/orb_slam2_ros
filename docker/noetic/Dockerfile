FROM ros:noetic-ros-core-focal

RUN apt update && \
    apt install -y --no-install-recommends \
    git \
    # build tools
    cmake \
    build-essential \
    ros-noetic-catkin \
    python3-catkin-tools \
    python3-rosdep \
    # build dependencies
    ros-noetic-cv-bridge \
    ros-noetic-image-transport \
    ros-noetic-tf \
    ros-noetic-tf2-geometry-msgs \
    ros-noetic-dynamic-reconfigure

COPY install-package.sh .
RUN ./install-package.sh && rm install-package.sh

FROM ros:melodic

COPY install-opencv-dependencies.sh .
RUN ./install-opencv-dependencies.sh

COPY install-opencv.sh .
RUN ./install-opencv.sh

# Update
RUN apt update
RUN apt-get install software-properties-common apt-utils -y

# Set working directory
WORKDIR /home/ros/src

# Install required ROS packages
RUN apt-get update && \
    apt-get install ros-melodic-cv-bridge ros-melodic-image-transport ros-melodic-tf ros-melodic-tf2-geometry-msgs python-catkin-tools -y

WORKDIR /home/ros

# Install ROS dependencies
RUN rosdep update \
    && rosdep install --from-paths src --ignore-src -r -y

RUN echo "source /opt/ros/melodic/setup.sh" >> ~/.bashrc
RUN echo "source /home/ros/devel/setup.bash" >> /$HOME/.bashrc

CMD "bash"

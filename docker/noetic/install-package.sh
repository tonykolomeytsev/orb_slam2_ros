#!/bin/bash

mkdir -p ~/catkin_ws/src/
cd ~/catkin_ws/
git clone --depth 1 https://github.com/tonykolomeytsev/orb_slam2_ros.git src/orb_slam2_ros

source /opt/ros/noetic/setup.bash
catkin init
catkin_make orb_slam2_ros

echo 'source /opt/ros/noetic/setup.bash' >> ~/.bashrc
echo 'source /root/catkin_ws/devel/setup.bash' >> ~/.bashrc
sed -i 's/#force_color_prompt=yes/force_color_prompt=yes/g' ~/.bashrc

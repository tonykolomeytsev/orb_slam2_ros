#!/bin/bash

rostopic pub /switcher/pose geometry_msgs/Pose "position:
  x: 0
  y: 0
  z: 0
orientation:
  x: 0
  y: 0
  z: 0
  w: 0
"

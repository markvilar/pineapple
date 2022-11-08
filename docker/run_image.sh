#!/usr/bin/bash

# allow containers to communicate with X server
xhost +si:localuser:root

# run image
docker run -it --runtime nvidia --privileged -e DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v /home/martin/data:/data \
    stereolabs/zed:3.8-gl-devel-cuda11.4-ubuntu20.04

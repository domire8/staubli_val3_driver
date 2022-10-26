FROM ros-industrial:core

RUN git clone https://github.com/ros-industrial/staubli.git && \
  mv ./staubli/staubli_resources ./src/ && rm -rf staubli

RUN git clone https://github.com/ros-industrial/staubli_experimental.git && \
  mv ./staubli_experimental/staubli_tx2_90_support ./src/ && rm -rf staubli_experimental

COPY ./staubli_val3_driver ./src/staubli_val3_driver
RUN /bin/bash -c "source /opt/ros/${ROS_DISTRO}/setup.bash; catkin_make"

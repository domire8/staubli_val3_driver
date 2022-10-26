cmake_minimum_required(VERSION 3.0.2)
project(staubli_val3_driver)

find_package(catkin REQUIRED COMPONENTS actionlib control_msgs roscpp trajectory_msgs)

catkin_package(
  CATKIN_DEPENDS actionlib control_msgs roscpp trajectory_msgs
  LIBRARIES action_client
)

include_directories(include
  ${catkin_INCLUDE_DIRS}
)

add_executable(action_client src/action_client.cpp)
install(TARGETS action_client
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

target_link_libraries(action_client ${catkin_LIBRARIES})

if (CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)
  roslaunch_add_file_check(tests/roslaunch_test.xml)
endif()

install(DIRECTORY launch val3
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(FILES README.md DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

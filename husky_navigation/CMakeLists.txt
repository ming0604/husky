cmake_minimum_required(VERSION 3.0.2)
project(husky_navigation)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  nav_msgs
)
catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(gt_2D src/gt_2D.cpp)
target_link_libraries(gt_2D  ${catkin_LIBRARIES})

if (CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)
  roslaunch_add_file_check(launch)
endif()

install(
  DIRECTORY config launch maps
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)


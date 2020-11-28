cmake_minimum_required(VERSION 2.8.3)
project(hallowelt)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  std_srvs
  actionlib
  actionlib_msgs
  message_generation
)

add_action_files(DIRECTORY action FILES Prime.action)

generate_messages(DEPENDENCIES actionlib_msgs std_msgs)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS actionlib actionlib_msgs message_generation message_runtime roscpp rospy std_msgs std_srvs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(service_server src/service_server.cpp)
target_link_libraries(service_server ${catkin_LIBRARIES})

add_executable(service_client src/service_client.cpp)
target_link_libraries(service_client ${catkin_LIBRARIES})

add_executable(action_server src/action_server.cpp)
target_link_libraries(action_server ${catkin_LIBRARIES})

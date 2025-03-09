set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/home/$ENV{USER}/ExternalLib/mavlink/install")

find_package(Git)
find_package(MAVLink)
find_package(rclcpp)

if(MAVLink_FOUND)
    message(STATUS "MAVLink found!")
    set(MAVLINK_FOUND TRUE)
else()
    message(WARNING "MAVLink not found!")
    add_definitions(-DMAVLINK_DISABLED)
    set(MAVLINK_FOUND FALSE)
endif()

if(rclcpp_FOUND)
    message(STATUS "ROS2 found!")
    set(ROS2_FOUND TRUE)
else()
    message(WARNING "ROS2 not found!")
    add_definitions(-DROS2_DISABLED)
    set(ROS2_FOUND FALSE)
endif()


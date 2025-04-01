if(ROS2_FOUND)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
endif()

set(COMM_FILE
    SerialLink.hpp
    SerialLink.cpp
    LinkManager.hpp
    LinkManager.cpp
    LinkInterface.cpp
    LinkInterface.hpp
    RosManager.hpp
    RosManager.cpp
    MAVLinkProtocol.hpp
    MAVLinkProtocol.cpp
)

if(ROS2_FOUND)
    list(APPEND COMM_FILE RosLink.hpp RosLink.cpp)
endif()

add_library(Communication STATIC ${COMM_FILE})

if(ROS2_FOUND)
ament_target_dependencies(Communication
    rclcpp
    std_msgs
    geometry_msgs
    sensor_msgs
)
endif()

target_include_directories(Communication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Communication
                Qt${QT_VERSION_MAJOR}::Core
                Qt${QT_VERSION_MAJOR}::Quick
                Qt${QT_VERSION_MAJOR}::SerialPort
                MAVLink::mavlink
)

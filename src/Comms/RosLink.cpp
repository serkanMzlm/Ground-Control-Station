#include "RosLink.hpp"

ROSLink::ROSLink(QObject *parent) : QObject(parent), Node("ros_link")
{
    pub.point = this->create_publisher<pointMsg>("point", 10);
    pub.button = this->create_publisher<int16Msg>("button", 10);
}

void ROSLink::onButtonChanged(int button_num)
{
    int16Msg msg;
    msg.data = button_num;
    pub.button->publish(msg);
}

void ROSLink::onPointStateChanged(int x, int y)
{
    pointMsg msg;
    msg.x = x;
    msg.y = y;
    msg.z = 0;
    pub.point->publish(msg);
}

ROSLink::~ROSLink()
{
    if (rclcpp::ok())
    {
        rclcpp::shutdown();
    }
}

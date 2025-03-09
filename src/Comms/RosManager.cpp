#include "RosManager.hpp"

RosManager::RosManager(QObject *parent) : QObject{parent}
{
#ifndef ROS2_DISABLED
    _ros2 = std::make_shared<ROSLink>(this);
    connect(this, &RosManager::buttonChanged, _ros2.get(), &ROSLink::onButtonChanged);
    connect(this, &RosManager::pointStateChanged, _ros2.get(), &ROSLink::onPointStateChanged);
#endif
}

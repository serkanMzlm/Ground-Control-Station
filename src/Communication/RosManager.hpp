#ifndef ROS_MANAGER_HPP
#define ROS_MANAGER_HPP

#include <QObject>

#ifndef ROS2_DISABLED
#include "RosLink.hpp"
#endif

class RosManager: public QObject
{
    Q_OBJECT
public:
    explicit RosManager(QObject *parent = nullptr);

private:
#ifndef ROS2_DISABLED
    std::shared_ptr<ROSLink> _ros2;
#endif

signals:
    void buttonChanged(int button_num);
    void pointStateChanged(int x, int y);
};

#endif

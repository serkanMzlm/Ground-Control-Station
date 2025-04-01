#ifndef ROS_LINK_HPP
#define ROS_LINK_HPP

#include <QDebug>
#include <QObject>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int16.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <geometry_msgs/msg/point.hpp>

using joyMsg = sensor_msgs::msg::Joy;
using int16Msg = std_msgs::msg::Int16;
using pointMsg = geometry_msgs::msg::Point;

typedef struct
{
    rclcpp::Publisher<int16Msg>::SharedPtr button;
    rclcpp::Publisher<pointMsg>::SharedPtr point;
} Pub_t;

class ROSLink : public QObject, public rclcpp::Node
{
    Q_OBJECT
public:
    ROSLink(QObject *parent = nullptr);
    ~ROSLink();

public slots:
    void onButtonChanged(int button_num);
    void onPointStateChanged(int x, int y);

private:
    Pub_t pub;
};

#endif
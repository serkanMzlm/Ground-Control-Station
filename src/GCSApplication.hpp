#ifndef GCS_APPLICATION_HPP
#define GCS_APPLICATION_HPP

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "DeviceLink.hpp"
#include "RosManager.hpp"
#include "SerialManager.hpp"

class GCSApplication: public QGuiApplication{
    Q_OBJECT
public:
    explicit GCSApplication(int argc, char** argv);
    void loadQML();
    void commInit();

private:
    QQmlApplicationEngine _engine;
    std::shared_ptr<SerialManager> _port;
};

#endif

#ifndef GCS_APPLICATION_HPP
#define GCS_APPLICATION_HPP

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "SystemDate.hpp"
#include "RosManager.hpp"
#include "LinkManager.hpp"

class GCSApplication: public QGuiApplication{
    Q_OBJECT
public:
    explicit GCSApplication(int argc, char** argv);
    void loadQML();
    void commInit();

private:
    QQmlApplicationEngine _engine;
    std::shared_ptr<LinkManager> _port;
};

#endif

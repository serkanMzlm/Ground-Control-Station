#include <QUrl>
#include <QIcon>
#include <QQmlEngine>
#include <QQmlContext>
#include <QCoreApplication>

#include "GCSApplication.hpp"

GCSApplication::GCSApplication(int argc, char** argv): QGuiApplication(argc, argv)
{
    setWindowIcon(QIcon(":/icons/cpu.ico"));

#ifndef ROS2_DISABLED
    rclcpp::init(argc, argv);
#endif

    _port = std::make_shared<LinkManager>(this);

    commInit();
    loadQML();
}

void GCSApplication::loadQML() {
    const QUrl url(QStringLiteral("qrc:/qml/MainWindow.qml"));

    QObject::connect(&_engine, &QQmlApplicationEngine::objectCreated,
                     this, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    _engine.load(url);
}

void GCSApplication::commInit() {
    QQmlContext *context = _engine.rootContext();

    context->setContextProperty("_LinkManager", _port.get());

    qmlRegisterType<DeviceLink>("GCS.DeviceLink", 1, 0, "DeviceLink");
    qmlRegisterType<RosManager>("GCS.ROSManager", 1, 0, "ROSManager");
}

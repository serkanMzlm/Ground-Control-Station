#include <QIcon>
#include <QDebug>
#include <QQmlContext>
#include <QDirIterator>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "GCSApplication.hpp"

int main(int argc, char *argv[])
{
    GCSApplication app(argc, argv);
    return app.exec();
}

#include "LinkInterface.hpp"

LinkInterface::LinkInterface(QObject *parent)
    : QObject(parent)
{
}

LinkInterface::~LinkInterface()
{
}

void LinkInterface::connectionRemoved()
{
    if (_vehicle_reference_count == 0) {
        disconnectFromPort();
    }
}
#include "SerialManager.hpp"

SerialManager::SerialManager(QObject *parent) : QObject{parent}
{
    initialize();
}

SerialManager::~SerialManager()
{
    _port->disconnectFromPort();
}

void SerialManager::initialize()
{
    _port = std::make_shared<SerialLink>(this);
    _auto_detect_timer = std::make_unique<QTimer>(this);

    connect(_auto_detect_timer.get(), &QTimer::timeout, this, &SerialManager::autoDetectAndConnect);
    connect(_port.get(), &SerialLink::portDisconnected, this, &SerialManager::disconnected);

    _auto_detect_timer->setInterval(1000);
    _auto_detect_timer->start();
}

void SerialManager::showAvailablePorts() const
{
    for (const QSerialPortInfo &port_list : QSerialPortInfo::availablePorts())
    {
        qDebug() << "-----------------------------------------------------";
        qDebug() << "portName:          " << port_list.portName();
        qDebug() << "systemLocation:    " << port_list.systemLocation();
        qDebug() << "description:       " << port_list.description();
        qDebug() << "manufacturer:      " << port_list.manufacturer();
        qDebug() << "serialNumber:      " << port_list.serialNumber();
        qDebug() << "vendorIdentifier:  " << port_list.vendorIdentifier();
        qDebug() << "productIdentifier: " << port_list.productIdentifier();
    }
}

void SerialManager::autoDetectAndConnect()
{
    static int64_t elapsed_ms = 0;
    bool is_device_found = false;

    _elapsed_duration = std::chrono::steady_clock::now() - _last_update_time;
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(_elapsed_duration).count();

    if (elapsed_ms <= (_time_out_coef * _time_out))
    {
        return;
    }

    for (const QSerialPortInfo &port : QSerialPortInfo::availablePorts())
    {
        is_device_found = ((port.manufacturer() == "FTDI") || (port.vendorIdentifier() == 9025));
        if (is_device_found)
        {
            _time_out_coef = 2;
            if (_port->isPortOpen())
            {
                break;
            }

            _port->setPortName(port.portName());
            _port->setBaudrate(_baudrate);
            if (_port->connectToPort())
            {
                if (port.manufacturer() == "FTDI")
                {
                    qDebug() << "Connected with Device [FTDI]";
                }
                else if (port.vendorIdentifier() == 9025)
                {
                    qDebug() << "Connected with Device [9025]";
                }
            }
            else
            {
                qDebug() << "Failed to connect to device: " << port.portName();
            }

            break;
        }
    }
    if (!is_device_found && _port->isPortOpen())
    {
        qDebug() << "Device Connection Lost";
        _time_out_coef = 1;
        _port->disconnectFromPort();
    }

    _last_update_time = std::chrono::steady_clock::now();
}

void SerialManager::refreshAvailablePorts()
{
    QStringList ports;
    const auto serial_port = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : serial_port) {
        ports.append(info.portName());
    }
    emit availablePortsUpdated(ports);
}
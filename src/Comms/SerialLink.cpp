#include "SerialLink.hpp"

SerialLink::SerialLink(QObject *parent) : QObject{parent}
{
    _port = std::make_unique<QSerialPort>(this);
    connect(_port.get(), &QSerialPort::readyRead, this, &SerialLink::readByte);
}

SerialLink::~SerialLink()
{
    disconnectFromPort();
}

void SerialLink::disconnectFromPort()
{
    if (isPortOpen())
    {
        _port->close();
        qDebug() << "Port Disconnect";
        emit portDisconnected();
    }
}

bool SerialLink::connectToPort()
{
    disconnectFromPort();
    _port->setPortName(_port_name);
    _port->setBaudRate(_baudrate);
    _port->setDataBits(QSerialPort::Data8);
    _port->setParity(QSerialPort::Parity::NoParity);
    _port->setStopBits(QSerialPort::StopBits::OneStop);

    if (!_port->open(QIODevice::ReadWrite))
    {
        qCritical() << "Failed to open port:" << _port->errorString();
        return false;
    }

    qDebug() << "Port opened successfully!";
    return true;
}

void SerialLink::readByte()
{
    if (!isPortOpen())
    {
        qWarning() << "Attempted to read data, but port is not open.";
        return;
    }

    while (_port->bytesAvailable())
    {
        uint8_t cur_byte;
        _port->read((char *)&cur_byte, 1);
        emit updateReadByte(cur_byte);
    }
}

void SerialLink::readBytes()
{
    if (!isPortOpen())
    {
        qWarning() << "Attempted to read data, but port is not open.";
        return;
    }

    emit updateReadBytes(_port->readAll());
}

int SerialLink::writeBytes(const QByteArray &data)
{
    if (!isPortOpen())
    {
        qWarning() << "Attempted to write data, but port is not open.";
        return -1;
    }

    return _port->write(data);
}

int SerialLink::writeByte(uint8_t data)
{
    if (!(isPortOpen()))
    {
        qWarning() << "Attempted to write data, but port is not open.";
        return -1;
    }

    char dataToSend[1] = {static_cast<char>(data)};
    qint64 bytesWritten = _port->write(dataToSend, 1);

    if (bytesWritten == -1)
    {
        qWarning() << "Could not write data to port: " << _port->errorString();
        return -1;
    }

    _port->flush();
    return 1;
}

void SerialLink::setPortName(const QString &port_name)
{
    if (QSerialPortInfo::availablePorts().isEmpty())
    {
        qWarning() << "No available serial ports found!";
        return;
    }
    _port_name = port_name;
}
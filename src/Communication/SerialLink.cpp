#include "SerialLink.hpp"

SerialLink::SerialLink(QObject *parent) : LinkInterface{parent}
{
    _port = std::make_unique<QSerialPort>(this);
    connect(_port.get(), &QSerialPort::readyRead, this, &SerialLink::readBytes);
}

SerialLink::~SerialLink()
{
    SerialLink::disconnect();
}

void SerialLink::readBytes()
{
    if (!isConnected())
    {
        qWarning() << "Port is not open.";
        return;
    }

    const QByteArray data = _port->readAll();

    if (!data.isEmpty())
    {
        emit dataReceived(data);
    }
}

void SerialLink::writeBytes(const QByteArray &data)
{
    if (data.isEmpty())
    {
        errorOccurred(tr("Data to Send is Empty"));
        return;
    }

    if (!isConnected())
    {
        errorOccurred(tr("Port is not Connected"));
        return;
    }

    if (!_port->isWritable())
    {
        errorOccurred(tr("Port is not Writable"));
        return;
    }

    qint64 total_bytes_written = 0;
    while (total_bytes_written < data.size())
    {
        const qint64 bytes_written = _port->write(data.constData() + total_bytes_written, data.size() - total_bytes_written);
        if (bytes_written == -1)
        {
            errorOccurred(tr("Could Not Send Data - Write Failed: %1").arg(_port->errorString()));
            return;
        }
        else if (bytes_written == 0)
        {
            errorOccurred(tr("Could Not Send Data - Write Returned 0 Bytes"));
            return;
        }
        total_bytes_written += bytes_written;
    }

    const QByteArray sent = data.first(total_bytes_written);
    emit dataSent(sent);
}

void SerialLink::connectToPort()
{
    if (isConnected())
    {
        errorOccurred("Already connected to" + _port->portName());
        return;
    }

    _port->setPortName(_port_name);

    if (!_port->open(QIODevice::ReadWrite))
    {
        errorOccurred("Failed to open port " + _port->portName());
        return;
    }

    _onPortConnected();
    qDebug() << "Port opened successfully!";
}

void SerialLink::disconnectFromPort()
{
    if (!isConnected())
    {
        qDebug() << "Already disconnected from port";
        return;
    }

    qDebug() << "Attempting to close port:" << _port->portName();
    _port->close();
    emit disconnected();
}

bool SerialLink::isConnected() const
{
    return (_port && _port->isOpen());
}

void SerialLink::setBaud(qint32 baud)
{
    if (baud != _baud)
    {
        _baud = baud;
        emit baudChanged();
    }
}

void SerialLink::setDataBits(QSerialPort::DataBits databits)
{
    if (databits != _data_bits)
    {
        _data_bits = databits;
        emit dataBitsChanged();
    }
}
void SerialLink::setFlowControl(QSerialPort::FlowControl flow_control)
{
    if (flow_control != _flow_control)
    {
        _flow_control = flow_control;
        emit flowControlChanged();
    }
}
void SerialLink::setStopBits(QSerialPort::StopBits stop_bits)
{
    if (stop_bits != _stop_bits)
    {
        _stop_bits = stop_bits;
        emit stopBitsChanged();
    }
}
void SerialLink::setParity(QSerialPort::Parity parity)
{
    if (parity != _parity)
    {
        _parity = parity;
        emit parityChanged();
    }
}

void SerialLink::setPortName(const QString &name)
{
    if (QSerialPortInfo::availablePorts().isEmpty())
    {
        qWarning() << "No available serial ports found!";
        return;
    }

    const QString port_name = name.trimmed();
    if (port_name.isEmpty())
    {
        return;
    }

    if (port_name != _port_name)
    {
        _port_name = port_name;
        emit portNameChanged();
    }

    const QString port_display_name = cleanPortDisplayName(port_name);
    setPortDisplayName(port_display_name);
}

void SerialLink::setPortDisplayName(const QString &port_display_name)
{
    if (port_display_name != _port_display_name)
    {
        _port_display_name = port_display_name;
        emit portDisplayNameChanged();
    }
}

void SerialLink::setBoard(QString board)
{
    if(_board != board)
    {
        _board = board;
    }
}

QStringList SerialLink::supportedBaudRates()
{
    QStringList support_baud_rate_strings;

    const QList<qint32> rates = QSerialPortInfo::standardBaudRates();
    for (qint32 rate : rates)
    {
        support_baud_rate_strings.append(QString::number(rate));
    }

    return support_baud_rate_strings;
}

QString SerialLink::cleanPortDisplayName(const QString &name)
{
    const QList<QSerialPortInfo> available_ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port_info : available_ports)
    {
        if (port_info.systemLocation() == name)
        {
            return port_info.portName();
        }
    }

    return QString();
}

void SerialLink::_onPortConnected()
{
    qDebug() << "Port connected:" << _port->portName();

    _port->setDataTerminalReady(true);
    _port->setBaudRate(_baud);
    _port->setDataBits(_data_bits);
    _port->setFlowControl(_flow_control);
    _port->setStopBits(_stop_bits);
    _port->setParity(_parity);

    emit connected();
}

void SerialLink::_checkPortAvailability()
{
    if (!isConnected())
    {
        return;
    }

    const auto available_ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : available_ports)
    {
        if (info.portName() == portDisplayName())
        {
            _port->close();
            break;
        }
    }
}

void SerialLink::_onErrorOccurred(const QString &errorString)
{
    qWarning() << "Communication error:" << errorString;
}

#ifndef SERIAL_LINK_HPP
#define SERIAL_LINK_HPP

#include <QDebug>
#include <QTimer>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialLink : public QObject
{
    Q_OBJECT
public:
    explicit SerialLink(QObject *parent = nullptr);
    ~SerialLink();

    void readByte();
    void readBytes();

    int writeByte(uint8_t data);
    int writeBytes(const QByteArray &data);

    void disconnectFromPort();
    bool connectToPort();

    void setPortName(const QString &port_name);
    void setBaudrate(int baudrate) { _baudrate = baudrate; };
    bool isPortOpen() const { return _port->isOpen(); };

private:
    std::unique_ptr<QSerialPort> _port;
    QString _port_name = "";
    int _baudrate = 115200;

signals:
    void portDisconnected();
    void updateReadByte(uint8_t data);
    void updateReadBytes(const QByteArray &data);
};

#endif

#ifndef SERIAL_LINK_HPP
#define SERIAL_LINK_HPP

#include <QDebug>
#include <QTimer>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "LinkInterface.hpp"

class SerialLink : public LinkInterface
{
    Q_OBJECT
    Q_PROPERTY(qint32 baud READ baud WRITE setBaud NOTIFY baudChanged)
    Q_PROPERTY(QSerialPort::DataBits dataBits READ dataBits WRITE setDataBits NOTIFY dataBitsChanged)
    Q_PROPERTY(QSerialPort::FlowControl flowControl READ flowControl WRITE setFlowControl NOTIFY flowControlChanged)
    Q_PROPERTY(QSerialPort::StopBits stopBits READ stopBits WRITE setStopBits NOTIFY stopBitsChanged)
    Q_PROPERTY(QSerialPort::Parity parity READ parity WRITE setParity NOTIFY parityChanged)
    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)
    Q_PROPERTY(QString portDisplayName READ portDisplayName NOTIFY portDisplayNameChanged)
public:
    explicit SerialLink(QObject *parent = nullptr);
    ~SerialLink();

    bool isConnected() const override;
    void connectToPort() override;
    void disconnectFromPort() override;

    void readBytes();
    void writeBytes(const QByteArray &data) override;

    qint32 baud() const { return _baud; };
    QSerialPort::DataBits dataBits() const { return _data_bits; }
    QSerialPort::FlowControl flowControl() const { return _flow_control; }
    QSerialPort::StopBits stopBits() const { return _stop_bits; }
    QSerialPort::Parity parity() const { return _parity; }
    QString portName() const { return _port_name; }
    QString portDisplayName() const { return _port_display_name; }

    void setBaud(qint32 baud);
    void setDataBits(QSerialPort::DataBits databits);
    void setFlowControl(QSerialPort::FlowControl flow_control);
    void setStopBits(QSerialPort::StopBits stop_bits);
    void setParity(QSerialPort::Parity parity);
    void setPortName(const QString &name);
    void setPortDisplayName(const QString &port_display_name);
    void setBoard(QString board);

    static QStringList supportedBaudRates();
    static QString cleanPortDisplayName(const QString &name);

private slots:
    void _onPortConnected();
    void _checkPortAvailability();
    void _onErrorOccurred(const QString &errorString);

signals:
    void connected();
    void disconnected();
    void dataReceived(const QByteArray &data);
    void dataSent(const QByteArray &data);
    void errorOccurred(const QString &errorString);

    void baudChanged();
    void dataBitsChanged();
    void flowControlChanged();
    void stopBitsChanged();
    void parityChanged();
    void portNameChanged();
    void portDisplayNameChanged();
    void usbDirectChanged();

private:
    std::unique_ptr<QSerialPort> _port;
    qint32 _baud = QSerialPort::Baud115200;
    QSerialPort::DataBits _data_bits = QSerialPort::Data8;
    QSerialPort::FlowControl _flow_control = QSerialPort::NoFlowControl;
    QSerialPort::StopBits _stop_bits = QSerialPort::OneStop;
    QSerialPort::Parity _parity = QSerialPort::NoParity;
    QString _port_name;
    QString _port_display_name;
    QString _board;
};

#endif

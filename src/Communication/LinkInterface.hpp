#ifndef LINK_INTERFACE_HPP
#define LINK_INTERFACE_HPP

#include <QObject>

class LinkInterface: public QObject
{
    Q_OBJECT
public:
    virtual ~LinkInterface();
    Q_INVOKABLE virtual void connectToPort() = 0;
    Q_INVOKABLE virtual void disconnectFromPort() = 0;
    virtual bool isConnected() const = 0;
    void addVehicleReference() { ++_vehicle_reference_count; }
    void removeVehicleReference();

protected:
    explicit LinkInterface(QObject *parent = nullptr); 
    void connectionRemoved();

signals:
    void bytesReceived(LinkInterface *link, const QByteArray &data);
    void bytesSent(LinkInterface *link, const QByteArray &data);

public slots:
    virtual void writeBytes(const QByteArray &bytes) = 0; 

private:
    int _vehicle_reference_count = 0;
};

#endif
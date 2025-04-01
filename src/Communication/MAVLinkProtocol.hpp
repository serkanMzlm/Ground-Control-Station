#ifndef __MAVLINK_PROTOCOL_HPP
#define __MAVLINK_PROTOCOL_HPP

#include <QDebug>
#include <QObject>

#include "mavlink/common/mavlink.h"

class MAVLinkProtocol : public QObject
{
    Q_OBJECT
public:
    explicit MAVLinkProtocol(QObject *parent = nullptr);
    int getSystemId() const { return _system_id; }
    static int getVersion() { return MAVLINK_VERSION; }
    void processMAVLinkMessage(const mavlink_message_t &msg);
    void handleHeartbeat(const mavlink_message_t &msg);
    void handleGlobalPosition(const mavlink_message_t &msg);
    void handleParamValue(const mavlink_message_t &msg);
    QByteArray sendHeartbeatMessage();
    QByteArray send(mavlink_message_t &msg);

public slots:
    void messageReceived(QByteArray data);
private:
    const int _system_id{255};
    const int _component_id{1};
};

#endif

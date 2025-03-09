#include "MAVLinkProtocol.hpp"

MAVLinkProtocol::MAVLinkProtocol(QObject *parent) : QObject(parent)
{
}

void MAVLinkProtocol::processMAVLinkMessage(const mavlink_message_t &msg)
{
    switch (msg.msgid)
    {
    case MAVLINK_MSG_ID_HEARTBEAT:
        handleHeartbeat(msg);
        break;

    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
        handleGlobalPosition(msg);
        break;

    case MAVLINK_MSG_ID_PARAM_VALUE:
        handleParamValue(msg);
        break;

    default:
        qDebug() << "Unknown message ID:" << msg.msgid;
        break;
    }
}

void MAVLinkProtocol::handleHeartbeat(const mavlink_message_t &msg)
{
    mavlink_heartbeat_t heartbeat;
    mavlink_msg_heartbeat_decode(&msg, &heartbeat);
}

void MAVLinkProtocol::handleGlobalPosition(const mavlink_message_t &msg)
{
    mavlink_global_position_int_t global_position;
    mavlink_msg_global_position_int_decode(&msg, &global_position);
}

void MAVLinkProtocol::handleParamValue(const mavlink_message_t &msg)
{
    mavlink_param_value_t param_value;
    mavlink_msg_param_value_decode(&msg, &param_value);
}

QByteArray MAVLinkProtocol::sendHeartbeatMessage()
{
    mavlink_heartbeat_t hb{};
    hb.type = MAV_TYPE_GENERIC;
    hb.autopilot = MAV_AUTOPILOT_GENERIC;
    hb.base_mode = 0;
    hb.custom_mode = 0;
    hb.system_status = MAV_STATE_STANDBY;
    hb.mavlink_version = MAVLINK_VERSION;

    mavlink_message_t msg;
    mavlink_msg_heartbeat_encode(_system_id, _component_id, &msg, &hb);

    return send(msg);
}

QByteArray MAVLinkProtocol::send(mavlink_message_t &msg)
{
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buf, &msg);

    QByteArray data(reinterpret_cast<const char *>(buf), len);

    return data;
}

void MAVLinkProtocol::messageReceived(QByteArray data)
{
    mavlink_message_t msg;
    mavlink_status_t status;

    for (const auto &byte : data) {
        if (mavlink_parse_char(MAVLINK_COMM_0, static_cast<uint8_t>(byte), &msg, &status)) {
            processMAVLinkMessage(msg);
        }
    }
}

#ifndef SERIAL_MANAGER_HPP
#define SERIAL_MANAGER_HPP

#include "SerialLink.hpp"

class SerialManager : public QObject
{
    Q_OBJECT
public:
    explicit SerialManager(QObject *parent = nullptr);
    ~SerialManager();

    void initialize();

    void showAvailablePorts() const;
    void autoDetectAndConnect();
    
    Q_INVOKABLE void refreshAvailablePorts();

    int getTargetDevice() const { return _target_device; }
    void setTargetDevice(int new_device) { _target_device = new_device; }
signals:
    void disconnected();
    void connected(int device);
    void availablePortsUpdated(const QStringList &ports);

private:
    unsigned int _time_out{1000}; // ms
    unsigned int _time_out_coef{1};

    int _baudrate{115200};
    int _target_device{0};

    std::chrono::steady_clock::time_point _last_update_time;
    std::chrono::steady_clock::duration _elapsed_duration;

    std::shared_ptr<SerialLink> _port;
    std::unique_ptr<QTimer> _auto_detect_timer;
};

#endif

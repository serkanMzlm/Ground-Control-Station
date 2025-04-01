#include "SystemDate.hpp"

SystemDate::SystemDate(QObject *parent) : QObject{parent}
{
    _current_time = std::time(nullptr);
    setDate("01.01.2025 00:00");

    connect(&_timer, &QTimer::timeout, this, &SystemDate::update);
    _timer.start(1000);
}

SystemDate::~SystemDate()
{
    delete _local_time;
}

void SystemDate::update()
{
    _local_time = std::localtime(&_current_time);
    QString formatted = QString("%1.%2.%3 %4:%5")
                                    .arg(_local_time->tm_mday, 2, 10, QChar('0'))
                                    .arg(_local_time->tm_mon + 1, 2, 10, QChar('0'))
                                    .arg(_local_time->tm_year + 1900)
                                    .arg(_local_time->tm_hour, 2, 10, QChar('0'))
                                    .arg(_local_time->tm_min, 2, 10, QChar('0'));

    setDate(formatted);
}

void SystemDate::setDate(const QString &new_date)
{
    if (m_date == new_date)
    {
        return;
    }

    m_date = new_date;
    emit dateChanged();
}

QString SystemDate::date() const
{
    return m_date;
}

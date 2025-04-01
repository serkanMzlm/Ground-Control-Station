#ifndef SYSTEM_DATE_HPP
#define SYSTEM_DATE_HPP

#include <QObject>
#include <QTimer>
#include <QDebug>

class SystemDate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged FINAL)

public:
    explicit SystemDate(QObject *parent = nullptr);
    ~SystemDate();
    QString date() const;
    void setDate(const QString &new_date);

private:
    QString m_date;
    std::tm *_local_time;
    std::time_t _current_time;
    QTimer _timer;

signals:
    void dateChanged();

public slots:
    void update();
};

#endif

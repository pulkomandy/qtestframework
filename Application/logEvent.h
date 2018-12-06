#ifndef LOGEVENT_H
#define LOGEVENT_H

#include <QObject>
#include <QDateTime>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QUdpSocket>

enum Level
{
    Emergency = 0,
    Alert = 1,
    Critical = 2,
    Error = 3,
    Warning = 4,
    Notice = 5,
    Information = 6,
    Debug = 7,
    Trace = 8,
};

/// <summary>
/// facility from where a message comes from
/// </summary>
enum Facility
{
    Kernel = 0,
    User = 1,
    Mail = 2,
    Daemon = 3,
    Auth = 4,
    Syslog = 5,
    Lpr = 6,
    News = 7,
    UUCP = 8,
    Clock = 9,
    Auth2 = 10,
    FTP = 11,
    NTP = 12,
    LogAudit = 13,
    LogAlert = 14,
    Clock2 = 15,
    Local0 = 16,
    Local1 = 17,
    Local2 = 18,
    Local3 = 19,
    Local4 = 20,
    Local5 = 21,
    Local6 = 22,
    Local7 = 23
};

class logEvent : public QObject
{
    Q_OBJECT


public:
    explicit logEvent(QObject *parent = 0);
    static logEvent* getInstance();

    ~logEvent();

    void sendLogMessage(Level _level, Facility _facility, QString _message );
    void setEnable(bool val);
    void setSyslogIp(QString _syslogIp);
    void setSyslogPort(quint16 _syslogPort);
    void setLogLevel(Level _logLevel);

private:
    QByteArray constructMessage(Level _level, Facility _facility, QString _message);
    void writeMessage(QByteArray _trame);

private:
    Level m_logLevel;
    QHostAddress m_syslogip;
    quint16 m_syslogport;
    bool m_logStarted;

    QUdpSocket* m_udpSocket;
};

#endif // LOGEVENT_H

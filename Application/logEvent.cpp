//!
//! \brief   class gestion des log fichier et/ou syslog
//!
//! \brief   Auteur : F.Cheminade
//! \brief   Date   : 04/2016
//! \brief   Vers   : 0.0.1
//!
//!
//!

#include "logEvent.h"


logEvent::logEvent(QObject *parent)
    : QObject(parent)
{
    m_syslogport = 514;
    m_syslogip = QHostAddress::LocalHost;
    m_logStarted = false;
    m_logLevel = Debug;

    m_udpSocket = new QUdpSocket();
}

logEvent::~logEvent(){

}

logEvent *logEvent::getInstance()
{
   static logEvent *instance = 0;
   if (!instance)
   {
      instance = new logEvent();
   }
   return instance;
}

void logEvent::setEnable(bool val)
{
    m_logStarted = val;
}

void logEvent::setSyslogIp(QString _syslogIp)
{
    m_syslogip = _syslogIp != "" ? QHostAddress(_syslogIp) : m_syslogip;
}

void logEvent::setSyslogPort(quint16 _syslogPort)
{
    m_syslogport= _syslogPort>0 ? _syslogPort:m_syslogport;
}

void logEvent::setLogLevel(Level _logLevel)
{
    m_logLevel = _logLevel;
}

void logEvent::sendLogMessage(Level _level,Facility _facility, QString _message )
{
   if(m_logStarted)
   {
      if(_level <= m_logLevel)
      {
         writeMessage(constructMessage((Level) _level,_facility,_message));
      }
      else
      {
         qDebug() << _message;
      }
   }
}


QByteArray logEvent::constructMessage(Level _level, Facility _facility, QString _message)
{
    static int i = 0;
    QByteArray result;
    int prival = ((int)_facility) * 8 + ((int)_level);
    QString pri = QString("<%1>1").arg(prival); //+1 Version protocole
    QDateTime DT =  QDateTime::currentDateTime();
    QString timestamp = DT.toString("HH:mm:ss.zzz");
    QString appName = QCoreApplication::applicationName();
    QString header = QString("%1 %2 %3 %4 ").arg(pri).arg(timestamp).arg(i++).arg(appName);
    result.append(header);
    result.append(_message);
    return result;
}

void logEvent::writeMessage(QByteArray _trame){
    Q_UNUSED(_trame);
    m_udpSocket->writeDatagram(_trame,m_syslogip,m_syslogport);
}

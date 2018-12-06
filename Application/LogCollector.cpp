#include "logEvent.h"

namespace LogCollector {

// Handler for Qt log messages that sends output to syslog.
static void SyslogMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	Q_UNUSED(context)

	Level level = Trace;

	QByteArray localMsg = msg.toLocal8Bit();
	switch (type) {
		case QtDebugMsg:
			level = Debug;
			break;
		case QtInfoMsg:
			level = Information;
			break;
		case QtWarningMsg:
			level = Warning;
			break;
		case QtCriticalMsg:
			level = Critical;
			break;
		case QtFatalMsg:
			level = Alert;
	}

	logEvent::getInstance()->sendLogMessage(level, Local2, localMsg.constData());

	if (level < Critical)
		abort();
}


// Handler that sends properly formated logs to the console.
static void ConsoleMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	Q_UNUSED(context)

	const char* header;
	switch (type) {
		case QtDebugMsg:
			header = "D: ";
			break;
		case QtInfoMsg:
			header = "\x1B[1mI: ";
			break;
		case QtWarningMsg:
			header = "\x1B[33mW: ";
			break;
		case QtCriticalMsg:
			header = "\x1B[31mC: ";
			break;
		case QtFatalMsg:
			header = "\x1B[31;1mF: ";
			break;
	}

	QStringList lines = msg.split('\n');
	QString date = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");

	for (QString& line: lines)
	{
		fprintf(stderr, "%s %s %s\x1B[0m\n", qPrintable(date), header, qPrintable(line));
	}

	if (type == QtFatalMsg)
		abort();
}


void LogToSyslog(QString serverAddress)
{
	logEvent::getInstance()->setEnable(true);
	logEvent::getInstance()->setSyslogIp(serverAddress);
	qInstallMessageHandler(SyslogMessageHandler);
}


void LogToConsole()
{
	qInstallMessageHandler(ConsoleMessageHandler);
}


};

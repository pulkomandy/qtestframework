#include <QDebug>

#include "Application.h"

#include "LogCollector.h"


ExampleApplication::ExampleApplication(int& argc, char* argv[])
	: QCoreApplication(argc, argv)
{
	// Install the logger
	LogCollector::LogToConsole();
}


/* Copyright 2012-2018, Viveris Technologies.
 * This program is distributed under the MIT licence.
 */

/** Test harness and entry point for running the tests.
 *
 * The Qt test framework is designed so each test class is run in its own executable. This is nice
 * in principle (it provides isolation of the tests, avoiding a depedency between them or other
 * hard to debug problems), but it makes it difficult to collect and analyze the results.
 *
 * This file provides a test harness that will run each test (in a separate process) and collect
 * the results to build a global XML report file. The report can then be parsed to generate
 * something user readable and give a clear overview of the test status.
 */


#include "Harness.h"

#include <QDebug>
#include <QHash>
#include <QProcess>
#include <QTest>

#include <iostream>



Harness::Harness(const char* appName, QString filename)
	: QObject()
	, fAppName(appName)
	, fOutputFile(filename)
	, fOutput(&fOutputFile)
{
	fOutputFile.open(QIODevice::WriteOnly);
	fOutput << "<Report>\n";
}


Harness::~Harness()
{
	fOutput << "</Report>\n";
}


void
Harness::RunTest(QString testName)
{
	fOutput << "<TestCase name=\"" << testName << "\">\n";

	QStringList args;
	args << testName;
	args << "-lightxml";

	QProcess proc;
	connect(&proc, SIGNAL(readyRead()), this, SLOT(ProcessTestOutput()));
	proc.setReadChannel(QProcess::StandardOutput);
	proc.start(fAppName, args);
	// TODO we could paralellize test executions here
	proc.waitForFinished();

	fOutput << "</TestCase>\n";
}


void
Harness::ProcessTestOutput()
{
	// Get the currently running process
	QProcess* process = static_cast<QProcess*>(sender());

	QByteArray line;
	for (;;)
	{
		line = process->readLine();
		if (line.isEmpty())
			return;

		fOutput << line;
	}
}


static QHash<QString, const QMetaObject*> allTests;


void registerTest(const QMetaObject& meta)
{
	allTests.insert(meta.className(), &meta);
}


int
main(int argc, char* argv[])
{
	if (argc == 1)
	{
		Harness harness(argv[0], "testresults.xml");

		// Run without arguments: run all tests in subprocesses
		for(auto testName: allTests.keys())
		{
			harness.RunTest(testName);
		}
	} else {
		if (strcmp(argv[1], "--list") == 0)
		{
			// List all registered tests
			for(auto i: allTests.keys())
			{
				qDebug() << i;
			}

			return 0;
		}

		QCoreApplication app(argc, argv);
			// Some tests may need it.

		const QMetaObject* meta = allTests.value(argv[1]);

		if (meta == NULL) {
			std::cerr << argv[1] << " is not a valid test name." << std::endl;
			return 1;
		}

		// Run with a test case name (and possibly more args): run the test directly
		QTest::qExec(meta->newInstance(), argc - 1, argv + 1);
	}
	return 0;
}

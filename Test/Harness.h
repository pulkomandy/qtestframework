/* Copyright 2012-2018, Viveris Technologies.
 * This program is distributed under the MIT licence.
 */

#pragma once


#include <QFile>
#include <QMetaObject>
#include <QObject>
#include <QTextStream>


class Harness: public QObject
{
		Q_OBJECT

	public:
					Harness(const char* appName, QString filename);
					~Harness();

		void		RunTest(QString testName);

	public slots:
		void		ProcessTestOutput();

	private:
		QString		fAppName;
		QFile		fOutputFile;
		QTextStream	fOutput;
};


/** This function registers a meta-object, which we can later use to create test instances */
void registerTest(const QMetaObject& meta);


/** We want each test to register itself, by calling the function above when the program starts.
 * We do this by instanciating the template below and creating an instance of it. This calls the
 * constructor, which does the job.
 */
template <class T>
class Test
{
	public:
		Test(const QMetaObject& meta) {
			registerTest(meta);
		}
};


/** And since we want this to be easy on people writing tests, we define a macro to hide the mess.
 */

#define REGISTER_TEST(class) static Test<class> t(class::staticMetaObject);

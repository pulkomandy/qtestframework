#QTestFrameWork

A test framework and harness for Qt.

Copyright 2016-2018, Viveris Technologies

Why is it needed?
=================

Qt provides the QTest framework for writing unit tests. This works well for writing a single unit
test, but it is not a complete framework. This project builds on top of it to provide:
- Running multiple tests in one go
- Single-line registration of tests in their own sourcefiles (no global test list to manage, no
  painful boilerplate code to add everywhere)
- Listing available tests
- Running each test as a separate process, to avoid interferences between them. Yet, build all tests
  in a single executable file with self-contained test harness (no perl, bash or python needed).
- Generate an HTML report from Qt's XML output, allowing to easily glance at the test results

How to use it?
==============

The test code is located in the "Test" directory. Other files (in "Sources") are just there to show
something to be tested.

Preparing your sources
----------------------

The philosophy here is "test what you deploy". As a result, the test framework expects the code to
test to be available as a static library. This way, it tests the exact same object code you will use
in production.

The single drawback to this is that the static lib should not have a main function, so the main
application must be a separate file. This makes sense, as the application should just be plugging
the components together to get things working. There will be nothing relevant to test there.

To keep things manageable, a "common.pri" qmakefile defines everything shared between the different
parts, so you don't need to repeat yourself too much.

It may be possible to integrate the test harness in your buildsystem even if it's designed in a
different way, let us know what you achieve.

Creating a test
---------------

You create a test the usual Qt way. Source filename must end in \_T.cpp. You then use REGISTER\_TEST
to register the test with the framework, so it can be listed and run automatically.

The sourcefile should of course be added to the list of sources in the Test.pro qmake file.

Running tests
-------------

"make check" will run all tests and generate an HTML report (testresults.html).

You can also manually run the test executable and specify the --list option (to list available
tests) or specify a test name to run. The usual QTest arguments are also accepted (to select the
report format, etc).

Checking the results
--------------------

The HTML report includes passed tests and debug messages (white), failed (green), and all warning
messages from qwarn (yellow). When relevant, filename and line numbers are also shown. The result
also shows the data tag (as the same test can be run on multiple data sources), the test description,
and the test duration for reference.

Each test gets a separate table with a header, making it easier to locate what you're after.

Use of qdebug and qwarn in your code will help locate problems when a test fails. And they will help
when debugging in other situations, as well, since they are the general logging framework. When
running in non-batch mode (a single test at a time), they will get to standard output.

How does it works?
=================

Running the tests
-----------------

All the fun happens in Test/Harness.cpp. This is a typical command-line application.
It will run each test by executing itself using QProcess, making sure the outcome of one test does
not impact any other. It will then put the results together in the output XML file.

When run for executing a test, the harness takes care of creating a QCoreApplication, in case the
tests need it. This allows each test to run without too much setup and teardown.

Collecting the tests to run
---------------------------

The REGISTER\_TEST macro declares a static class instance, and uses QMetaObject to then register
the given class as a test to run. Eventually the tests are stored in an hashmap, nothing too fancy.

Generating the html report
--------------------------

XSLT is great. xsltproc is used with Test/report.xsl to turn Qt HTML report into a nice HTML file
(styling is quite minimal, but does the job).

Getting "make check" to do the right thing
------------------------------------------

For the test harness to be run, we declare it as a testcase using CONFIG += testcase in its QMakeFile.
We need to do this a single time, as all tests are run by the same executable. The QTest framework
would expect us to add a separate directory and pro file for each test case, this is not acceptable.

The XSLT report generation is injected into the makefile using check.commands += ...

What's missing?
===============

Mocks
-----

There does not need to be specific support for them. Architecture your C++ code taking care about
testability, separation of concerns and dependency injection, and you should be fine. If you need
a complicated mock framework, it means your code is not architectured the right way.

Make clean
----------

make clean does not delete the generated xml and html reports.

css
---

The html report does the job, but does not look very nice. Want to play with css to make it look
awesome and easier to navigate when there are lots of tests?

Bonus material
==============

Also included is a custom Qt logger that can send data to syslog (locally or on another machine)
through UDP, and to the console with fancy colors and timestamps. This makes qDebug, qWarning and
friends a lot more interesting to use, even outside of the test framework.

The test application just does some silly math things to show how to use the test harness.

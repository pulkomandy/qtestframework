/* Copyright 2012-2018, Viveris Technologies.
 * This program is distributed under the MIT licence.
 */

#include "Harness.h"

#include "Sqrt_T.h"
#include "sqrt.h"

TestSqrt::TestSqrt()
	: QObject()
{
}

void
TestSqrt::init()
{
}

void TestSqrt::cleanup()
{
}

void TestSqrt::SquarePositive_data()
{
	QTest::addColumn<double>("input");
	QTest::addColumn<double>("output");

	QTest::newRow("four") << 4.0 << 2.0;
	QTest::newRow("two")  << 2.0 << 1.414;
	QTest::newRow("nine") << 9.0 << 3.0;
}

void TestSqrt::SquarePositive()
{
	QFETCH(double, input);
	QFETCH(double, output);
	QCOMPARE(squareRoot(input), output);
}

void TestSqrt::SquareNegative()
{
	QCOMPARE(squareRoot(-1.0), nan("-1"));
}


// Register this test with the framework.
REGISTER_TEST(TestSqrt);

/* Copyright 2012-2018, Viveris Technologies.
 * This program is distributed under the MIT licence.
 */

#include "Harness.h"

#include "Primes_T.h"
#include "primes.h"


/* Constructor (run once) and init/cleanup functions (run before and after each test) */


TestPrimes::TestPrimes()
	: QObject()
{
}


void
TestPrimes::init()
{
}


void TestPrimes::cleanup()
{
}


/* Here comes the test functions to be called */


void TestPrimes::IsPrime()
{
	QVERIFY(isPrime(2));
	QVERIFY(isPrime(3));
	QVERIFY(!isPrime(4));
}


void TestPrimes::NextPrime()
{
	int i = 1;
	i = nextPrime(i);
	QCOMPARE(i, 2);
	i = nextPrime(i);
	QCOMPARE(i, 3);
	i = nextPrime(i);
	QCOMPARE(i, 5);
}


// Register this test with the framework.
REGISTER_TEST(TestPrimes);

/* Copyright 2012-2018, Viveris Technologies.
 * This program is distributed under the MIT licence.
 */

#include <QDebug>

#include <math.h>

bool isPrime(int i)
{
	for (int k = 2; k <= sqrt(i); k++) {
		if (i % k == 0) {
			qDebug() << i << "is divisible by " << k;
			return false;
		}
	}

	return true;
}

int nextPrime(int i)
{
	for (;;) {
		i++;
		if (isPrime(i))
			return i;
		qDebug() << i << "is not prime";
	}
}

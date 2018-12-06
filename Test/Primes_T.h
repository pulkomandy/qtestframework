/* Copyright 2012-2018, Viveris Technologies.
 * This program is distributed under the MIT licence.
 */

#pragma once

#include "primes.h"

#include <QtTest/QtTest>


class TestPrimes: public QObject
{
	Q_OBJECT

	public:
		Q_INVOKABLE TestPrimes();

	private slots:
		void init();
		void cleanup();

		void IsPrime();
		void NextPrime();
};

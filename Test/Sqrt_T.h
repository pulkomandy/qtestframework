/* Copyright 2012-2018, Viveris Technologies.
 * This program is distributed under the MIT licence.
 */

#pragma once

#include <QtTest/QtTest>

class TestSqrt: public QObject
{
	Q_OBJECT

	public:
		Q_INVOKABLE TestSqrt();

	private slots:
		void init();
		void cleanup();

		void SquarePositive_data();
		void SquarePositive();
		void SquareNegative();
};

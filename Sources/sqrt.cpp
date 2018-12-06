/* Copyright 2012-2018, Viveris Technologies.
 * This program is distributed under the MIT licence.
 */

#include "sqrt.h"

#include <math.h>
#include <QDebug>

double squareRoot(double value)
{
	if (value < 0) {
		qWarning() << "Attempt to root a negative number";
		return 0;
	}

	return sqrt(value);
}

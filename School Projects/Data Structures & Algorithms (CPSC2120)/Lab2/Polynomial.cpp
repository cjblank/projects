#include <iostream>
#include <ostream>
#include <string>
#include "Polynomial.h"

using namespace std;

Polynomial::Polynomial()
{
	for (int i = 0; i < 100; i++)
	{
		poly[i].coef = 0;
		poly[i].pwr = 0;
	}
    powerCount = 0;
}

void Polynomial::incrementBy(int c, int p)
{
	poly[p].pwr = p;
	poly[p].coef += c;
}

bool Polynomial::operator==(const Polynomial &other)
{
	for (int i = 99; i >= 0; i--)
	{
		if ((poly[i].coef != other.poly[i].coef) || (poly[i].pwr != other.poly[i].pwr))
			return false;
	}
	return true;
}

ostream& operator<<(ostream& output, const Polynomial& p)
{
	bool sign = false;

	for (int i = 99; i >= 0; i--)
	{

		if (p.poly[i].coef != 0)
		{
			if (sign)
				output << " + ";

			output << p.poly[i].coef << "x^" << p.poly[i].pwr;
			sign = true;
		}

	}
	return output;
}

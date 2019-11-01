#include "Point.h"
#include <iostream>

using namespace std;

Point::Point(int x, int y): X(x), Y(y)
{}

Point::Point(const Point & other)
{
	this->X = other.getX();
	this->Y = other.getY();
}

int Point::getX() const
{
	return X;
}

int Point::getY() const
{
	return Y;
}

bool Point::operator==(const Point & other) const
{
	if ((this->getX() == other.getX()) && (this->getY() == other.getY()))
		return true;
	return false;
}

ostream & operator<<(ostream& out, const Point& P)
{
	out << "(" << P.getX() << ',' << P.getY() << ")";

	return out;
}
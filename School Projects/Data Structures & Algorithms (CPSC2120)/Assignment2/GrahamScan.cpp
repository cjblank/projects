// partial implementation of GrahamScan
#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
#include "GrahamScan.h"

// returns bearing of line from Point A to Point B
double angle(Point &A, Point &B) 
{
	double bearing;
	bearing = atan2(B.getY() - A.getY(), B.getX() - A.getX()); // tan^-1 = (Y[B] - Y[A]) / (X[B] - X[A])
	bearing = bearing * 180.0 / M_PI; // radians to degrees
	return bearing;
}

// sorts points by angle counterclockwise from list[0] using insertion sort
void sortByAngleFromFirst(vector<Point> &list)
{
   for(unsigned int round=1; round<list.size(); round++) {
      int i=round; 
      Point newPoint = list[round];
      double newAngle = angle(list[0], newPoint );
      while( i>1 && ( newAngle < angle(list[0], list[i-1]) ) ) {
	 list[i]=list[i-1];
         i--;
      }
      list[i] = newPoint;
   }
} 

// finds leftmost point in list and moves it into position 0
void moveLeftmostFirst( vector<Point> &list ) 
{
	int lmost = 0;
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i].getX() < list[lmost].getX()) // x-coordinate determines how left-right a point is 
												 // the lowest x-coordinate is leftmost
		{
			lmost = i; // changes position of the leftmost point
		}
	}
	if (!list.empty())
	{
		Point temp(list[lmost]); // makes new Point object with lmost data
		list.erase(list.begin() + lmost); // takes list[lmost] off list
		list.insert(list.begin(), temp); // adds lmost data onto front of list
	}
}

// returns true if going A to B to C is a left turn
bool isLeftTurn( Point &A, Point &B, Point &C ) 
{
      return (B.getY()-A.getY())*(C.getX()-B.getX()) <
                    (C.getY()-B.getY())*(B.getX()-A.getX());
}

// prints out contents of list
void debugDump( vector<Point> &list)
{
	cout << "POINT DUMP\n";
	for (unsigned int i = 0; i < list.size(); i++)
	{
		cout << list[i];
	}
}

// determines convex hull of list using Graham scan
vector<Point> convexHull( vector<Point> &list)
{
	if (list.size() < 3) // anything smaller is not a polygon
		return list;

	vector<Point> newList;
	newList = list;
	moveLeftmostFirst(newList);
	sortByAngleFromFirst(newList);

	PointStack hull; // holds hull's data

	hull.push(newList[0]);
	hull.push(newList[1]);

	for (unsigned int i = 2; i < newList.size(); i++) 
	{
		while (!isLeftTurn(hull.peekUnder(), hull.peek(), newList[i])) // pops right turns off
		{
			hull.pop();
		}
		hull.push(newList[i]);
	}

	vector<Point> temp;

	while (!hull.isEmpty())
	{
		temp.insert(temp.begin(), hull.pop());
	}

	return temp;
}

// determines convex shells of list by repeated use of convexHull
void shellIt(vector<Point> &list)
{
	cout << "Shells are: \n";
	while(!list.empty())
	{
		vector<Point> hull;
		hull = convexHull(list);
		for (unsigned int i = 0; i < hull.size(); i++)
		{
			cout << hull[i];

			for (unsigned int j = 0; j < list.size(); j++)
			{
				if (hull[i] == list[j])
				{
					list.erase(list.begin() + j); // erases list[j]
					break; // leaves loop once j is found 
				}
			}
		}

		cout << endl;
	}
}


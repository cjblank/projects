#include "Point.h"
#include "PointStack.h"
#include "GrahamScan.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<Point> pnt;

int main()
{
	int count, x, y;

	cout << "Enter count: ";
	cin >> count;
	cout << endl;
	cout << "Enter point: ";
	for (int i = 0; i < count; i++)
	{
		cin >> x;
		cin >> y;
		pnt.push_back(*(new Point(x, y)));
	}

	cout << endl;

	vector<Point> hull;
	hull = convexHull(pnt);	
	cout << "Hull is ";
	for (unsigned int i = 0; i < hull.size(); i++)
	{
		cout << hull[i];
	}

	cout << endl;

	shellIt(pnt);

	return 0;
}
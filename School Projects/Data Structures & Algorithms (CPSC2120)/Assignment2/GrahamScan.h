// goddard - 2017
#ifndef GRAHAM_SCAN_H
#define GRAHAM_SCAN_H

#include <vector>
using namespace std;
#include "Point.h"
#include "PointStack.h"

double angle(Point &A, Point &B);
void sortByAngleFromFirst(vector<Point> &list);
void moveLeftmostFirst( vector<Point> &list );
bool isLeftTurn( Point &A, Point &B, Point &C );
void debugDump( vector<Point> &list);
vector<Point> convexHull( vector<Point> &list);
void shellIt( vector<Point> &list );
 
#endif

// goddard - 2017
// must not be altered
#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

class Point 
{
   private:
     int X,Y;

   public:
      Point(int x, int y);
      Point( const Point & other);
      int getX( ) const;
      int getY( ) const;
      bool operator==(const Point & other) const;
      friend ostream & operator<<(ostream &out, const Point & P );
};

#endif

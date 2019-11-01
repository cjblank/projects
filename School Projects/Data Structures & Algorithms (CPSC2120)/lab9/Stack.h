// Goddard Stack.h 2015
#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

//template <class E>
class Disc {

	int width;
public:
	Disc(int w) {
		width = w;
	}

	bool compare(Disc *other) {
		return (this->width < other->width);
	}

	friend ostream& operator<<(ostream &output, const Disc &item);
};


template <class E>
class Stack 
{
 private:
   E* arr;
   int count;
   static const int capacity = 100;

 public:
   Stack();
   ~Stack();

   E pop();
   void push(E item);
   E peek();

   bool isEmpty() const 
   {
     return (count==0);
   }
   int getCount() const 
   {
     return count;
   }
};

#endif

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <ostream>
#include <string>

using namespace std;

struct Pair{
		int coef;
		int pwr;
} ;

class Polynomial
{
	public:
		Polynomial();
		void incrementBy(int c, int p);
		bool operator==(const Polynomial &other);
		friend ostream& operator<<(ostream& output, const Polynomial& polynom);

	private:
		int powerCount;
		Pair poly[100];
		
};


#endif // !POLYNOMIAL_H

// TestBlister.cpp - goddard - 2017
// adapt as desired
#include <iostream>
using namespace std;
#include "Blister.h"

int main( ) 
{
   Blister X("abcde");
   Blister Y("acde");
   Blister Z("abode");

   cout << X << " " << Y << " " << Z << endl;

   cout << X.length() << " " << Y.length() << " " << Z.length() << endl;

   cout << boolalpha << X.isSubstitutionOf(Y) << " ";
   cout << boolalpha << Y.isSubstitutionOf(Z) << " ";
   cout << boolalpha << Z.isSubstitutionOf(X) << " ";
   cout << endl;

   cout << boolalpha << Y.isInsertionOf(X) << " ";
   cout << boolalpha << X.isInsertionOf(Y) << " ";
   cout << boolalpha << Y.isInsertionOf(Z) << " ";
   cout << boolalpha << Z.isInsertionOf(X) << " ";
   cout << endl;

   return 0;

}

/* expected output

abcde acde abode
5 4 5
false false true 
false true false false 

*/

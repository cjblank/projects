// Goddard Stack.cpp 2015
// note that this is #included from Stack.h
// and not compile separately
#include <iostream>

using namespace std;
#include "Stack.h"

template class Stack<Disc*>;

  template< class E >
  Stack<E>::Stack() 
    : arr( new E[capacity] ), count(0)
  {
  }

  template< class E >
  Stack<E>::~Stack() 
  {
    delete [] arr;
  }

  template< class E >
  E Stack<E>::pop() 
  {
       count--;
       return arr[count];
  }

  template< class E >
  void Stack<E>::push(E item) 
  {
    arr[count] = item;
    count++;
  }


 template< class E >
 E Stack<E>::peek() {
  if (count > 0)
  {
	  return arr[count - 1];
  }

  return NULL;
 }

  ostream& operator<<(ostream &output, const Disc &item)
  {
	  if (&item == NULL)
		  output << "empty";
	  else
		output << item.width;

	  return output;
  }

  

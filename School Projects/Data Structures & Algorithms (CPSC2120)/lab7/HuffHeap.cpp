// Heap.cpp - wdg 2014
#include "HuffHeap.h"

  Heap::Heap( ) : count(0)
  {
  }

  void Heap::insertItem(ItemType newVal) 
  {
      int bubble = count;
      int parent = (bubble-1)/2;  // round down
      while(  bubble>0 && newVal<A[parent] ) {
         A[bubble] = A[parent];
         bubble = parent;
         parent = (bubble-1)/2;
      }
      A[bubble] = newVal;
      count++;
  }

  ItemType Heap::removeMin( ) 
  {
    if (count==0) 
      return ERROR;
    else {
      ItemType toReturn = A[0];
      count--;
      ItemType bubbleVal = A[count];
      int bubble = 0;
      int left = 1;
      int right = left+1;
      while(  ( left < count && bubbleVal>A[left]) ||
               ( right < count && bubbleVal>A[right] ) ) 
         {
         int smallerChild = left;
         if( right < count && A[right]<A[left] )
           smallerChild = right;
         A[bubble] = A[smallerChild];
         bubble = smallerChild;
         left = 2*smallerChild+1;
         right = left+1;
      } // endwhile
      A[bubble] = bubbleVal;
      return toReturn;
    }
  }

  bool Heap::isEmpty( ) const
  {
    return (count==0);
  }

  int Heap::getCount( ) const
  {
    return count;
  }




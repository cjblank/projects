// HuffHeap.h - wdg 2015
#ifndef HUFF_HEAP_H
#define HUFF_HEAP_H

#include "CharRecord.h"

typedef CharRecord ItemType;

const ItemType ERROR;

class Heap 
{
 public:
   Heap();
   void insertItem(ItemType);
   ItemType removeMin();
   bool isEmpty() const;
   int getCount() const;

 private:
   int count;
   ItemType A[100];
};

#endif

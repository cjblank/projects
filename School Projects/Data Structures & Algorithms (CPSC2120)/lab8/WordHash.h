#ifndef WORDHASH_H
#define WORDHASH_H
#include "WordCount.h"
#include <string>
using namespace std;

class WordHash 
{
   private:
      int arrayLength;
      WordCount **data;
      int count;

      static unsigned int hashOf(const string & word)
      {         
          return hash<string>()(word);
      }
      static const double LOAD_FACTOR;
      void rehash( );

   public:
      WordHash(int arraylength);
      ~WordHash( );
      void addWord( const string & word);
      void printCommon() const;
};

#endif

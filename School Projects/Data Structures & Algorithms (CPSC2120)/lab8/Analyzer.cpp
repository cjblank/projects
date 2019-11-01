#include <string>
#include <iostream>
#include <fstream>
using namespace std;
#include "WordHash.h"

void read(WordHash & hash, string fileName);

int main(int argc, char *args[]) 
{
      // check for input
      if(argc != 2) {
         cerr << "Please specify filename on command-line\n";
         return 1;
      } // end if

      WordHash hash(103);                  // create hash table
      read( hash, args[1] );
      hash.printCommon();
      return 0;
} // end main


// Method: read
// Arguments: String fileName - name of file to read
// Purpose: reads a file, adding the words to the hash table
void read(WordHash & hash, string fileName)
{
      // delimiters used in StringTokenizer
      string delimiters = " .,!?:;@#$%^&*-_=+1234567890";

      string line;

      ifstream in ( fileName );
      if( !in ) {
         cerr << "Cannot open " << fileName;
         return;
      } 
      while( getline(in, line) ) {
          int lineLen = line.length();
          for(int i=0; i<lineLen; i++) 
             if( line[i]>='A' && line[i]<='Z' )
                 line[i] += 'a'-'A' ;
          int start = line.find_first_not_of(delimiters,0);
          while( start>=0 && start<lineLen ) {
             int stop = line.find_first_of(delimiters,start);
             if( stop<0 || stop>lineLen)
                  stop = lineLen;
             hash.addWord( line.substr( start, stop-start ) );
             start = line.find_first_not_of( delimiters, stop+1);
          } // end while 
      } // end while

} // end read

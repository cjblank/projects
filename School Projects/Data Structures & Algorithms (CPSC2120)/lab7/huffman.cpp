// huffman.cpp - Goddard 2015
#include <iostream>
using namespace std;
#include "HuffHeap.h"
#include "huffman.h"

int main(int argc, char *argv[] ) 
{
    huffman( argv[1] );
    return 0;
}

void huffman( string S)
{
   int *count = getCount(S);
   string huffer = encode(count);
   printBinary( huffer );
}

int * getCount(string S)
{
   int * count = new int[ALPHABET];
   for(int i=0; i<ALPHABET; i++) 
       count[i]=0;
   for(unsigned int i=0; i<S.length(); i++) {
       if( S[i]>='A' && S[i]<='Z' )
          count[ S[i]-'A' ]++;
       else 
          cout << "Ignored char: " << S[i] << endl; 
   }
   for(int i=0; i<ALPHABET; i++)
      if( count[i]>0 ) 
         cout << (char)(BIG_A+i) << " : " << count[i] << endl; 
   cout << endl;
   return count;
}

string encode(int count[])
{
   Heap H;
   int i; 
   for(i=0; i<ALPHABET; i++)
      if( count[i]>0 ) 
         H.insertItem( CharRecord(string(1,BIG_A+i), count[i]) ); 
   while( H.getCount()>= 2 ) {
      CharRecord alpha = H.removeMin( );
      CharRecord beta = H.removeMin( );
      string newString = LEFT + alpha.getCharString() + SEPARATOR + beta.getCharString() + RIGHT; 
      int newCount = alpha.getCount()+beta.getCount();
      cout << newString << " : " << newCount << endl; 
      H.insertItem(  CharRecord( newString, newCount ) );
   }
   cout << endl;
   return H.removeMin( ).getCharString();
}   

void printBinary( string huffer )
{
    string current( huffer.length(), ' ');
    int depth=0;
    for(unsigned int i=0; i<huffer.length(); i++) {
       if( huffer[i]==LEFT )  
          current[depth++] = '0';
       else if( huffer[i]==RIGHT ) 
          depth--;
       else if( huffer[i]==SEPARATOR )
          current[depth-1]='1';
       else {
          cout << huffer[i] << " -> ";
          for(int d=0; d<depth; d++)
             cout << current[d];
          cout << endl;
       }
    }
}





#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
using namespace std;

const char LEFT = '(';
const char RIGHT = ')';
const char SEPARATOR = ':';
const char BIG_A = 'A';
const int ALPHABET = 26;

void huffman( string S);

int * getCount(string S);
string encode(int count[]);
void printBinary( string huffer );

#endif


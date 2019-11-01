#ifndef WORDCOUNT_H
#define WORDCOUNT_H
#include <string>
using namespace std;

class WordCount {

   private:
       string word;     // word stored by this WordCount object
       int frequency;   // number of times the word appears

   public:

   // Constructor: WordCount
   // Arguments: string newWord - word to store in WordCount object
   // Purpose: stores newWord in a WordCount object
   WordCount(string newWord) : 
      word(newWord),   // save the word
      frequency(1)    // the word occurs once so far
   {
   } 

   // Method: raiseCount
   // Arguments: none
   // Purpose: raises the frequency count of this word by one
   void incrementCount() 
   {
      frequency ++;
   } 

   // Method: getCount
   // Arguments: none
   // Returns: number of times word appears
   // Purpose: returns the frequency of this word
   int getCount() const 
   {
      return frequency;
   } 

   // Method: getWord
   // Arguments: none
   // Returns: word held in WordCount object
   // Purpose: returns the word
   string getWord() const 
   {
      return word;
   } 

};

#endif

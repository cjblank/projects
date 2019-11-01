#ifndef CHAR_RECORD_H
#define CHAR_RECORD_H

#include <iostream>
#include <string>
using namespace std;

class CharRecord{

private:
	string charString;
	int count;
public:
	CharRecord() : charString(""), count(0) {}
	CharRecord(string record, int num) : charString(record), count (num){}

	int getCount(){
		return count;
	}
	string getCharString(){
		return charString;
	}

	friend bool operator<(const CharRecord &i1, const CharRecord &i2){
		return (i1.count < i2.count);
	}

	friend bool operator>(const CharRecord &i1, const CharRecord &i2) {
		return (i1.count > i2.count);
	}
};

#endif

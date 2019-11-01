#include <iostream>
#include <string>

using namespace std;

#include "WordCount.h"
#include "WordHash.h"


WordHash::WordHash(int wordLength) 
{
	data = new WordCount*[wordLength];

	for (int i = 0; i < wordLength; i++)
	{
		data[i] = nullptr;
	}

	arrayLength = wordLength;
	count = 0;
}

WordHash::~WordHash()
{
	for (int i = 0; i < arrayLength; i++)
	{
		if(data[i] != nullptr)
			delete data[i];
	}

	delete data;
}

void WordHash::addWord(const string & word)
{
	unsigned int slot;

	slot = hashOf(word) % arrayLength;


	for (int i = 0; i < arrayLength; i++)
	{

		if (data[slot] == nullptr)
		{
			data[slot] = new WordCount(word);
			count++;
			break;
		}
		else if (data[slot]->getWord() == word)
		{
			data[slot]->incrementCount();
			break;
		}

		slot++;
		slot %= arrayLength;
	}

	if (((float)count / (float)arrayLength) > 0.7)
	{
		rehash();
	}
}

void WordHash::rehash()
{
	WordHash nHash(arrayLength*2);

	WordCount **oldData = data;
	WordCount **newData = new WordCount*[arrayLength*2+1];

	data = newData;

	for (int i = 0; i < arrayLength; i++)
	{
		addWord(oldData[i]->getWord());
	}

	for (int i = 0; i < arrayLength; i++)
		delete oldData[i];

	delete oldData;
}

void WordHash::printCommon() const
{
	int freq = 0;
	string wordMax = "empty table";

	for (int i = 0; i < arrayLength; i++)
	{
		if (data[i] != nullptr)
		{
			if (freq < data[i]->getCount())
			{
				freq = data[i]->getCount();
				wordMax = data[i]->getWord();
			}
		}
	}

	cout << wordMax << "\t" << freq << endl;
}
#include "PointStack.h"
#include <iostream>

using namespace std;

PointStack::PointStack():stackTop(nullptr){}

PointStack::~PointStack()
{
	while (stackTop != nullptr)
	{
		Node *temp = stackTop->next;
		delete temp;
		stackTop = temp;
	}
}

void PointStack::push(const Point & item)
{
	Node *newNode = new Node(item); // takes data from Point object
	
	newNode->next = stackTop; // pushes new data to the top of stack
	
	stackTop = newNode; // sets newNode to stackTop for later use of method

}

Point PointStack::pop()
{
	if (stackTop != nullptr)
	{
		Point p(stackTop->data); // puts stackTops data in temporary Point object
		Node *temp = stackTop; 

		stackTop = stackTop->next; // changes stackTop to next node in linked list
		delete temp; // deletes the previous stackTop from linked list
		return p; // returns the data from stackTop's node
	}
	return NOTHING;
}

Point& PointStack::peek() const
{
	if(stackTop != nullptr)
		return stackTop->data; // gets data from the top of the stack
	return NOTHING;
}

Point& PointStack::peekUnder() const
{
	if((stackTop != nullptr) || (stackTop->next != nullptr)) 
		return stackTop->next->data; // gets data from the node directly under the top of the stack
	return NOTHING;
}

bool PointStack::isEmpty() const
{
	if (stackTop == nullptr)
		return true;

	return false;
}

Point PointStack::NOTHING(0, 0);
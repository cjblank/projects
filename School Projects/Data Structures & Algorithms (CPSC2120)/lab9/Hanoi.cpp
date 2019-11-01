#include <iostream>
using namespace std;

#include "Stack.h"
#include "Stack.cpp"

Stack<Disc*> tower[3];

int main(int arc, char* argv[]) {
	int num;
	int to;
	int from;
	int moves = 0;

	num = atoi(argv[1]);
		
	for (int j = 0; j < num; j++)
	{
		Disc *tempDisc = new Disc(num-j);
		tower[0].push(tempDisc);
	}

	while (tower[2].getCount() != num)
	{
		do {
			from = rand() % 3;
		} while (tower[from].isEmpty());

		do {
			to = rand() % 3;
		} while (to == from);

		if (tower[to].isEmpty() || tower[from].peek()->compare(tower[to].peek())) {
			moves++;
			cout << moves << ". tower " << from << "(width " << *tower[from].peek() << ") -> tower " << to << "(width " << *tower[to].peek() << ")" << endl;
			tower[to].push(tower[from].pop());
		}
	}
	for (int stack = 0; stack < 3; stack++)
	{
		cout << "tower #" << stack << endl;
		cout << "    ";
		while (!tower[stack].isEmpty())
		{
			cout << *tower[stack].peek() << " ";
			tower[stack].pop();
		}
		cout << endl;
	}
}
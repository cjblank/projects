#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class Recursion {

private:
	int array[10][10];

	char temp;

public:

	Recursion(char *fileName)
	{
		ifstream input(fileName);

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				input >> temp;

				cout << temp;

				if (temp == '.')
				{
					array[i][j] = 0;
				}
				else
				{
					array[i][j] = 1;
				}

			}
			cout << '\n';
		}

	}

	void printGroupWith(int row, int col)
	{
		if ((row < 0) || (row > 9) || (col > 9) || (col < 0) || (array[row][col] == 0))
			return;

		cout << '(' << row << ',' << col << ") ";

		array[row][col] = 0;

		printGroupWith(row - 1, col);
		printGroupWith(row, col - 1);
		printGroupWith(row + 1, col);
		printGroupWith(row, col + 1);

	}

	void Print()
	{
		int arrayCpy[10][10];
		int groupCtr = 1;


		memcpy(arrayCpy, array, sizeof(array));

		/*
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				array[i][j] = arrayCpy[i][j];
			}
		}*/

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (array[i][j] == 1)
				{
					cout << "Group " << groupCtr << ": " ;
					printGroupWith(i, j);
					cout << '\n';
					groupCtr++;
				}
			}
		}

		memcpy(array, arrayCpy, sizeof(array));

	}
};


int main(int argc, char *argv[])
{
	Recursion obj(argv[1]);

	obj.Print();

	return 0;
}

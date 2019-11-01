#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

#include "FiloTree.h"

int main(int argc, char* argv[]) {
	
	string str = argv[1];

	int numSpecies;
	string *nameSpecies = NULL;
	ifstream file;
	file.open(str);

	if (!file.is_open()) {
		cout << "unable to open file";
		exit(1);
	}

	file >> numSpecies;

	nameSpecies = new string[numSpecies];

	for (int i = 0; i < numSpecies; i++)
		file >> nameSpecies[i];

	FiloTree *f1 = new FiloTree(nameSpecies, (int)log2(numSpecies));
	f1->dump();

	cout << "\n\n\n\n\n";
	FiloTree *f2 = new FiloTree(str);
	f2->dump();
	
	delete f1;
	delete f2;

	return 0;
}

#if 0
int __main(int argc, char *argv[])
{
	double D[16] =
	{
		0.0, 2.2, 5.0, 5.0,
		2.2, 0.0, 5.0, 6.0,
		5.0, 5.0, 0.0, 1.4,
		5.0, 6.0, 1.4, 0.0
	};

	double D2[16];

	int N = 4;
	int row, col;

	// loop until only 2 elements left
	while (N>2)
	{
		double dist = 100000000.0; // random large value
		// look for the smallest distance.
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if ((D[i * N + j] < dist) && (i != j))
				{
					dist = D[i * N + j];
					row = i;
					col = j;
				}
			}
		}

		int newi = 0, newj = 0;

		// copy the rows and columns that we're keeping. into the new matrix
		memset(D2, 0, sizeof(D2));
		for (int i = 0; i < N; i++)
		{

			if ((i == row) || (i == col))
				continue;

			newj = 0;
			for (int j = 0; j < N; j++)
			{
				if ((j == row) || (j == col))
					continue;

				D2[newi * (N - 1) + newj] = D[i * N + j];

				cout << D2[newi * (N - 1) + newj] << " ";
				newj++;
			}
			cout << endl;
			newi++;
		}

		double	D3[16];
		int x = 0;
		// create a vector with the averaged values
		for (int i = 0; i < N; i++)
		{
			if ((i == row) || (i == col))
				continue;
			D3[x++] = (D[i * N + col] + D[i * N + row]) / 2;
		}

		cout << endl;
		cout << endl;
		for (int i = 0; i < x; i++)
			cout << D3[i] << " ";
		cout << endl;
		cout << endl;

		N--; 
		// place the new averaged vector into the rol and column representing the merged node
		for (int i = 0; i < x; i++)
		{
			D2[(N - 1)*N + (N - 1)] = 0.0;
			D2[i * N + (N - 1)] = D3[i];
			D2[(N - 1) * N + i] = D3[i];
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cout << D2[i * N + j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << endl;
		// copy the new matrix into the old
		memcpy(D, D2, N * N * sizeof(double));
	}
}
#endif
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

using namespace std;

#include "FiloTree.h"

FiloTree::FiloTree(string leaves[], int depth) {
	root = buildTree((int) exp2(depth), 0, leaves);
}
 
FiloTree::FiloTree(string fileName) {
	int numSpecies;
	double dist = 0;
	int row, col;
	string *nameSpecies = NULL;
	double *reals = NULL;
	root = nullptr;

	// lines 19-61 makes the input into usable data
	ifstream file;
	file.open(fileName);

	if (!file.is_open()) {
		cout << "unable to open file";
		exit(1);
	}

	file >> numSpecies;

	nameSpecies = new string[numSpecies];
	reals = new double[numSpecies * numSpecies];

	for (int i = 0; i < numSpecies; i++)
		file >> nameSpecies[i];

	for (int i = 0; i < (numSpecies * numSpecies); i++)
		file >> reals[i];

	file.close();

	for (int i = 0; i < numSpecies * numSpecies; i++) {
		if (reals[i] > dist)
			dist = reals[i];
	}

	dist += 1.0;

	for (int i = 0; i < numSpecies; i++) {
		for (int j = 0; j < numSpecies; j++) {
			if (i == j)
				continue;
			if (reals[(i * numSpecies) + j] < dist) {
				dist = reals[(i * numSpecies) + j];
				row = i;
				col = j;
			}
		}
	}

	root = buildTree(row, col, reals, numSpecies, nameSpecies);

	//cout << "real = " << dist << "\t(row, col) = (" << row << "," << col << ")";

	delete reals;

}

FiloTree::~FiloTree() {
	eraseTree(root);
}

void FiloTree::dump() const {

	printTree(root, 0);
	
}

bool FiloTree::compare(const FiloTree &A, const FiloTree &B) {
	return compareTree(A.root, B.root);
}

void FiloTree::printTree(FiloNode *node, int level) const {
	if (node == nullptr)
		return;

	// represents the different levels of the tree
	for (int i = 0; i < level; i++) { 
		cout << "...";
	}
	
	cout << node->lable << endl;

	level++;

	if (node->left != nullptr) {
		printTree(node->left, level);
	}
	if (node->right != nullptr) {
		printTree(node->right, level);
	}

}


void FiloTree::eraseTree(FiloNode *node) { // uses recursion to erase tree
	if (node != nullptr) {
		if (node->left != nullptr) {
			eraseTree(node->left);
		}
		if (node->right != nullptr) {
			eraseTree(node->right);
		}

		delete node;
	}
}

FiloNode* FiloTree::buildTree(int numStrings, int start, string str[]) {
	FiloNode *node;

	node = new FiloNode();

	if (numStrings == 1)
		node->lable = str[start];
	else {
		node->left = buildTree(numStrings / 2, start, str);
		node->right = buildTree(numStrings / 2, start + numStrings / 2, str);
	}

	return node;

}

bool FiloTree::compareTree(FiloNode *node1, FiloNode *node2) {
	int leafCount = 0;

	//determines if the given nodes are leaves or not 
	if ((node1->left == nullptr) && (node1->right == nullptr))
		leafCount++;
	if ((node2->left == nullptr) && (node2->right == nullptr))
		leafCount++;

	//if leaf count if 1 then the tree is incomplete
	if (leafCount == 1)
		return false;
	else if (leafCount == 2) { //once the bottom of the tree is reached, the labels are compared
		if (node1->lable == node2->lable)
			return true;
	}
	else if (leafCount == 0) 
	{
		if (compareTree(node1->left, node2->left) && compareTree(node1->right, node2->right))
			return true;
		if (compareTree(node1->left, node2->right) && compareTree(node1->right, node2->left))
			return true;
	}

	return false;
}

FiloNode* FiloTree::buildTree(int row, int col, double *reals, int numStrings, string *nameStrings) {

	const int initialSize = numStrings * numStrings; // size of reals[]
	double *matrix1 = new double[initialSize]; // local copy of reals[]
	double *matrix2 = new double[initialSize]; // intermediate copy of reals[] that has current nodes removed
	int mergeCount = 1; // tracks number of merges
	vector<FiloNode*> nodes; // base/bottom of tree

	for (int i = 0; i < numStrings; i++) {
		nodes.push_back(new FiloNode(nameStrings[i]));
	}

	int N = numStrings;

	memcpy((void*)matrix1, (void*)reals, initialSize * sizeof(double)); // copies content of reals[] to matrix1[]

	// loop until only 2 elements left
	while (N > 2)
	{
		double dist = 10000000000.0; // random large value
								   // look for the smallest distance.
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if ((matrix1[i * N + j] < dist) && (i != j))
				{
					dist = matrix1[i * N + j];
					row = i;
					col = j;
				}
			}
		}

		int newi = 0, newj = 0;

		// copy the rows and columns that we're keeping. into the new matrix
		memset(matrix2, 0, initialSize * sizeof(double));
		for (int i = 0; i < N; i++)
		{

			if ((i == row) || (i == col))
				continue;

			newj = 0;
			for (int j = 0; j < N; j++)
			{
				if ((j == row) || (j == col))
					continue;

				matrix2[newi * (N - 1) + newj] = matrix1[i * N + j];

				newj++;
			}
			newi++;
		}

		vector <double> matrix3;
		// create a vector with the averaged values
		for (int i = 0; i < N; i++)
		{
			if ((i == row) || (i == col))
				continue;
			matrix3.push_back((matrix1[i * N + col] + matrix1[i * N + row]) / 2);
		}

		N--;
		// place the new averaged vector into the rol and column representing the merged node
		for (unsigned int i = 0; i < matrix3.size(); i++)
		{
			matrix2[(N - 1)*N + (N - 1)] = 0.0;
			matrix2[i * N + (N - 1)] = matrix3[i];
			matrix2[(N - 1) * N + i] = matrix3[i];
		}

		memcpy(matrix1, matrix2, N * N * sizeof(double));

		nodes.push_back(new FiloNode(to_string(mergeCount), nodes[row], nodes[col]));
		if (col > row) 
		{
			nodes.erase(nodes.begin() + col);
			nodes.erase(nodes.begin() + row);
		}
		else
		{
			nodes.erase(nodes.begin() + row);
			nodes.erase(nodes.begin() + col);
		}
		mergeCount++;
	}

	delete matrix1;
	delete matrix2;

	return new FiloNode(to_string(mergeCount), nodes[0], nodes[1]); // returns root

}

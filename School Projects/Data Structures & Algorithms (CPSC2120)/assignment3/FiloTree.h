#ifndef FILO_TREE_H
#define FILO_TREE_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct FiloNode
{
	string lable;
	FiloNode *left, *right;

	FiloNode(string lab = "X", FiloNode *L = nullptr, FiloNode *R = nullptr)
		: lable(lab), left(L), right(R)
	{ }
};

class FiloTree
{
private:
	FiloNode *root; 
	void printTree(FiloNode *node, int level) const; // formats the tree recursively
	void eraseTree(FiloNode *node); // deletes all nodes recursively
	FiloNode* buildTree(int numNodes, int location, string  str[]); // builds tree for first constuctor
	FiloNode* buildTree(int row, int col, double reals[], int numStrings, string nameStings[]); // builds tree for second constructor
	static bool compareTree(FiloNode *node1, FiloNode *node2); // uses recursion and FiloNodes to compare trees
public:
	FiloTree(string leaves[], int depth);
	void dump() const;
	static bool compare(const FiloTree &A, const FiloTree &B);
	~FiloTree();
	FiloTree(string fileName);
};

#endif

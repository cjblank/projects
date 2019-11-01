#include "TreeNode.h"
#include <iostream>
#include <stack>

using namespace std;

TreeNode::TreeNode(string str) : 
	value(str),
	lchild(nullptr),
	rchild(nullptr)
{
}

void TreeNode::setLeft(TreeNode * l)
{
	lchild = l;
}

void TreeNode::setRight(TreeNode * r)
{
	rchild = r;
}

void TreeNode::postorder() const
{
	if (lchild != nullptr)
	{
		lchild->postorder();
	}
	if (rchild != nullptr)
	{
		rchild->postorder();
	}
	
	cout << value;
	
}

void TreeNode::preorder() const
{
	stack<TreeNode> nodes;
	TreeNode* temp;
	bool printed = false;

	nodes.push(*this);

	while (!nodes.empty())
	{
		if(printed == false)
			cout << nodes.top().value;
		if (nodes.top().lchild != nullptr)
		{
			temp = nodes.top().lchild;
			nodes.top().lchild = nullptr;
			nodes.push(*temp);
			printed = false;
			continue;
		}
		if (nodes.top().rchild != nullptr)
		{
			temp = nodes.top().rchild;
			nodes.top().rchild = nullptr;
			nodes.push(*temp);
			printed = false;
			continue;
		}
		nodes.pop();
		printed = true;
	}
}

ostream& operator<<(ostream& out, const TreeNode & node)
{
	string str = node.value;
	out << str.c_str();
	return out;
}
// goddard - TreeNode.h - 2016
#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using namespace std;

class TreeNode { 

  private:
      const string value;    // contains node value 
      TreeNode * lchild;   // pointer to node's left child 
      TreeNode * rchild;   // pointer to node's right child 

  public:
  
  // only constructor
  TreeNode (string str);

  // mutator methods to set children
  void setLeft( TreeNode* l);
  void setRight( TreeNode* r);

  // methods that print out tree rooted at this node
  void postorder ( ) const;
  void preorder( ) const;

  // prints out the value of one node
  friend ostream & operator<< ( ostream & , const TreeNode & );
};

#endif

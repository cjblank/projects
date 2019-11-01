// goddard - TreeDriver.cpp - 2016
// a rather poor tester for TreeNode
#include <iostream>
using namespace std;
#include "TreeNode.h"

int main() 
{ 
      // Create tree by hand here.
     TreeNode * t1 = new TreeNode("A"); 
     TreeNode * t2 = new TreeNode("B"); 
     TreeNode * t3 = new TreeNode("C"); 
     TreeNode * t4 = new TreeNode("D"); 
     TreeNode * t5 = new TreeNode("E"); 
     TreeNode * t6 = new TreeNode("F"); 
     TreeNode * t7 = new TreeNode("G"); 
	 TreeNode * t8 = new TreeNode("H");
	 TreeNode * t9 = new TreeNode("I");
	 TreeNode * t10 = new TreeNode("J");
	 TreeNode * t11 = new TreeNode("K");
	 TreeNode * t12 = new TreeNode("L");
	 TreeNode * t13 = new TreeNode("M");
	 TreeNode * t14 = new TreeNode("N");
	 TreeNode * t15 = new TreeNode("O");


     cout << *t1 << " " << *t2 << " " << *t3 << " " << *t4 << " " << *t5 << " " << *t6 << " " << *t7 << " " << *t8 << " " << *t9 << " "<< *t10 <<
		 " " << *t11 << " " << *t12 << " " << *t13 << " " << *t14 << " " << *t15 << endl;

     t1->setLeft(t2); 
     t1->setRight(t3);
     t2->setLeft(t4);
     t2->setRight(t5);
     t3->setLeft(t6); 
     t3->setRight(t7);
	 t4->setRight(t8);
	 t8->setLeft(t9);
	 t6->setRight(t10);
	 t10->setLeft(t11);
	 t10->setRight(t12);
	 t7->setLeft(t13);
	 t6->setLeft(t14);
	 t13->setRight(t15);

     cout << "Postorder should be IHDEBNKLJFOMGCA" << endl;     
     t1->postorder( );
     cout << "\nPreorder should be ABDHIECFNJKLGMO" << endl;     
     t1->preorder( );
     
     cout << endl;

     delete t1;
     delete t2;
     delete t3;
     delete t4;
     delete t5;
     delete t6;
     delete t7;
     return 0;
} 



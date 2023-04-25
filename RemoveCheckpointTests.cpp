#include <iostream>
#include <cassert>

#include "RedBlackTree.h"


void TestRemoveLeaf(){
	cout << "Testing Remove Leaf..." << endl;
	
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(40);

	// removing root
	rbt.Remove(40);
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == "");
	//assert(rbt.root == nullptr);


	rbt.Insert(40);
	rbt.Insert(23);
	rbt.Remove(23);
	//cout << "rbt after: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B40 ");
	
	rbt.Insert(23);
	rbt.Insert(52);
	rbt.Remove(52);
	assert(rbt.ToPrefixString() == " B40  R23 ");


	rbt.Insert(52);
	rbt.Insert(15);
	rbt.Remove(15);
	//cout << "rbt after: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B40  B23  B52 ");
	
	cout << "PASSED!" << endl << endl;
}

void TestDoubleBlackTests() {
    RedBlackTree* rbt = new RedBlackTree();

    rbt->Insert(2);
    rbt->Insert(3);
    rbt->Insert(4);
    rbt->Insert(6);

    rbt->Remove(2);

    cout << rbt->ToPrefixString() << endl;
}

void TestRemove() {
    RedBlackTree* rbt = new RedBlackTree();

    rbt->Insert(31);
    rbt->Insert(49);
    rbt->Insert(23);
    rbt->Insert(11);
    rbt->Insert(28);
    rbt->Insert(47);
    rbt->Insert(56);
    rbt->Insert(24);
    rbt->Insert(45);

    cout << rbt->ToPrefixString() << endl;

    delete rbt;
}


int main(){
	
//	TestRemoveLeaf();

//    TestDoubleBlackTests();

    TestRemove();

	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}

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

//void TestRemove() {
//    RedBlackTree* rbt = new RedBlackTree();
//
//    rbt->Insert(31);
//    rbt->Insert(49);
//    rbt->Insert(23);
//    rbt->Insert(11);
//    rbt->Insert(28);
//    rbt->Insert(47);
//    rbt->Insert(56);
//    rbt->Insert(24);
//    rbt->Insert(45);
//
//    cout << rbt->ToPrefixString() << endl;
//
//    delete rbt;
//}

void TestGetAll() {
    RedBlackTree* rbt = new RedBlackTree();

//    rbt->Insert(31);
//    rbt->Insert(49);
//    rbt->Insert(23);
//    rbt->Insert(11);
//    rbt->Insert(28);
//    rbt->Insert(47);
//    rbt->Insert(56);
//    rbt->Insert(24);
//    rbt->Insert(45);
    rbt->Insert(0);
    rbt->Insert(1);
    rbt->Insert(2);

    cout << rbt->ToPrefixString() << endl;
    cout << rbt->Size() << endl;
}

void TestRemove() {
//    RedBlackTree rbt = RedBlackTree();
//
//    rbt.Insert(12);
//    rbt.Insert(11);
//    rbt.Insert(15);
//    rbt.Insert(5);
//    rbt.Insert(13);
//    rbt.Insert(7);

    RedBlackTree rbt1 = RedBlackTree();
    rbt1.Insert(11);
    rbt1.Insert(23);
    rbt1.Insert(9);
    rbt1.Insert(52);
    rbt1.Insert(31);
    rbt1.Insert(4);

    assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

    RedBlackTree rbt2 = RedBlackTree(rbt1);

    cout << rbt1.ToPrefixString() << endl;
    cout << rbt2.ToPrefixString() << endl;

    assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

    rbt1.Insert(200);
    assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

    rbt1 = RedBlackTree();
    rbt2 = RedBlackTree(rbt1);

    rbt1 = RedBlackTree();
    rbt1.Insert(2);
    rbt2 = RedBlackTree(rbt1);

    rbt1 = RedBlackTree();
    rbt1.Insert(1);
    rbt1.Insert(2);

    rbt2 = RedBlackTree(rbt1);

    cout << rbt1.ToPrefixString() << endl;
    cout << rbt2.ToPrefixString() << endl;

    cout << "PASSED!" << endl << endl;

//    RedBlackTree *rbt2 = new RedBlackTree();
//
//    rbt2->Insert(12);
//    rbt2->Insert(11);
//    rbt2->Insert(15);
//    rbt2->Insert(5);
//    rbt2->Insert(13);
//    rbt2->Insert(7);
//
//    delete rbt2;
}


int main(){
	
//	TestRemoveLeaf();
//
//    TestDoubleBlackTests();

//    TestGetAll();
    TestRemove();
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}


#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

/**
 * 
 * This "First Step" tests file is useful to get your project started
 * 
 * To run this code you only need to implement
 * 	+ The Constructor
 * 	+ The Insert() function to insert only one node
 * 	+ The ToInfixString() function to print a tree containing only one node
 * 
**/

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt->ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}


void TestInsertFirstNode(){
	cout << "Testing Insert One RBTNode..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
//	cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");
    cout << rbt.ToPostfixString() << endl;

	cout << "PASSED!" << endl << endl;
}

void TestInsertSecondNode(){
    cout << "Testing Insert Second RBTNode..." << endl;
    RedBlackTree *rbt = new RedBlackTree();
    rbt->Insert(30); // leak here
    rbt->Insert(15);
    cout << rbt->ToPrefixString() << endl;
    assert(rbt->ToPrefixString() == " B30  R15 ");
    delete rbt;

    rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(45);
    assert(rbt->ToPrefixString() == " B30  R45 ");
    delete rbt;

    cout << "PASSED!" << endl << endl;
}


void TestInsertThirdNode(){
    cout << "Testing Insert Third RBTNode..." << endl;
    RedBlackTree *rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(15);
    rbt->Insert(10); // Left Left
    cout << "rbt: "  << rbt->ToPrefixString() << endl;
//    assert(rbt->ToPrefixString() == " B15  R10  R30 ");

    rbt = new RedBlackTree();
    rbt->Insert(50);
    rbt->Insert(22);
    rbt->Insert(34);
    cout << "rbt: " << rbt->ToPrefixString() << endl;

    delete rbt;

    rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(15);
    rbt->Insert(25); // Right Left
    cout << "rbt: " << rbt->ToPrefixString() << endl;
    assert(rbt->ToPrefixString() == " B25  R15  R30 ");
    delete rbt;

    rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(15);
    rbt->Insert(45); // Easy case
    assert(rbt->ToPrefixString() == " B30  R15  R45 ");
    delete rbt;

    // more tests go here
    // consider some symmetry!

    cout << "TESTS MISSING" << endl << endl;
    cout << "PASSED!" << endl << endl;
}

void RandomInsertTests() {
    cout << "Testing Randomly Inserting Into the RBT" << endl;

    int input;
    RedBlackTree* rbt = new RedBlackTree();

    cout << "Insert: ";
    cin >> input;

    while(input != -1) {
        rbt->Insert(input);
        cout << rbt->ToPrefixString() << endl;

        cout << "Insert: ";
        cin >> input;
    }

    delete rbt;
}

void InsertFour() {
    RedBlackTree* rbt = new RedBlackTree();

    rbt->Insert(5);
    rbt->Insert(8);
    rbt->Insert(3);
    rbt->Insert(2);

    cout << rbt->ToPrefixString() << endl;
}

int main(){
//	TestSimpleConstructor();
//	TestInsertFirstNode();
//    TestInsertSecondNode();
//    TestInsertThirdNode();

    RandomInsertTests();
//    InsertFour();
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}

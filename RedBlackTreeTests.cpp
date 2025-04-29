
#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}

void TestConstructor(){
	cout << "Testing Constructor W/Int Input..." << endl;
	RedBlackTree rbt = RedBlackTree(15);
	assert(rbt.ToPrefixString() == " B15 ");

	cout << "PASSED!"<< endl << endl;
}

void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
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
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Right Left
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	rbt=new RedBlackTree();
	rbt->Insert(32);
    rbt->Insert(20);
    rbt->Insert(28); // Left Right
    assert(rbt->ToPrefixString() == " B28  R20  R32 ");
    delete rbt;
    
    rbt=new RedBlackTree();
	rbt->Insert(42);
    rbt->Insert(420);
    rbt->Insert(4200); // Right Right
    assert(rbt->ToPrefixString() == " B420  R42  R4200 ");
    delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	rbt->Insert(13);
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  B10  R13  B30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Right Left
	rbt->Insert(29);
	assert(rbt->ToPrefixString() == " B25  B15  B30  R29 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	rbt->Insert(69);
	assert(rbt->ToPrefixString() == " B30  B15  B45  R69 ");
	delete rbt;
	
	rbt=new RedBlackTree();
	rbt->Insert(32);
    rbt->Insert(20);
    rbt->Insert(28); // Left Right
	rbt->Insert(21);
    assert(rbt->ToPrefixString() == " B28  B20  R21  B32 ");
    delete rbt;
    
    rbt=new RedBlackTree();
	rbt->Insert(42);
    rbt->Insert(420);
    rbt->Insert(4200); // Right Right
	rbt->Insert(86);
    assert(rbt->ToPrefixString() == " B420  B42  R86  B4200 ");
    delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	rbt->Insert(7);
	rbt->Insert(9);
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  B9  R7  R10  B30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Right Left
	rbt->Insert(32);
	rbt->Insert(38);
	assert(rbt->ToPrefixString() == " B25  B15  B32  R30  R38 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	rbt->Insert(60);
	rbt->Insert(80);
	assert(rbt->ToPrefixString() == " B30  B15  B60  R45  R80 ");
	delete rbt;
	
	rbt=new RedBlackTree();
	rbt->Insert(32);
    rbt->Insert(20);
    rbt->Insert(28); // Right Right
	rbt->Insert(26);
	rbt->Insert(24);
    assert(rbt->ToPrefixString() == " B28  B24  R20  R26  B32 ");
    delete rbt;
    
    rbt=new RedBlackTree();
	rbt->Insert(42);
    rbt->Insert(420);
    rbt->Insert(4200); // Right Right
	rbt->Insert(86);
	rbt->Insert(101);
    assert(rbt->ToPrefixString() == " B420  B86  R42  R101  B4200 ");
    delete rbt;

	
	cout << "PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	//cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	// probably should have a delete or something here
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);

	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}






void TestContains(){
	cout << "Testing Contains..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	assert(rbt->Contains(6) == false);
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(rbt->Contains(34));
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(19);
	rbt->Insert(39);
	rbt->Insert(9);
	rbt->Insert(8);
	rbt->Insert(3);
	rbt->Insert(4);
	rbt->Insert(2);
	rbt->Insert(92);
	rbt->Insert(88);
	rbt->Insert(47);
	rbt->Insert(36);
	rbt->Insert(99);
	rbt->Insert(103);
	rbt->Insert(2222);
	rbt->Insert(2234);
	rbt->Insert(233);
	rbt->Insert(938);
	
	
	assert(rbt->Contains(2234));
	assert(rbt->Contains(2));
	assert(rbt->Contains(60) == false);
	assert(rbt->Contains(44) == false);
	delete rbt;
	

	cout << "PASSED!" << endl << endl;
}




void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	RedBlackTree *rbt=new RedBlackTree();
    rbt->Insert(1);
    rbt->Insert(10);
    rbt->Insert(20);
    rbt->Insert(30);
    rbt->Insert(69);
    
    assert(rbt->GetMin()==1);
    assert(rbt->GetMax()==69);
    delete rbt;

	cout<<"PASSED!"<<endl;

	RedBlackTree *rbt2 = new RedBlackTree();
    try{
        rbt2->GetMin();
        assert(false);
    }
	catch (const invalid_argument& e){
        cout<<"PASSED!"<<endl;
    }

	RedBlackTree *rbt3 = new RedBlackTree();
	try{
        rbt3->GetMax();
        assert(false);
    }
	catch (const invalid_argument& e){
        cout<<"PASSED!"<<endl;
    }
}





int main(){

	
	TestSimpleConstructor();
	TestConstructor();
	
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();

	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();

	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}

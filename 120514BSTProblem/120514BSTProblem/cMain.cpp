#include "cMain.h"
#include "cBSTree.h"
#include "cParser.h"


cMain::cMain()
{
}


cMain::~cMain()
{
}

int main(){

	cParser g;
	g.loadFromFile("bst_data.txt");
	/*cBSTree bst;
	bst.insert(5);
	bst.insert(3);
	bst.insert(8);
	bst.insert(1);
	bst.insert(10);
	bst.insert(2);
	bst.insert(9);
	bst.insert(4);
	bst.insert(7);
	bst.insert(6);
	bst.print();

	bst.deleteMin();
	bst.print(); 
	bst.deleteMin();
	bst.print();
	bst.deleteMin();
	bst.print();

	bst.deleteByValue(8);
	bst.print();

	bst.deleteByValue(5);
	bst.print();*/

	//bst.remove(5);
	//bst.remove(3);

	//bst.print();
}
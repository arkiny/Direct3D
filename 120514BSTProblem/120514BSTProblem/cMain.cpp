#include "cMain.h"
#include "cBSTree.h"


cMain::cMain()
{
}


cMain::~cMain()
{
}

int main(){
	cBSTree bst;
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

	//bst.remove(5);
	//bst.remove(3);

	//bst.print();
}
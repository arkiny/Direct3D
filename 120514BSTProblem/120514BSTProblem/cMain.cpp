#include <Windows.h>
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
	cBSTree bst;
	int aData[1000];

	for (int i = 0; i < 1000; ++i){
		aData[i] = rand() % 1000;
		bst.insert(aData[i]);
	}
	for (int i = 0; i < 1000; ++i){
		int nIndx1 = rand() % 1000;
		int nIndx2 = rand() % 1000;
		int nTemp = aData[nIndx1];
		aData[nIndx1] = aData[nIndx2];
		aData[nIndx2] = nTemp;
	}


	for (int i = 0; i < 1000; ++i){
		bst.deleteByValue(aData[i]);
	}

	bst.insert(1);
	bst.print();
	return 0;
	/*cParser g;
	g.loadFromFile("bst_data.txt");*/
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
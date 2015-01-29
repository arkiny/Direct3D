#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "cGraph.h"
#include "cDjikstraSP.h"
// Indirected Graph Djikstra Prototype
// Graph
//		0	1	2	3	4	5	6	7
//	0	0	2	inf	inf	inf	3	inf	inf
//	1	2	0	4	1	inf	inf	inf	inf
//	2	inf	4	0	3	inf	inf	inf	inf
//	3	inf	1	inf	0
//	4	inf	inf	3		0
//	5	3	inf	inf			0
//	6	inf	inf	inf				0
//	7	inf	inf	inf					0	

void main(){
	cGraph* p = new cGraph(8);
	// setup edge

	p->SetEdge(0, 1, 2.0f);
	p->SetEdge(0, 5, 3.0f);
	p->SetEdge(1, 2, 4.0f);
	p->SetEdge(1, 3, 1.0f);
	p->SetEdge(2, 4, 3.0f);
	p->SetEdge(3, 4, 3.0f);
	p->SetEdge(3, 6, 2.0f);
	p->SetEdge(4, 7, 4.0f);
	p->SetEdge(5, 6, 6.0f);
	p->SetEdge(6, 7, 4.0f);


	//p->SetEdge(2, 1, 2.0f);

	//
	p->ToStringAdjCostTable();
	cDjikstraSP* pdsp = new cDjikstraSP(p, 4, 5);
	pdsp->SetupAndCalculate();
	pdsp->ShortestPathToString();

	delete pdsp;
	delete p;
	system("pause");
}

// initialize
// node
// edge
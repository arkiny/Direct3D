// 020415 PriorityQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "cTile.h"
#include "cPriorityQueue.h"

int _tmain(int argc, _TCHAR* argv[])
{
	
	cTile* p;
	cPriorityQueue pq;

	p = new cTile(0, 0);
	p->SetFGH(100.0f, 0.0f, 0.0f);
	pq.Push(p);

	p = new cTile(0, 0);
	p->SetFGH(50.0f, 0.0f, 0.0f);
	pq.Push(p);

	p = new cTile(0, 0);
	p->SetFGH(70.0f, 0.0f, 0.0f);
	pq.Push(p);

	p = new cTile(0, 0);
	p->SetFGH(80.0f, 0.0f, 0.0f);
	pq.Push(p);

	p = new cTile(0, 0);
	p->SetFGH(30.0f, 0.0f, 0.0f);
	pq.Push(p);

	p = new cTile(0, 0);
	p->SetFGH(60.0f, 0.0f, 0.0f);
	pq.Push(p);

	pq.Pop();
	pq.ToString();
	int a = 0;



	return 0;
}


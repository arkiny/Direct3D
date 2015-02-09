#include "stdafx.h"
#include "cDjikstraSP.h"
#include "cGraph.h"
#include <algorithm>
#include <iostream>

cDjikstraSP::cDjikstraSP() :
m_pGraph(NULL),
m_uiStart(0),
m_uiDestination(0)
{
}


cDjikstraSP::~cDjikstraSP()
{
}

cDjikstraSP::cDjikstraSP(cGraph* pGraph, int uiStartVertex, int uiDestination) :
m_pGraph(pGraph),
m_uiStart(uiStartVertex),
m_uiDestination(uiDestination),
m_vecMoveCost(pGraph->GetNumVertex()),
m_vecVia(pGraph->GetNumVertex()),
m_vecVisted(pGraph->GetNumVertex())
{
	std::fill(std::begin(m_vecMoveCost),	std::end(m_vecMoveCost), 99999.0f);
	std::fill(std::begin(m_vecVia),			std::end(m_vecVia), -1);
	std::fill(std::begin(m_vecVisted),		std::end(m_vecVisted), false);

	for (int i = 0; i < pGraph->GetNumVertex(); i++){
		m_setNotVisitVertex.insert(i);
	}

	m_vecMoveCost[uiStartVertex]			= 0.0f;
	m_vecVisted[uiStartVertex]				= true;
	m_vecVia[uiStartVertex]					= uiStartVertex; 
}

void cDjikstraSP::SetupAndCalculate(){
	if (m_pGraph){
		int CurrentVer = m_uiStart;
		m_setNotVisitVertex.erase(CurrentVer);
		while (!m_setNotVisitVertex.empty()){
			for (size_t i = 0; i < m_pGraph->GetNumVertex(); i++){
				CalculatePathCost(CurrentVer, i);
			}
			CurrentVer = FindLeastCostUnvisitedNode();
			if (CurrentVer == -1){
				break;
			}
		}
	}
	else {
		return;
	}
}

void cDjikstraSP::CalculatePathCost(int from, int to){
	if (m_vecVisted[to] == false && m_pGraph->GetEdgeCost(from, to) < 99999.0f){
		if (m_vecMoveCost[to] > m_vecMoveCost[from] + m_pGraph->GetEdgeCost(from, to)){
			m_vecMoveCost[to] = m_vecMoveCost[from] + m_pGraph->GetEdgeCost(from, to);
			m_vecVia[to] = from;
		}
	}
}

int cDjikstraSP::FindLeastCostUnvisitedNode(){
	int ret = -1;
	for (size_t i = 0; i < m_pGraph->GetNumVertex(); i++){
		if (ret == -1 && m_vecVisted[i] == false){
			ret = i;
		}
		else if(m_vecVisted[i] == false){
			if (m_vecMoveCost[i] < m_vecMoveCost[ret]){
				ret = i;				
			}
		}		 
	}
	if (ret == -1){
		return ret;
	}
	m_vecVisted[ret] = true;
	m_setNotVisitVertex.erase(ret);
	return ret;
}


void cDjikstraSP::ShortestPathToString(){
	int node = m_uiDestination;
	float cost = m_vecMoveCost[node];
	while (m_uiStart != node){
		std::cout << node << std::endl;
		node = m_vecVia[node];
		
	}
	//cost += m_vecMoveCost[node];
	std::cout << node << std::endl;

	std::cout << "Total Cost : " << cost << std::endl;
}


void cDjikstraSP::GetShortestPathAsVector(OUT std::vector<int>& path){
	int node = m_uiDestination;
	while (m_uiStart != node){
		path.push_back(node);
		node = m_vecVia[node];
	}
	//cost += m_vecMoveCost[node];
	path.push_back(node);
	std::reverse(path.begin(), path.end());
}
#pragma once
#include <vector>
#include <set>

class cGraph;

class cDjikstraSP
{
private:
	// visited, via, MoveCost
	cGraph*						m_pGraph;
	int							m_uiStart;
	int							m_uiDestination;
	
	//
	std::vector<bool>			m_vecVisted;

	//Last Edge
	std::vector<int>			m_vecVia;

	//DistTo
	std::vector<float>			m_vecMoveCost;

	std::set<int>				m_setNotVisitVertex;


public:
	cDjikstraSP();
	~cDjikstraSP();

	cDjikstraSP(cGraph* pGraph, int uiStartVertex, int uiDestination);
	void SetupAndCalculate();

	void CalculatePathCost(int from, int to);

	int FindLeastCostUnvisitedNode();

	void ShortestPathToString();

	void GetShortestPathAsVector(OUT std::vector<int>& path);
};


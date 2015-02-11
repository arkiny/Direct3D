#pragma once
#include <vector>
class cAPoint;
class cGraph
{
private:
	// Num of Vertexed
	int				m_uiNumVertex;
	// Edge Costs
	std::vector<float>			m_vecAdj;

public:
	cGraph();
	~cGraph();

	cGraph(int uiNumofVertex);

	void SetEdge(int uiFrom, int uiTo, float cost);
	// overload
	void setEdge(int nfrom, int nTo, std::vector<cAPoint*>& src);

	void ToStringAdjCostTable();

	float GetEdgeCost(int uiFrom, int uiTo);
	unsigned int GetNumVertex(){ return m_uiNumVertex; }
};


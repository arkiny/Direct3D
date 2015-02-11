#include "stdafx.h"
#include "cGraph.h"
#include "cAPoint.h"
#include <iostream>


cGraph::cGraph():
m_uiNumVertex(0)
{
}


cGraph::~cGraph()
{
}

cGraph::cGraph(int uiNumofVertex):
m_uiNumVertex(uiNumofVertex),
m_vecAdj(uiNumofVertex * uiNumofVertex)
{
	//memset(&m_vecAdj[0], 9999, m_vecAdj.size());
	// Indirected Graph
	std::fill(std::begin(m_vecAdj), std::end(m_vecAdj), 99999.0f);
	for (unsigned int i = 0; i < m_uiNumVertex; i++){
		m_vecAdj[(i*m_uiNumVertex) + i] = 0;
	}
}

void cGraph::SetEdge(int uiFrom, int uiTo, float cost){
	m_vecAdj[(uiFrom*m_uiNumVertex) + uiTo] = cost;
	m_vecAdj[(uiTo*m_uiNumVertex) + uiFrom] = cost;
}

void cGraph::setEdge(int nfrom, int nTo, std::vector<cAPoint*>& src){
	D3DXVECTOR3 tolength = src[nfrom]->GetTransform()->GetPosition() - src[nTo]->GetTransform()->GetPosition();
	float		weight = fabs(D3DXVec3Length(&tolength));
	SetEdge(nfrom, nTo, weight);
}

void cGraph::ToStringAdjCostTable(){
	for (size_t y = 0; y < m_uiNumVertex; y++){
		for (size_t x = 0; x < m_uiNumVertex; x++){
			std::cout << m_vecAdj[(y*m_uiNumVertex) + x] << "\t";
		}
		std::cout << std::endl;
	}
}

float cGraph::GetEdgeCost(int uiFrom, int uiTo){
	return m_vecAdj[(uiFrom*m_uiNumVertex) + uiTo];
}

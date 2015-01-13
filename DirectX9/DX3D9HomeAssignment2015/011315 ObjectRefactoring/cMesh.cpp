#include "stdafx.h"
#include "cMesh.h"
#include "cGroup.h"
#include "cMtlTex.h"

cMesh::cMesh()
	: m_pMesh(NULL)
{
}


cMesh::~cMesh()
{
	SAFE_RELEASE(m_pMesh);
}


void cMesh::init(){
	std::map<std::string, int>	mtlList;	
	std::vector<int>			subSet;
	
	int nAccumSubSetNum = 0;
	DWORD dAccumVertexNum = 0;
	DWORD dAccumFaceNum = 0;

	// subset check and vertex calculating
	std::vector<ST_PNT_VERTEX> vecVertices;
	for (auto pG : m_vecGroup){
		int nSubSetNum;
		if (mtlList.count(pG->GetMtlTex()->sMtlName) == 0){
			mtlList[pG->GetMtlTex()->sMtlName] = nAccumSubSetNum;
			m_mapMtlData[nAccumSubSetNum] = pG->GetMtlTex();			
			nSubSetNum = nAccumSubSetNum;
			nAccumSubSetNum++;
		}
		else{
			nSubSetNum = mtlList.at(pG->GetMtlTex()->sMtlName);
		}
		dAccumVertexNum += pG->m_vecVertex.size();
		for (size_t i = 0; i < pG->m_vecVertex.size(); i++)
		{
			vecVertices.push_back(pG->m_vecVertex[i]);
			subSet.push_back(nSubSetNum);
		}
	}


	dAccumFaceNum = dAccumVertexNum / 3;

	HRESULT hr = D3DXCreateMeshFVF(
		dAccumFaceNum,
		dAccumVertexNum,
		D3DXMESH_MANAGED,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pMesh);

	_ASSERT(hr == S_OK);
/*
	ST_PT_VERTEX* buffv;

	memcpy(buffv, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PT_VERTEX));*/

	ST_PNT_VERTEX* v = 0;
	m_pMesh->LockVertexBuffer(0, (void**)&v);
	//for (int i = 0; i < vecVertices.size(); i++){
	//	v[i] = vecVertices[i];
	//}
	memcpy(v, &vecVertices[0], vecVertices.size() * sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();

	WORD* di = 0;
	m_pMesh->LockIndexBuffer(0, (void**)&di);
	//std::vector<int> check;
	for (UINT i = 0; i < vecVertices.size(); i++){
		di[i] = i;
	}
	m_pMesh->UnlockIndexBuffer();

	DWORD* attributeBuffer = 0;
	m_pMesh->LockAttributeBuffer(0, &attributeBuffer);
	
	int j = 0;
	for (UINT i = 0; i < dAccumFaceNum; i++){
		attributeBuffer[i] = subSet[j];
		if (j == 0){
			j += 2;
		}
		else {
			j += 3;
		}
		
	}

	m_pMesh->UnlockAttributeBuffer();


	//DWORD adjacenyInfo;
	//std::vector<DWORD> adjacencyBuffer(m_pMesh->GetNumFaces() * 3);
	/*UINT a = adjacencyBuffer.max_size() / (sizeof(DWORD) * m_pMesh->GetNumVertices());
	UINT b = sizeof(DWORD) * m_pMesh->GetNumVertices();*/
	//adjacencyBuffer.resize();

	std::vector<DWORD> adjacencyBuffer(m_pMesh->GetNumFaces() * 3);
	m_pMesh->GenerateAdjacency(0.00001f, &adjacencyBuffer[0]);

	hr = m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&adjacencyBuffer[0],
		0, 0, 0);
}

void cMesh::render(){
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	for (DWORD i = 0; i < m_mapMtlData.size(); i++){
		g_pD3DDevice->SetTexture(0, m_mapMtlData[i]->pTex);
		g_pD3DDevice->SetMaterial(&m_mapMtlData[i]->stMtl);
		m_pMesh->DrawSubset(i);
	}	
}
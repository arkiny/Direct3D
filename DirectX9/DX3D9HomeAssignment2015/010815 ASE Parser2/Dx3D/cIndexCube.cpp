#include "StdAfx.h"
#include "cIndexCube.h"


cIndexCube::cIndexCube(void)
	: m_pVB(NULL)
	, m_pIB(NULL)
	, m_nNumTri(0)
{
}


cIndexCube::~cIndexCube(void)
{
	SAFE_RELEASE(m_pIB);
	SAFE_RELEASE(m_pVB);
}

void cIndexCube::Setup()
{
	std::vector<ST_PC_VERTEX>	vecVertex;

	ST_PC_VERTEX v;
	
	v.c = D3DCOLOR_XRGB(255, 0, 0);

	v.p = D3DXVECTOR3(-1, -1, -1);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1,  1, -1);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1,  1, -1);
	vecVertex.push_back(v);
	
	v.p = D3DXVECTOR3( 1, -1, -1);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1,  1);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1,  1,  1);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1,  1,  1);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1,  1);
	vecVertex.push_back(v);

	g_pD3DDevice->CreateVertexBuffer(
		vecVertex.size() * sizeof(ST_PC_VERTEX),
		0,
		ST_PC_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		0);

	ST_PC_VERTEX* pV;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PC_VERTEX));
	m_pVB->Unlock();

	m_nNumVertex = vecVertex.size();

	std::vector<WORD> vecIndex;
	
	vecIndex.push_back(0);
	vecIndex.push_back(1);
	vecIndex.push_back(2);
	vecIndex.push_back(0);
	vecIndex.push_back(2);
	vecIndex.push_back(3);
	vecIndex.push_back(4);
	vecIndex.push_back(6);
	vecIndex.push_back(5);
	vecIndex.push_back(4);
	vecIndex.push_back(7);
	vecIndex.push_back(6);
	vecIndex.push_back(4);
	vecIndex.push_back(5);
	vecIndex.push_back(1);
	vecIndex.push_back(4);
	vecIndex.push_back(1);
	vecIndex.push_back(0);
	vecIndex.push_back(3);
	vecIndex.push_back(2);
	vecIndex.push_back(6);
	vecIndex.push_back(3);
	vecIndex.push_back(6);
	vecIndex.push_back(7);
	vecIndex.push_back(1);
	vecIndex.push_back(5);
	vecIndex.push_back(6);
	vecIndex.push_back(1);
	vecIndex.push_back(6);
	vecIndex.push_back(2);
	vecIndex.push_back(4);
	vecIndex.push_back(0);
	vecIndex.push_back(3);
	vecIndex.push_back(4);
	vecIndex.push_back(3);
	vecIndex.push_back(7);

	g_pD3DDevice->CreateIndexBuffer(
		vecIndex.size() * sizeof(WORD),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIB,
		0);

	WORD* pI;
	m_pIB->Lock(0, 0, (LPVOID*)&pI, 0);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(WORD));
	m_pIB->Unlock();

	m_nNumTri = vecIndex.size() / 3;
}

void cIndexCube::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PC_VERTEX));
	g_pD3DDevice->SetIndices(m_pIB);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nNumVertex, 0, m_nNumTri);
}

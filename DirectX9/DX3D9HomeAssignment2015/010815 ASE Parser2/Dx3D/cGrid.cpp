#include "StdAfx.h"
#include "cGrid.h"


void cGrid::cPyramid::Setup(D3DXMATRIXA16& mat, D3DCOLOR c)
{
	std::vector<ST_PC_VERTEX>	m_vecVertex;

	m_matWorld = mat;

	ST_PC_VERTEX v;
	v.c = c;

	v.p = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1,  1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1,  1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1,  1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1,  1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1,  1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1, -1,  1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1,  1);
	m_vecVertex.push_back(v);

	g_pD3DDevice->CreateVertexBuffer(
		m_vecVertex.size() * sizeof(ST_PC_VERTEX),
		0,
		ST_PC_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		0);

	ST_PC_VERTEX* pV;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	memcpy(pV, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PC_VERTEX));
	m_pVB->Unlock();

	m_nNumTri = m_vecVertex.size() / 3;
}

void cGrid::cPyramid::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumTri);
}

cGrid::cGrid(void)
	: m_pVB(NULL)
	, m_nNumLine(0)
{
}

cGrid::~cGrid(void)
{
	SAFE_RELEASE(m_pVB);
	for each (auto p in m_vecPyramid)
	{
		SAFE_DELETE(p);
	}
}

void cGrid::Setup( int nHalfTile, float fWidth )
{
	std::vector<ST_PC_VERTEX>	m_vecVertex;

	float fMin = -nHalfTile * fWidth;
	float fMax = -fMin;

	ST_PC_VERTEX v;

	for (int i = 1; i <= nHalfTile; ++i)
	{
		if(i % 5 == 0)
			v.c = D3DCOLOR_XRGB(255, 255, 255);
		else
			v.c = D3DCOLOR_XRGB(128, 128, 128);

		v.p = D3DXVECTOR3(fMin, 0, i * fWidth);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMax, 0, i * fWidth);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i * fWidth);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMax, 0, -i * fWidth);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i * fWidth, 0, fMin);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i * fWidth, 0, fMax);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i * fWidth, 0, fMin);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i * fWidth, 0, fMax);
		m_vecVertex.push_back(v);
	}

	// xÃà
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(fMin, 0, 0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(fMax, 0, 0);
	m_vecVertex.push_back(v);

	// yÃà
	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, fMin, 0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, fMax, 0);
	m_vecVertex.push_back(v);

	// zÃà
	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0, 0, fMin);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, fMax);
	m_vecVertex.push_back(v);


	g_pD3DDevice->CreateVertexBuffer(
		m_vecVertex.size() * sizeof(ST_PC_VERTEX),
		0,
		ST_PC_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		0);

	ST_PC_VERTEX* pV;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	memcpy(pV, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PC_VERTEX));
	m_pVB->Unlock();

	m_nNumLine = m_vecVertex.size() / 2;


	D3DXMATRIXA16 mat, matS, matR;

	cPyramid* pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.1f, 2.0f, 0.1f);
	mat = matS * matR;
	pPyramid->Setup(mat, D3DCOLOR_XRGB(255, 0, 0));
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	D3DXMatrixScaling(&matS, 0.1f, 2.0f, 0.1f);
	mat = matS * matR;
	pPyramid->Setup(mat, D3DCOLOR_XRGB(0, 255, 0));
	m_vecPyramid.push_back(pPyramid);
	
	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.1f, 2.0f, 0.1f);
	mat = matS * matR;
	pPyramid->Setup(mat, D3DCOLOR_XRGB(0, 0, 255));
	m_vecPyramid.push_back(pPyramid);
}

void cGrid::Render()
{
	
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, 0);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_nNumLine);

	for each (auto p in m_vecPyramid)
	{
		p->Render();
	}
}

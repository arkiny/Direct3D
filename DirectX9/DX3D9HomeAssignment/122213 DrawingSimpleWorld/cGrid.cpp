#include "stdafx.h"
#include "cGrid.h"


cGrid::cGrid() :
m_fLength(0.0f),
m_nGridNum(0) // should be power of 2
{
}


cGrid::~cGrid()
{
}

cGrid::cGrid(float length, int numOfGrid) : 
m_fLength(length),
m_nGridNum(numOfGrid) // should be power of 2
{
}

void cGrid::init(){
	float _fwidth = m_fLength / m_nGridNum;
	ST_PC_VERTEX v;
	for (int i = 0; i < m_nGridNum; i++){
		v.p = D3DXVECTOR3((0.0f - m_fLength / 2.0f + _fwidth*i), 0, 0.0 + m_fLength / 2.0f);
		if (i % 5 == 0){
			v.c = D3DCOLOR_XRGB(255, 255, 255);
		}
		else {
			v.c = D3DCOLOR_XRGB(100, 100, 100);
		}
		m_vecVertexLineXGrid.push_back(v);
		v.p = D3DXVECTOR3((0.0f - m_fLength / 2.0f + _fwidth*i), 0, 0.0 - m_fLength / 2.0f);
		m_vecVertexLineXGrid.push_back(v);
	}

	for (int i = 0; i < m_nGridNum; i++){
		v.p = D3DXVECTOR3(0.0 + m_fLength / 2.0f, 0, (0.0f - m_fLength / 2.0f + _fwidth*i));
		if (i % 5 == 0){
			v.c = D3DCOLOR_XRGB(255, 255, 255);
		}
		else {
			v.c = D3DCOLOR_XRGB(100, 100, 100);
		}
		m_vecVertexLineZGrid.push_back(v);
		v.p = D3DXVECTOR3(0.0 - m_fLength / 2.0f, 0, (0.0f - m_fLength / 2.0f + _fwidth*i));
		m_vecVertexLineZGrid.push_back(v);
	}
}

void cGrid::render(){
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertexLineXGrid.size() / 2,
		&m_vecVertexLineXGrid[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertexLineZGrid.size() / 2,
		&m_vecVertexLineZGrid[0],
		sizeof(ST_PC_VERTEX));
}
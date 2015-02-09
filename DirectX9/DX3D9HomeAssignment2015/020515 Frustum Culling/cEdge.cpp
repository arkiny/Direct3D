#include "stdafx.h"
#include "cEdge.h"


cEdge::cEdge()
{
}


cEdge::~cEdge()
{
}

void cEdge::Setup(D3DXVECTOR3 from, D3DXVECTOR3 to){
	ST_PC_VERTEX v;
	v.p = from;
	v.c = D3DXCOLOR(0.6f, 0.6f, 0.2f, 1.0f);
	m_vecVertex.push_back(v);

	v.p = to;
	v.c = D3DXCOLOR(0.6f, 0.6f, 0.2f, 1.0f);
	m_vecVertex.push_back(v);
}

void cEdge::Render(){
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_LINELIST,
		m_vecVertex.size() / 2,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
}
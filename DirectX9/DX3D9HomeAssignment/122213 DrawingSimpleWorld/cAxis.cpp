#include "stdafx.h"
#include "cAxis.h"

cAxis::cAxis() :
m_fEdgeLength(0.0f)
{
}

cAxis::cAxis(float flength) :
m_fEdgeLength(flength)
{

}

cAxis::~cAxis()
{
}

void cAxis::init(){
	ST_PC_VERTEX v;
	//X Axis
	v.p = D3DXVECTOR3(0.0f - m_fEdgeLength / 2.0f, 0, 0);
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	m_vecVertexLineXAxis.push_back(v);
	v.p = D3DXVECTOR3(0.0f + m_fEdgeLength / 2.0f, 0, 0);
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	m_vecVertexLineXAxis.push_back(v);
	//Y Axis
	v.p = D3DXVECTOR3(0, 0.0f - m_fEdgeLength / 2.0f, 0);
	v.c = D3DCOLOR_XRGB(0, 255, 0);
	m_vecVertexLineYAxis.push_back(v);
	v.p = D3DXVECTOR3(0, 0.0f + m_fEdgeLength / 2.0f, 0);
	v.c = D3DCOLOR_XRGB(0, 255, 0);
	m_vecVertexLineYAxis.push_back(v);
	//Z Axis
	v.p = D3DXVECTOR3(0, 0, 0.0f - m_fEdgeLength / 2.0f);
	v.c = D3DCOLOR_XRGB(0, 0, 255);
	m_vecVertexLineZAxis.push_back(v);
	v.p = D3DXVECTOR3(0, 0, 0.0f + m_fEdgeLength / 2.0f);
	v.c = D3DCOLOR_XRGB(0, 0, 255);
	m_vecVertexLineZAxis.push_back(v);

	// pyramid
	std::vector<ST_PC_VERTEX> original_payrimid;
	v.p = D3DXVECTOR3(0, 0, 0);
	v.c = D3DCOLOR_XRGB(0, 255, 0);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(-1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(1, -4, 1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(-1, -4, 1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(1, -4, 1);
	original_payrimid.push_back(v);


	v.p = D3DXVECTOR3(0, 0, 0);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(-1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(-1, -4, 1);
	original_payrimid.push_back(v);


	v.p = D3DXVECTOR3(-1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(-1, -4, 1);
	original_payrimid.push_back(v);


	v.p = D3DXVECTOR3(1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(1, -4, 1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(-1, -4, 1);
	original_payrimid.push_back(v);

	D3DXMATRIXA16 matRotate;
	D3DXMATRIXA16 matScaling;
	D3DXMATRIXA16 matFinal;
	D3DXVECTOR4 new_vec4;
	D3DXMatrixScaling(&matScaling, 0.2f, 0.2f, 0.2f);
	for (UINT i = 0; i < original_payrimid.size(); i++){
		original_payrimid[i].c = D3DCOLOR_XRGB(0, 255, 0);
		D3DXVec3Transform(&new_vec4, &original_payrimid[i].p, &matScaling);
		original_payrimid[i].p = D3DXVECTOR3(new_vec4.x, new_vec4.y, new_vec4.z);
	}
	m_vecVertexLineYPyramid = original_payrimid;

	
	
	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(270.0f));
	
	matFinal = matRotate;
	for (UINT i = 0; i < original_payrimid.size(); i++){
		original_payrimid[i].c = D3DCOLOR_XRGB(255, 0, 0);
		D3DXVec3Transform(&new_vec4, &original_payrimid[i].p, &matFinal);
		original_payrimid[i].p = D3DXVECTOR3(new_vec4.x, new_vec4.y, new_vec4.z);
	}
	m_vecVertexLineXPyramid = original_payrimid;

	D3DXMatrixIdentity(&matRotate);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(270.0f));
	for (UINT i = 0; i < original_payrimid.size(); i++){
		original_payrimid[i].c = D3DCOLOR_XRGB(0, 0, 255);
		D3DXVec3Transform(&new_vec4, &original_payrimid[i].p, &matRotate);
		original_payrimid[i].p = D3DXVECTOR3(new_vec4.x, new_vec4.y, new_vec4.z);
	}
	m_vecVertexLineZPyramid = original_payrimid;
	//m_vecVertexLineZPyramid;*/
}

void cAxis::render(){
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertexLineXAxis.size() / 2,
		&m_vecVertexLineXAxis[0],
		sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertexLineYAxis.size() / 2,
		&m_vecVertexLineYAxis[0],
		sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertexLineZAxis.size() / 2,
		&m_vecVertexLineZAxis[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertexLineXPyramid.size() / 3,
		&m_vecVertexLineXPyramid[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertexLineYPyramid.size() / 3,
		&m_vecVertexLineYPyramid[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertexLineZPyramid.size() / 3,
		&m_vecVertexLineZPyramid[0],
		sizeof(ST_PC_VERTEX));

	//std::vector<ST_PC_VERTEX>	m_vecVertexLineXAxis;
	//std::vector<ST_PC_VERTEX>	m_vecVertexLineYAxis;
	//std::vector<ST_PC_VERTEX>	m_vecVertexLineZAxis;
}

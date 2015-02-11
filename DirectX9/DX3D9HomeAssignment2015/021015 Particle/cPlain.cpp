#include "stdafx.h"
#include "cPlain.h"


cPlain::cPlain() 
{
	ZeroMemory(&m_stMaterial, sizeof(m_stMaterial));
}


cPlain::~cPlain()
{
}

void cPlain::Setup(){
	m_stMaterial.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_stMaterial.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_stMaterial.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	ST_PN_VERTEX v;
	v.n = D3DXVECTOR3(0, 1.0f, 0);
	v.p = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	m_vecVertices.push_back(v);

	v.n = D3DXVECTOR3(0, 1.0f, 0);
	v.p = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
	m_vecVertices.push_back(v);
	
	v.n = D3DXVECTOR3(0, 1.0f, 0);
	v.p = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	m_vecVertices.push_back(v);

	
	
	v.n = D3DXVECTOR3(0, 1.0f, 0);
	v.p = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
	m_vecVertices.push_back(v);

	v.n = D3DXVECTOR3(0, 1.0f, 0);
	v.p = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	m_vecVertices.push_back(v);
	
	v.n = D3DXVECTOR3(0, 1.0f, 0);
	v.p = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	m_vecVertices.push_back(v);

	m_vecPoints.resize(m_vecVertices.size());
	for (size_t i = 0; i < m_vecVertices.size(); i++){
		m_vecPoints[i] = m_vecVertices[i].p;
	}
}

void cPlain::Render(){
	D3DXMATRIXA16 matWorld, matT;
	D3DXMatrixIdentity(&matT);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matT);
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDevice->SetMaterial(&m_stMaterial);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertices.size() / 3,
		&m_vecVertices[0],
		sizeof(ST_PN_VERTEX));

	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
}

float cPlain::GetHeight(OUT bool& isLand, IN D3DXVECTOR3* pvPosition){
	return 0.0f;
}

std::vector<D3DXVECTOR3>& cPlain::GetVerticesPoints(){
	return m_vecPoints;
}
#include "stdafx.h"
#include "cObject.h"


cObject::cObject()
	:m_pTexture(NULL)
{
	ZeroMemory(&m_stMaterial, sizeof(D3DMATERIAL9));
	m_vecVertex.clear();
	D3DXMatrixIdentity(&m_worldMat);
}


cObject::~cObject()
{
	SAFE_RELEASE(m_pTexture); 
}

void cObject::setup(LPDIRECT3DTEXTURE9 texture, D3DMATERIAL9& mat, std::vector<ST_PNT_VERTEX>& vecVertex){
	m_pTexture = texture;
	m_pTexture->AddRef();
	m_stMaterial = mat;
	m_vecVertex = vecVertex;
}

void cObject::update(float delta){

}

void cObject::render(){
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_worldMat);

	
	m_stMaterial.Emissive = D3DXCOLOR(0, 0, 0, 1.0f);
	m_stMaterial.Power = 5.0f;

	g_pD3DDevice->SetMaterial(&m_stMaterial);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PNT_VERTEX));	

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	//reset
	D3DXMATRIXA16  matWorld;
	D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixRotationX(&matWorld, D3DXToRadian(90.0f));
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
}
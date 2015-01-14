#include "stdafx.h"
#include "cAPoint.h"
#include "cTransform.h"

cAPoint::cAPoint()
	:m_pMesh(NULL)	
{
	ZeroMemory(&m_stMtl, sizeof(m_stMtl));
}


cAPoint::~cAPoint()
{
	SAFE_RELEASE(m_pMesh);
}

void cAPoint::Setup(D3DXCOLOR& c, D3DXVECTOR3& pos){
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMesh, NULL);
	m_pTransform->SetPosition(pos);
	m_stMtl.Ambient = c;
	m_stMtl.Diffuse = c;
	m_stMtl.Specular = c;
}

void cAPoint::Update(float delta){
	// currently do nothing
}

void cAPoint::Render(){
	D3DXMATRIXA16 matReset;
	D3DXMatrixIdentity(&matReset);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matReset);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, GetTransformMatrix());
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(0, NULL);
	m_pMesh->DrawSubset(0);
}
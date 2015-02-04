#include "stdafx.h"
#include "cSphere.h"


cSphere::cSphere() :
m_pMesh(NULL),
m_fRadius(0.5f)
{
	ZeroMemory(&m_stMaterialNoneSelected, sizeof(m_stMaterialNoneSelected));
	ZeroMemory(&m_stMaterialSelected, sizeof(m_stMaterialSelected));
}


cSphere::~cSphere()
{
	SAFE_RELEASE(m_pMesh);
}

void cSphere::Setup(){
	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pMesh, 0);
	m_stMaterialNoneSelected.Ambient = D3DXCOLOR(.2f, .8f, .2f, 1.0f);
	m_stMaterialNoneSelected.Diffuse = D3DXCOLOR(.2f, .8f, .2f, 1.0f);
	m_stMaterialNoneSelected.Specular = D3DXCOLOR(.2f, .8f, .2f, 1.0f);
	m_stMaterialSelected.Ambient = D3DXCOLOR(.8f, .2f, .2f, 1.0f);
	m_stMaterialSelected.Diffuse = D3DXCOLOR(.8f, .2f, .2f, 1.0f);
	m_stMaterialSelected.Specular = D3DXCOLOR(.8f, .2f, .2f, 1.0f);
}

void cSphere::Render(){
#ifdef _DEBUG
	D3DXMATRIXA16 matR, matT;
	matT = *GetTransformMatrix();
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXMATRIXA16 matWorld = matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	if (m_bSelected){
		g_pD3DDevice->SetMaterial(&m_stMaterialSelected);
	}
	else {
		g_pD3DDevice->SetMaterial(&m_stMaterialNoneSelected);
	}
	g_pD3DDevice->SetTexture(0, NULL);

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pMesh->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
#endif // _DEBUG
}
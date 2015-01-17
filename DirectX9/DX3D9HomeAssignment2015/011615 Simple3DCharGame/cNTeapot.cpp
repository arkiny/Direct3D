#include "stdafx.h"
#include "cNTeapot.h"
#include "cActionMove.h"
#include "cTransform.h"

cNTeapot::cNTeapot() 
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pMesh, NULL);
	ZeroMemory(&m_stMtl, sizeof(m_stMtl));
}

cNTeapot::~cNTeapot()
{
	SAFE_RELEASE(m_pMesh);
}

void cNTeapot::Setup(D3DXCOLOR c)
{
	m_stMtl.Ambient = c;
	m_stMtl.Diffuse = c;
	m_stMtl.Specular = c;
	
}

void cNTeapot::Render()
{
	D3DXMATRIXA16 matR, matT;
	matT = *GetTransformMatrix();
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXMATRIXA16 matWorld = matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(0, NULL);
	m_pMesh->DrawSubset(0);
}


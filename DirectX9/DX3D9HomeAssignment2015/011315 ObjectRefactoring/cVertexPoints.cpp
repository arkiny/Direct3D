#include "stdafx.h"
#include "cVertexPoints.h"
#include "cMtlTex.h"

cVertexPoints::cVertexPoints()
	:m_pMtlTex(NULL),
	m_pSphereMesh(NULL)
{
}


cVertexPoints::~cVertexPoints()
{
	SAFE_RELEASE(m_pMtlTex);
	SAFE_RELEASE(m_pSphereMesh);
}

D3DXVECTOR3& cVertexPoints::getPointAt(int a){
	if (a < 0 && a > 6){
		exit(1);
	}
	return m_arrPoints[a];
}

void cVertexPoints::setup(){
	m_pMtlTex = new cMtlTex;
	m_pMtlTex->pTex = NULL;
	m_pMtlTex->stMtl.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_pMtlTex->stMtl.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_pMtlTex->stMtl.Specular = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_pMtlTex->stMtl.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_pMtlTex->stMtl.Power = 5.0f;

	m_arrPoints[0] = D3DXVECTOR3(0, 0, 5.0f);
	D3DXMATRIXA16 matRotY;
	for (int i = 1; i < 6; i++){
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(360.0f / 6.0f * i));
		D3DXVec3TransformCoord(&m_arrPoints[i], &m_arrPoints[0], &matRotY);
	}
	D3DXCreateSphere(g_pD3DDevice, 0.1f, 10, 10, &m_pSphereMesh, NULL);
}

void cVertexPoints::render(){
	D3DXMATRIXA16 mat, matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_pMtlTex->stMtl);

	for (int i = 0; i < 6 ; i++){
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
		D3DXMatrixTranslation(&mat, m_arrPoints[i].x, m_arrPoints[i].y, m_arrPoints[i].z);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
		m_pSphereMesh->DrawSubset(0);
	}
}
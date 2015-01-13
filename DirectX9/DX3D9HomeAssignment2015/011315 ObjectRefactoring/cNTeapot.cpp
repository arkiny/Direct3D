#include "stdafx.h"
#include "cNTeapot.h"
#include "cActionMove.h"
#include "cTransform.h"

cNTeapot::cNTeapot() :
m_pCurrAction(NULL)
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pMesh, NULL);
	ZeroMemory(&m_stMtl, sizeof(m_stMtl));
}

cNTeapot::~cNTeapot()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_DELETE(m_pCurrAction);
}

void cNTeapot::Setup(D3DXCOLOR c)
{
	m_stMtl.Ambient = c;
	m_stMtl.Diffuse = c;
	m_stMtl.Specular = c;
	
	m_pCurrAction = new cActionMove;
	D3DXVECTOR3 cur = m_pTransform->GetPosition();	
}

void cNTeapot::SetTargetList(const std::vector<D3DXVECTOR3>& vecP){
	m_vecTargetList = vecP;
	((cActionMove*)m_pCurrAction)->SetFrom(m_vecTargetList[0]);
	((cActionMove*)m_pCurrAction)->SetTo(m_vecTargetList[1]);
}

void cNTeapot::SetNextTarget(){
	m_nCurrentIndex++;
	m_nTargetIndex++;
	((cActionMove*)m_pCurrAction)->SetFrom(m_vecTargetList[m_nCurrentIndex % 6]);
	((cActionMove*)m_pCurrAction)->SetTo(m_vecTargetList[m_nTargetIndex % 6]);
	if (m_nCurrentIndex % 6 == 0)	m_nCurrentIndex = 0;
	if (m_nTargetIndex % 6 == 0)	m_nTargetIndex = 0;
}

void cNTeapot::Update(float delta){
	m_pCurrAction->Update(delta, this);
}

void cNTeapot::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, GetTransformMatrix());
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(0, NULL);
	m_pMesh->DrawSubset(0);
}


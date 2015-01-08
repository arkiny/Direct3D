#include "StdAfx.h"
#include "cCube.h"


cCube::cCube(void)
	: m_pTexture(NULL)
	, m_fAngle(0.0f)
	, m_fAngleSpeed(0.0f)
{
	D3DXMatrixIdentity(&m_matPrevT);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matPostT);
	D3DXMatrixIdentity(&m_matWorldTM);
}


cCube::~cCube(void)
{
	SAFE_RELEASE(m_pTexture);
}

void cCube::Setup(float fWidth, float fHeight, float fDepth)
{
	ST_PNT_VERTEX v;
	
	// 전
	v.n = D3DXVECTOR3(0, 0, -1);
	v.t = D3DXVECTOR2(0.75f, 0.25f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f,  fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(1.00f, 0.25f);
	v.p = D3DXVECTOR3( fWidth / 2.0f,  fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(1.00f, 0.75f);
	v.p = D3DXVECTOR3( fWidth / 2.0f, -fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.75f, 0.25f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f,  fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(1.00f, 0.75f);
	v.p = D3DXVECTOR3( fWidth / 2.0f, -fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.75f, 0.75f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f, -fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	// 후
	v.n = D3DXVECTOR3(0, 0, 1);

	v.t = D3DXVECTOR2(0.25f, 0.25f);
	v.p = D3DXVECTOR3( fWidth / 2.0f,  fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.50f, 0.25f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f,  fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.50f, 0.75f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f, -fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.25f, 0.25f);
	v.p = D3DXVECTOR3( fWidth / 2.0f,  fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.50f, 0.75f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f, -fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.25f, 0.75f);
	v.p = D3DXVECTOR3( fWidth / 2.0f, -fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	// 상
	v.n = D3DXVECTOR3(0, 1, 0);
	v.t = D3DXVECTOR2(0.25f, 0.00f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f,  fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.50f, 0.00f);
	v.p = D3DXVECTOR3( fWidth / 2.0f,  fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.50f, 0.25f);
	v.p = D3DXVECTOR3( fWidth / 2.0f,  fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.25f, 0.00f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f,  fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.50f, 0.25f);
	v.p = D3DXVECTOR3( fWidth / 2.0f,  fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.25f, 0.25f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f,  fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);


	// 하
	v.n = D3DXVECTOR3(0, -1, 0);
	v.t = D3DXVECTOR2(0.25f, 0.75f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f, -fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.50f, 0.75f);
	v.p = D3DXVECTOR3( fWidth / 2.0f, -fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.50f, 1.00f);
	v.p = D3DXVECTOR3( fWidth / 2.0f, -fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.25f, 0.75f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f, -fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.50f, 1.00f);
	v.p = D3DXVECTOR3( fWidth / 2.0f, -fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.25f, 1.00f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f, -fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	// 좌
	v.n = D3DXVECTOR3(-1, 0, 0);
	v.t = D3DXVECTOR2(0.50f, 0.25f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f,  fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.75f, 0.25f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f,  fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.75f, 0.75f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f, -fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.50f, 0.25f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f,  fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.75f, 0.75f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f, -fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.50f, 0.75f);
	v.p = D3DXVECTOR3(-fWidth / 2.0f, -fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	// 우
	v.n = D3DXVECTOR3(1, 0, 0);
	v.t = D3DXVECTOR2(0.00f, 0.25f);
	v.p = D3DXVECTOR3( fWidth / 2.0f,  fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.25f, 0.25f);
	v.p = D3DXVECTOR3( fWidth / 2.0f,  fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.25f, 0.75f);
	v.p = D3DXVECTOR3( fWidth / 2.0f, -fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.00f, 0.25f);
	v.p = D3DXVECTOR3( fWidth / 2.0f,  fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.25f, 0.75f);
	v.p = D3DXVECTOR3( fWidth / 2.0f, -fHeight / 2.0f,  fDepth / 2.0f);
	m_vecVertex.push_back(v);

	v.t = D3DXVECTOR2(0.00f, 0.75f);
	v.p = D3DXVECTOR3( fWidth / 2.0f, -fHeight / 2.0f, -fDepth / 2.0f);
	m_vecVertex.push_back(v);
}

void cCube::Update(D3DXMATRIXA16* pmatParentWorld/* = NULL*/)
{
	m_fAngle += m_fAngleSpeed;
	if(m_fAngle < -D3DX_PI / 4.0f)
	{
		m_fAngle = -D3DX_PI / 4.0f;
		m_fAngleSpeed *= -1;
	}

	if(m_fAngle > D3DX_PI / 4.0f)
	{
		m_fAngle = D3DX_PI / 4.0f;
		m_fAngleSpeed *= -1;
	}

	D3DXMatrixRotationX(&m_matRot, m_fAngle);

	m_matWorldTM = m_matPrevT * m_matRot * m_matPostT;
	if(pmatParentWorld)
	{
		m_matWorldTM = m_matWorldTM * (*pmatParentWorld);
	}

	for each (auto p in m_vecChildren)
	{
		p->Update(&m_matWorldTM);
	}
}

void cCube::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	//g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PNT_VERTEX));

	for each (auto p in m_vecChildren)
	{
		p->Render();
	}
}

void cCube::SetTexture( LPDIRECT3DTEXTURE9 pTexture )
{
	pTexture->AddRef();
	m_pTexture = pTexture;
}

void cCube::SetTransform( D3DXMATRIXA16& matPrevT, D3DXMATRIXA16& matPostT )
{
	m_matPrevT = matPrevT;
	m_matPostT = matPostT;
}

void cCube::AddChild( cCube* pChild )
{
	m_vecChildren.push_back(pChild);
}

void cCube::Destroy()
{
	for each (auto p in m_vecChildren)
	{
		p->Destroy();
	}
	delete this;
}

void cCube::SetForcedAngle( float fAngle )
{
	m_fAngle = fAngle;
	for each (auto p in m_vecChildren)
	{
		p->SetForcedAngle(fAngle);
	}
}

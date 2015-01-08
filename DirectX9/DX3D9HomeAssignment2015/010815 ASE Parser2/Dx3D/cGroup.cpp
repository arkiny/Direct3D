#include "StdAfx.h"
#include "cGroup.h"
#include "cMtlTex.h"

cGroup::cGroup(void)
	: m_pMtlTex(NULL)
	, m_pVB(NULL)
	, m_nNumTri(0)
{
}


cGroup::~cGroup(void)
{
	SAFE_RELEASE(m_pMtlTex);
	SAFE_RELEASE(m_pVB);
}

void cGroup::SetMtlTex( cMtlTex* pMtlTex )
{
	if(m_pMtlTex == NULL && pMtlTex != NULL)
	{
		pMtlTex->AddRef();
		m_pMtlTex = pMtlTex;
	}
}

void cGroup::Render()
{
	g_pD3DDevice->SetTexture(0, m_pMtlTex->pTex);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumTri);
}

void cGroup::BuildVB( std::vector<ST_PNT_VERTEX>& vecVertex )
{
	g_pD3DDevice->CreateVertexBuffer(
		vecVertex.size() * sizeof(ST_PNT_VERTEX),
		0,
		ST_PNT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		0);

	ST_PNT_VERTEX* pV;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pVB->Unlock();

	m_nNumTri = vecVertex.size() / 3;
}

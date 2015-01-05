#include "stdafx.h"
#include "cGroup.h"
#include "cMtlTex.h"

cGroup::cGroup(void)
	: m_pMtlTex(NULL)
{
}


cGroup::~cGroup(void)
{
	SAFE_RELEASE(m_pMtlTex);
}

void cGroup::SetMtlTex(cMtlTex* pMtlTex)
{
	if (m_pMtlTex == NULL && pMtlTex != NULL)
	{
		pMtlTex->AddRef();
		m_pMtlTex = pMtlTex;
	}
}

void cGroup::Render()
{
	g_pD3DDevice->SetTexture(0, m_pMtlTex->pTex);
	g_pD3DDevice->SetMaterial(&m_pMtlTex->stMtl);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PNT_VERTEX));

}

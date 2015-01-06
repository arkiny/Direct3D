#include "stdafx.h"
#include "cGroup.h"
#include "cMtlTex.h"

cGroup::cGroup(void)
	: m_pMtlTex(NULL),
	m_pVertexBuffer(NULL)
{
}


cGroup::~cGroup(void)
{
	SAFE_RELEASE(m_pMtlTex);
	SAFE_RELEASE(m_pVertexBuffer);
}

void cGroup::SetMtlTex(cMtlTex* pMtlTex)
{
	if (m_pMtlTex == NULL && pMtlTex != NULL)
	{
		pMtlTex->AddRef();
		m_pMtlTex = pMtlTex;
	}
}

void cGroup::Buffering(){
	g_pD3DDevice->CreateVertexBuffer(
		m_vecVertex.size() * sizeof(ST_PNT_VERTEX),
		D3DUSAGE_WRITEONLY,
		ST_PNT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		0
		)
		;	

	ST_PNT_VERTEX* buffv;
	m_pVertexBuffer->Lock(0, 0, (void**)&buffv, 0);

	for (size_t i = 0; i < m_vecVertex.size(); i++){
		buffv[i] = m_vecVertex[i];
	}

	m_pVertexBuffer->Unlock();
}

void cGroup::Render()
{
	g_pD3DDevice->SetTexture(0, m_pMtlTex->pTex);
	g_pD3DDevice->SetMaterial(&m_pMtlTex->stMtl);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	/*g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PNT_VERTEX));*/
	
	g_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(ST_PNT_VERTEX));
	//g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST,
		0,
		m_vecVertex.size()/3);
}

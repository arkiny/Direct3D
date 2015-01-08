#include "StdAfx.h"
#include "cCircleRHW.h"


cCircleRHW::cCircleRHW(void)
	: m_fRadius(0)
{
}


cCircleRHW::~cCircleRHW(void)
{
}

void cCircleRHW::Setup( D3DXVECTOR2 vCenter, float fRadius )
{
	m_fRadius = fRadius;

	ST_RHWC_VERTEX v;
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	for (int i = 0; i < 360; i += 5)
	{
		v.p = D3DXVECTOR4(0, 0, 0, 0);
		v.p += D3DXVECTOR4(vCenter.x, vCenter.y, 0, 0);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR4(fRadius * cosf(D3DXToRadian(i)), fRadius * sinf(D3DXToRadian(i)), 0, 0);
		v.p += D3DXVECTOR4(vCenter.x, vCenter.y, 0, 0);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR4(fRadius * cosf(D3DXToRadian(i + 5)), fRadius * sinf(D3DXToRadian(i + 5)), 0, 0);
		v.p += D3DXVECTOR4(vCenter.x, vCenter.y, 0, 0);
		m_vecVertex.push_back(v);
	}
}

void cCircleRHW::Render()
{
	g_pD3DDevice->SetFVF(ST_RHWC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_RHWC_VERTEX));
}

void cCircleRHW::SetCenter( D3DXVECTOR2 vCenter )
{
	m_vecVertex.clear();

	ST_RHWC_VERTEX v;
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	for (int i = 0; i < 360; i += 5)
	{
		v.p = D3DXVECTOR4(0, 0, 0, 0);
		v.p += D3DXVECTOR4(vCenter.x, vCenter.y, 0, 0);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR4(m_fRadius * cosf(D3DXToRadian(i)), m_fRadius * sinf(D3DXToRadian(i)), 0, 0);
		v.p += D3DXVECTOR4(vCenter.x, vCenter.y, 0, 0);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR4(m_fRadius * cosf(D3DXToRadian(i + 5)), m_fRadius * sinf(D3DXToRadian(i + 5)), 0, 0);
		v.p += D3DXVECTOR4(vCenter.x, vCenter.y, 0, 0);
		m_vecVertex.push_back(v);
	}
}

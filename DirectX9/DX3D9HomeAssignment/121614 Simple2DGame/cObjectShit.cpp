#include "stdafx.h"
#include "cObjectShit.h"
#include "cObjectCircle.h"

cObjectShit::cObjectShit(LPDIRECT3DTEXTURE9 texture)
{
	m_stShitSize = { 60.0, 120.0f };
	m_vPosition = D3DXVECTOR4(static_cast<float>(rand()%400), 0, 0, 1.0f);
	m_fCollisionRad = 30.0f;//¶Ë Ãæµ¹ ¹üÀ§
	m_pTexture = NULL;
	/*m_pColisionCircle = new cObjectCircle(
		D3DXVECTOR4(
		m_vPosition.x,
		m_vPosition.y,
		m_vPosition.z,
		m_vPosition.w),
		m_fCollisionRad);*/
	m_fvelocity = (static_cast<float>(rand() % 300 + 100.0f));
	m_pTexture = texture;
}

cObjectShit::~cObjectShit()
{
	//delete m_pColisionCircle;
}

void cObjectShit::init(){
	ST_RHW_PT_VERTEX v;

	// left top
	v.t = D3DXVECTOR2(0, 0);
	//v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR4(
		m_vPosition.x - (m_stShitSize.x / 2),
		m_vPosition.y - (m_stShitSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
	m_vecVertex.push_back(v);

	// right top
	v.t = D3DXVECTOR2(1, 0);
	//v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR4(
		m_vPosition.x + (m_stShitSize.x / 2),
		m_vPosition.y - (m_stShitSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
	m_vecVertex.push_back(v);

	// right bottom
	v.t = D3DXVECTOR2(1, 1);
	//v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR4(
		m_vPosition.x + (m_stShitSize.x / 2),
		m_vPosition.y + (m_stShitSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
	m_vecVertex.push_back(v);

	// left top
	v.t = D3DXVECTOR2(0, 0);
	//v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR4(
		m_vPosition.x - (m_stShitSize.x / 2),
		m_vPosition.y - (m_stShitSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
	m_vecVertex.push_back(v);

	// right bottom
	v.t = D3DXVECTOR2(1, 1);
	//v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR4(
		m_vPosition.x + (m_stShitSize.x / 2),
		m_vPosition.y + (m_stShitSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
	m_vecVertex.push_back(v);

	// left bottom
	v.t = D3DXVECTOR2(0, 1);
	//v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR4(
		m_vPosition.x - (m_stShitSize.x / 2),
		m_vPosition.y + (m_stShitSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
	m_vecVertex.push_back(v);

	//m_pColisionCircle->init();
	//m_pColisionCircle->ChangeColor(D3DCOLOR_XRGB(255, 0, 0));
}

void cObjectShit::update(float delta){
	m_vPosition.y = m_vPosition.y + (m_fvelocity * delta);
	ChangePosUptoOrigin();
	//m_pColisionCircle->ChangeOrigin(m_vPosition.x, m_vPosition.y);
	//m_pColisionCircle->update(delta);

	if (m_vPosition.y >= 800.0f){
		setPos(static_cast<float>(rand() % 400), 0.0f);
	}
}

void cObjectShit::ChangePosUptoOrigin(){
	// left top
	m_vecVertex[0].p = D3DXVECTOR4(
		m_vPosition.x - (m_stShitSize.x / 2),
		m_vPosition.y - (m_stShitSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);

	// right top
	m_vecVertex[1].p = D3DXVECTOR4(
		m_vPosition.x + (m_stShitSize.x / 2),
		m_vPosition.y - (m_stShitSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);

	// right bottom
	m_vecVertex[2].p = D3DXVECTOR4(
		m_vPosition.x + (m_stShitSize.x / 2),
		m_vPosition.y + (m_stShitSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);

	// left top
	m_vecVertex[3].p = D3DXVECTOR4(
		m_vPosition.x - (m_stShitSize.x / 2),
		m_vPosition.y - (m_stShitSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);

	// right bottom
	m_vecVertex[4].p = D3DXVECTOR4(
		m_vPosition.x + (m_stShitSize.x / 2),
		m_vPosition.y + (m_stShitSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);

	// left bottom
	m_vecVertex[5].p = D3DXVECTOR4(
		m_vPosition.x - (m_stShitSize.x / 2),
		m_vPosition.y + (m_stShitSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
}

void cObjectShit::render(){
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	//
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_RHW_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 6, &m_vecVertex[0], sizeof(ST_RHW_PT_VERTEX));
	//m_pColisionCircle->render();
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

bool cObjectShit::isCollided(const IObject* target){
	float hRange = abs(this->getPos().x - target->getPos().x);
	float vRange = abs(this->getPos().y - target->getPos().y);
	float collidingRange = this->getRad() + target->getRad();
	float range = (hRange*hRange) + (vRange*vRange);
	return range <= collidingRange* collidingRange;
}
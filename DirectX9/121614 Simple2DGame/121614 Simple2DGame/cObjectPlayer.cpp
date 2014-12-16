#include "stdafx.h"
#include "cObjectPlayer.h"
#include "cObjectCircle.h"


cObjectPlayer::cObjectPlayer()
{
	// 플레이어 초기 위치
	m_stPlayerSize = { 36.0f, 91.0f };
	m_vPosition = D3DXVECTOR4(200.f, 600.f, 0, 1.0f);
	m_fCollisionRad = 10.0f;//플레이어 충돌 범위
	m_pTexture = NULL;
	m_pColisionCircle = new cObjectCircle(
		D3DXVECTOR4(
		m_vPosition.x,
		m_vPosition.y,
		m_vPosition.z,
		m_vPosition.w) ,
		m_fCollisionRad);
}


cObjectPlayer::~cObjectPlayer()
{
	delete m_pColisionCircle;
}

void cObjectPlayer::init(){
	D3DXCreateTextureFromFileEx(g_pD3DDevice
		, L"../Resource/pstraight.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 1
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, 0x0000001
		, 0x0000001
		, D3DCOLOR_XRGB(255, 255, 255)
		, NULL
		, NULL
		, &m_pTexture);
	/*D3DXCreateTextureFromFile(
		g_pD3DDevice,
		L"../Resource/pstraight.png",
		&m_pTexture);*/

	ST_RHW_PT_VERTEX v;

	// left top
	v.t = D3DXVECTOR2(0, 0);
	//v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR4(
		m_vPosition.x - (m_stPlayerSize.x / 2),
		m_vPosition.y - (m_stPlayerSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
	m_vecVertex.push_back(v);

	// right top
	v.t = D3DXVECTOR2(1, 0);
	//v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR4(
		m_vPosition.x + (m_stPlayerSize.x / 2),
		m_vPosition.y - (m_stPlayerSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
	m_vecVertex.push_back(v);

	// right bottom
	v.t = D3DXVECTOR2(1, 1);
	//v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR4(
		m_vPosition.x + (m_stPlayerSize.x / 2),
		m_vPosition.y + (m_stPlayerSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
	m_vecVertex.push_back(v);

	// left top
	v.t = D3DXVECTOR2(0, 0);
	//v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR4(
		m_vPosition.x - (m_stPlayerSize.x / 2),
		m_vPosition.y - (m_stPlayerSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
	m_vecVertex.push_back(v);

	// right bottom
	v.t = D3DXVECTOR2(1, 1);
	//v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR4(
		m_vPosition.x + (m_stPlayerSize.x / 2),
		m_vPosition.y + (m_stPlayerSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
	m_vecVertex.push_back(v);

	// left bottom
	v.t = D3DXVECTOR2(0, 1);
	//v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR4(
		m_vPosition.x - (m_stPlayerSize.x / 2),
		m_vPosition.y + (m_stPlayerSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
	m_vecVertex.push_back(v);
	
	m_pColisionCircle->init();
	m_pColisionCircle->ChangeColor(D3DCOLOR_XRGB(0, 0, 255));
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
}

void cObjectPlayer::update(float delta){
	D3DXVECTOR4 temp = m_vPosition;
	if (g_pControl->getKeyControlInfo(VK_LEFT)){
		m_vPosition.x = m_vPosition.x - (200.0f*delta);
	}
	else if (g_pControl->getKeyControlInfo(VK_RIGHT)){
		m_vPosition.x = m_vPosition.x + (200.0f*delta);
	}
	if (temp != m_vPosition){
		ChangePosUptoOrigin();
		m_pColisionCircle->ChangeOrigin(
			m_vPosition.x,
			m_vPosition.y);
	}
	m_pColisionCircle->update(delta);
}

void cObjectPlayer::ChangePosUptoOrigin(){

	// left top
	m_vecVertex[0].p = D3DXVECTOR4(
		m_vPosition.x - (m_stPlayerSize.x / 2),
		m_vPosition.y - (m_stPlayerSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);

	// right top
	m_vecVertex[1].p = D3DXVECTOR4(
		m_vPosition.x + (m_stPlayerSize.x / 2),
		m_vPosition.y - (m_stPlayerSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);

	// right bottom
	m_vecVertex[2].p = D3DXVECTOR4(
		m_vPosition.x + (m_stPlayerSize.x / 2),
		m_vPosition.y + (m_stPlayerSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);

	// left top
	m_vecVertex[3].p = D3DXVECTOR4(
		m_vPosition.x - (m_stPlayerSize.x / 2),
		m_vPosition.y - (m_stPlayerSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);

	// right bottom
	m_vecVertex[4].p = D3DXVECTOR4(
		m_vPosition.x + (m_stPlayerSize.x / 2),
		m_vPosition.y + (m_stPlayerSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);

	// left bottom
	m_vecVertex[5].p = D3DXVECTOR4(
		m_vPosition.x - (m_stPlayerSize.x / 2),
		m_vPosition.y + (m_stPlayerSize.y / 2),
		m_vPosition.z,
		m_vPosition.w);
}

void cObjectPlayer::render(){
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_RHW_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 6, &m_vecVertex[0], sizeof(ST_RHW_PT_VERTEX));
	m_pColisionCircle->render();
}

bool cObjectPlayer::isCollided(const IObject* target){
	float hRange = abs(this->getPos().x - target->getPos().x);
	float vRange = abs(this->getPos().y - target->getPos().y);
	float collidingRange = this->getRad() + target->getRad();
	float range = (hRange*hRange) + (vRange*vRange);
	return range <= collidingRange* collidingRange;
}
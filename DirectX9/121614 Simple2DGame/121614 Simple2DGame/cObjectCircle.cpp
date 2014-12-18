#include <math.h>
#include "stdafx.h"
#include "cObjectCircle.h"


cObjectCircle::cObjectCircle()
{
	m_vOrigin = D3DXVECTOR4(0, 0, 1.0f, 1.0f);
	m_fRad = 0.0f;
	m_stColor = D3DCOLOR_XRGB(255, 255, 255);
	m_pTexture = NULL;
}

cObjectCircle::cObjectCircle(D3DXVECTOR4 origin, float rad){
	m_vOrigin = origin;
	m_fRad = rad;
	m_stColor = D3DCOLOR_XRGB(255, 255, 255);
	m_pTexture = NULL;
	//m_vecVertex.resize(1080);
}


cObjectCircle::~cObjectCircle()
{
}

void cObjectCircle::init(){
	//ST_RHW_VERTEX v;
	//float delta = 360.0f / static_cast<float>(m_nNumOfPoints);
	//float theta = 0.0f + delta;
	////float x = ;
	////float y = sinf(theta);
	//// point 1
	//v.p = m_vOrigin;
	//v.c = m_stColor;
	////v.t = D3DXVECTOR2(0, 0);
	//m_vecVertex.push_back(v);
	//v.p.x = v.p.x + m_fRad * cosf(theta * (PI / 180.0f));
	//v.p.y = v.p.y + m_fRad * sinf(theta * (PI / 180.0f));
	//m_vecVertex.push_back(v);
	//v.p = m_vOrigin;
	//v.p.x = v.p.x + m_fRad;
	//m_vecVertex.push_back(v);
	//v.p.x = v.p.x + m_fRad;
	//for (int i = 0; i < m_nNumOfPoints; i++){
	//	//v.p = m_vOrigin;
	//}

	float delta = 360.0f / static_cast<float>(m_nNumOfPoints);
	float theta = 0.0f + delta;

	ST_RHW_VERTEX v;
	v.c = m_stColor;
	//v.t = D3DXVECTOR2(0, 0);
	v.p = m_vOrigin;
	m_vecVertex.push_back(v);

	//v.c = D3DCOLOR_XRGB(255, 0, 0);
	//v.t = D3DXVECTOR2(1, 1);
	v.p = m_vOrigin;
	v.p.x = m_vOrigin.x + m_fRad;
	m_vecVertex.push_back(v);

	//v.c = D3DCOLOR_XRGB(0, 255, 0);
	//v.t = D3DXVECTOR2(1, 0);
	/*v.p = D3DXVECTOR4(400, 100, 0, 1.0f);*/
	v.p = m_vOrigin;
	v.p.x = m_vOrigin.x + m_fRad * cosf(theta * (PI / 180.0f));
	v.p.y = m_vOrigin.y + m_fRad * sinf(theta * (PI / 180.0f));
	m_vecVertex.push_back(v);

	ST_RHW_VERTEX store = v;

	for (int i = 0; i < m_nNumOfPoints - 1; i++){
		theta += delta;
		v.p = m_vOrigin;
		//v.c = D3DCOLOR_XRGB(0, 0, 255);
		m_vecVertex.push_back(v);

		m_vecVertex.push_back(store);

		v.p.x = m_vOrigin.x + m_fRad * cosf(theta * (PI / 180.0f));
		v.p.y = m_vOrigin.y + m_fRad * sinf(theta * (PI / 180.0f));
		store = v;
		m_vecVertex.push_back(v);
	}
}

void cObjectCircle::update(float delta){
	//for (int i = 0; i < m_vecVertex.size(); i++){
	//	m_vecVertex[i].c = D3DCOLOR_XRGB(m_stuff, m_stuff, m_stuff);
	//}
	//if (m_stuff == 255){
	//	m_neg = m_neg * -1;
	//	m_stuff += m_neg;
	//}
	//else if (m_stuff == 0){
	//	m_neg = m_neg * -1;
	//	m_stuff += m_neg;
	//}
	//else{
	//	m_stuff += 1 * m_neg;
	//}
}

void cObjectCircle::render(){
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_RHW_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_nNumOfPoints, &m_vecVertex[0], sizeof(ST_RHW_VERTEX));
}

void cObjectCircle::ChangeOrigin(float x, float y){
	while (!m_vecVertex.empty()){
		m_vecVertex.pop_back();
	}
	//m_vecVertex.resize(1080);
	m_vOrigin = D3DXVECTOR4(x, y, 0, 1.0f);
	init();
}

void cObjectCircle::ChangeColor(D3DCOLOR color){
	m_stColor = color;
	for (unsigned int i = 0; i < m_vecVertex.size(); i++){
		m_vecVertex[i].c = color;
	}	
}

bool cObjectCircle::isCollide(IObject_Circle* other){
	/*int hRange = abs(_player.getPos().x - _obstacle.getPos().x);
	int vRange = abs(_player.getPos().y - _obstacle.getPos().y);

	int collidingRange = _player.getSize() + _obstacle.getSize();
	int range = (hRange*hRange) + (vRange*vRange);

	return range <= collidingRange*collidingRange;*/

	float hRange = abs(m_vOrigin.x - other->getOrigin().x);
	float vRange = abs(m_vOrigin.y - other->getOrigin().y);
	float collidingRange = m_fRad + other->getRad();
	float range = (hRange*hRange) + (vRange*vRange);
	return range <= collidingRange* collidingRange;
}
#include "stdafx.h"
#include "cObjectRectangle.h"

cObjectRectangle::cObjectRectangle()
{
	m_vOrigin = D3DXVECTOR4(0, 0, 1.0f, 1.0f);
	m_stSize = { 10.0f, 100.0f };
	m_stColor = D3DCOLOR_XRGB(255, 255, 0);
}

cObjectRectangle::cObjectRectangle(D3DXVECTOR4 origin, POINTFLOAT size){
	m_vOrigin = origin;
	m_stSize = size;
	m_stColor = D3DCOLOR_XRGB(255, 255, 0);
}

cObjectRectangle::~cObjectRectangle()
{
	
}

void cObjectRectangle::init(){
	ST_RHW_VERTEX v;
	// left top
	v.p.x = m_vOrigin.x - (m_stSize.x / 2.0f);
	v.p.y = m_vOrigin.y - (m_stSize.y / 2.0f);
	v.c = m_stColor;
	m_vecVertex.push_back(v);

	v.p.x = m_vOrigin.x + (m_stSize.x / 2.0f);
	v.p.y = m_vOrigin.y - (m_stSize.y / 2.0f);
	v.c = m_stColor;
	m_vecVertex.push_back(v);

	v.p.x = m_vOrigin.x + (m_stSize.x / 2.0f);
	v.p.y = m_vOrigin.y + (m_stSize.y / 2.0f);
	v.c = m_stColor;
	m_vecVertex.push_back(v);

	v.p.x = m_vOrigin.x - (m_stSize.x / 2.0f);
	v.p.y = m_vOrigin.y - (m_stSize.y / 2.0f);
	v.c = m_stColor;
	m_vecVertex.push_back(v);

	v.p.x = m_vOrigin.x + (m_stSize.x / 2.0f);
	v.p.y = m_vOrigin.y + (m_stSize.y / 2.0f);
	v.c = m_stColor;
	m_vecVertex.push_back(v);

	v.p.x = m_vOrigin.x - (m_stSize.x / 2.0f);
	v.p.y = m_vOrigin.y + (m_stSize.y / 2.0f);
	v.c = m_stColor;
	m_vecVertex.push_back(v);
}

void cObjectRectangle::updateNewPos(){
	m_vecVertex[0].p.x = m_vOrigin.x - (m_stSize.x / 2.0f);
	m_vecVertex[0].p.y = m_vOrigin.y - (m_stSize.y / 2.0f);
	
	m_vecVertex[1].p.x = m_vOrigin.x + (m_stSize.x / 2.0f);
	m_vecVertex[1].p.y = m_vOrigin.y - (m_stSize.y / 2.0f);
	
	m_vecVertex[2].p.x = m_vOrigin.x + (m_stSize.x / 2.0f);
	m_vecVertex[2].p.y = m_vOrigin.y + (m_stSize.y / 2.0f);
	
	m_vecVertex[3].p.x = m_vOrigin.x - (m_stSize.x / 2.0f);
	m_vecVertex[3].p.y = m_vOrigin.y - (m_stSize.y / 2.0f);
	
	m_vecVertex[4].p.x = m_vOrigin.x + (m_stSize.x / 2.0f);
	m_vecVertex[4].p.y = m_vOrigin.y + (m_stSize.y / 2.0f);
	
	m_vecVertex[5].p.x = m_vOrigin.x - (m_stSize.x / 2.0f);
	m_vecVertex[5].p.y = m_vOrigin.y + (m_stSize.y / 2.0f);
}

void cObjectRectangle::update(float delta){
	if (m_vOrigin.y >= 800.0f){
		setPos(m_vOrigin.x, 0.0f);
	}
	m_vOrigin.y += 600.0f * delta;
	updateNewPos();
}

void cObjectRectangle::render(){
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_RHW_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 6, &m_vecVertex[0], sizeof(ST_RHW_VERTEX));
}

D3DXVECTOR4 cObjectRectangle::getPos() const{
	return m_vOrigin;
}

float cObjectRectangle::getRad() const{
	// no need
	return 0;
}

void cObjectRectangle::setPos(float x, float y){
	m_vOrigin.x = x;
	m_vOrigin.y = y;
	updateNewPos();
}

bool cObjectRectangle::isCollided(const IObject* target){
	// no need
	return false;
}
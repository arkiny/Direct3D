#include "stdafx.h"
#include "cBox.h"


cBox::cBox()
	:m_vPosition(0,0,0),
	m_stGridPosition(0,0,0)
{
}


cBox::~cBox()
{
}

void cBox::init(){
	// rectangle hard corded version
	ST_PC_VERTEX v;

	float left = -0.5f;
	float top = 0.5f;
	float right = 0.5f;
	float bottom = -0.5f;
	float frontdepth = 0.5f;
	float backdepth = -0.5f;

	//front
	std::vector<ST_PC_VERTEX> plane;
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR3(left, top, 0);
	plane.push_back(v);
	v.p = D3DXVECTOR3(right, top, 0);
	plane.push_back(v);
	v.p = D3DXVECTOR3(left, bottom, 0);
	plane.push_back(v);
	v.p = D3DXVECTOR3(left, bottom, 0);
	plane.push_back(v);
	v.p = D3DXVECTOR3(right, top, 0);
	plane.push_back(v);
	v.p = D3DXVECTOR3(right, bottom, 0);
	plane.push_back(v);

	//D3DXMATRIXA16 matTrans;
	D3DXMATRIXA16 matScale, matRotate, matTrans, matFinal;
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(180.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.z = v.p.z + frontdepth;
		v.c = D3DCOLOR_XRGB(255, 0, 0);
		m_vecVertex.push_back(v);
	}

	// right
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(270.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.x = v.p.x + right;
		v.c = D3DCOLOR_XRGB(0, 255, 0);
		m_vecVertex.push_back(v);
	}

	//back
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		//D3DXMatrixRotationY(&matRotate, D3DXToRadian(0.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		//D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.z = v.p.z + backdepth;
		v.c = D3DCOLOR_XRGB(0, 0, 255);
		m_vecVertex.push_back(v);
	}
	//left
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(90.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.x = v.p.x + left;
		v.c = D3DCOLOR_XRGB(255, 255, 0);
		m_vecVertex.push_back(v);
	}

	//top
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationX(&matRotate, D3DXToRadian(90.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.y = v.p.y + top;
		v.c = D3DCOLOR_XRGB(255, 0, 255);
		m_vecVertex.push_back(v);
	}

	// bottom
	// lefttop righttop leftbottom leftbottom righttop rightbottom
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationX(&matRotate, D3DXToRadian(270.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.y = v.p.y + bottom;
		v.c = D3DCOLOR_XRGB(0, 255, 255);
		m_vecVertex.push_back(v);
	}

	for (UINT i = 0; i < m_vecVertex.size(); i++){
		D3DXMatrixScaling(&matScale, m_vSize, m_vSize, m_vSize);
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matScale);
	}
}

void cBox::update(float delta){

}

void cBox::render(){
	if (m_hp > 0){
		D3DXMATRIXA16 matWorld, matT;
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matT);
		g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecVertex.size() / 3,
			&m_vecVertex[0],
			sizeof(ST_PC_VERTEX));

		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	}
}

bool cBox::collidewith(gIObject* obj){
	//@todo
	return true;
}

// return world space coord
D3DXVECTOR3& cBox::getWorldPosition(){
	//@todo
	return m_vPosition;
}
// return grid space position
GRIDPOSITION& cBox::getGridPosition(){
	//@todo
	return m_stGridPosition;
}

// set position using grid system
void cBox::setPositionByGrid(GRIDPOSITION& gridpos){
	m_stGridPosition = gridpos;
	m_vPosition = D3DXVECTOR3(gridpos.x * 5.0f - 50.0f, m_vPosition.y, gridpos.z*5.0f - 50.0f);
}

// set position using worldCoordSystem
void cBox::setPositionByWorldCoord(D3DXVECTOR3& pos){

}

bool cBox::collidewithPoint(D3DXVECTOR3& pos){
	float half = m_vSize / 2.0f;
	if (pos.x > m_vPosition.x - half && pos.x < m_vPosition.x + half
		&& pos.y > m_vPosition.y - half && pos.y < m_vPosition.y + half
		&& pos.z > m_vPosition.z - half && pos.z < m_vPosition.z + half){
		return true;
	}
	else {
		return false;
	}
}

void cBox::getHit(int dmg){ 
	for (UINT i = 0; i < m_vecVertex.size(); i++){
		m_vecVertex[i].c += 100;
	}
	m_hp -= dmg; 
}
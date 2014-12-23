#include "stdafx.h"
#include "cMyCube.h"
#include <math.h>


cMyCube::cMyCube(D3DXVECTOR3 origin, float edgeLength)
{
	m_vec3Origin = origin;
	m_fEdgeLength = edgeLength; 
	m_fAngleDegree = 0.0f;
}


cMyCube::~cMyCube()
{
}

void cMyCube::init(){
	// rectangle hard corded version
	ST_PC_VERTEX v;

	float left = -0.5f;
	float top = 0.5f;
	float right = 0.5f;
	float bottom = -0.5f;

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
	D3DXVECTOR4 new_vec4;

	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		//D3DXMatrixIdentity(&matTrans);
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(0.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3Transform(&new_vec4, &v.p, &matRotate);
		v.c = D3DCOLOR_XRGB(255, 0, 0);
		v.p = D3DXVECTOR3(new_vec4.x, new_vec4.y, new_vec4.z - 0.5f);
		m_vecVertex.push_back(v);
	}

	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(90.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3Transform(&new_vec4, &v.p, &matRotate);
		v.c = D3DCOLOR_XRGB(0, 255, 0);
		v.p = D3DXVECTOR3(new_vec4.x - 0.5f, new_vec4.y, new_vec4.z);
		m_vecVertex.push_back(v);
	}

	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(180.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3Transform(&new_vec4, &v.p, &matRotate);
		v.c = D3DCOLOR_XRGB(0, 0, 255);
		v.p = D3DXVECTOR3(new_vec4.x, new_vec4.y, new_vec4.z + 0.5f);
		m_vecVertex.push_back(v);
	}

	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(270.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3Transform(&new_vec4, &v.p, &matRotate);
		v.c = D3DCOLOR_XRGB(255, 255, 0);
		v.p = D3DXVECTOR3(new_vec4.x + 0.5f, new_vec4.y, new_vec4.z);
		m_vecVertex.push_back(v);
	}

	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationX(&matRotate, D3DXToRadian(90.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3Transform(&new_vec4, &v.p, &matRotate);
		v.c = D3DCOLOR_XRGB(0, 255, 255);
		v.p = D3DXVECTOR3(new_vec4.x, new_vec4.y + 0.5f, new_vec4.z);
		m_vecVertex.push_back(v);
	}

	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationX(&matRotate, D3DXToRadian(270.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3Transform(&new_vec4, &v.p, &matRotate);
		v.c = D3DCOLOR_XRGB(255, 0, 255);
		v.p = D3DXVECTOR3(new_vec4.x, new_vec4.y - 0.5f, new_vec4.z);
		m_vecVertex.push_back(v);
	}

	ZeroMemory(&matFinal, sizeof(D3DXMATRIXA16));
	ZeroMemory(&matScale, sizeof(D3DXMATRIXA16));
	ZeroMemory(&matTrans, sizeof(D3DXMATRIXA16));

	for (UINT j = 0; j < m_vecVertex.size(); j++){
		v = m_vecVertex[j];
		D3DXMatrixScaling(&matScale, m_fEdgeLength, m_fEdgeLength, m_fEdgeLength);
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//D3DXMatrixRotationX(&matRotate, D3DXToRadian(270.0f));
		//
		matFinal = matScale;
		D3DXVec3Transform(&new_vec4, &v.p, &matFinal);
		v.p = D3DXVECTOR3(new_vec4.x, new_vec4.y, new_vec4.z);
		m_vecVertex[j] = v;
	}
}

void cMyCube::update(float delta){
	if (GetKeyState('A') & 0x8000){
		m_fAngleDegree -= 90.0f * delta;
		//m_vec3Origin.x = m_vec3Origin.x - 10.0f*delta;
	}
	if (GetKeyState('D') & 0x8000){
		m_fAngleDegree += 90.0f * delta;
		//m_vec3Origin.x = m_vec3Origin.x + 10.0f*delta;
	}
	if (GetKeyState('W') & 0x8000){
		//m_fAngleDegree += 10.0f * delta;
		m_vec3Origin.y;
		m_vec3Origin.x = m_vec3Origin.x + 10.0f * delta * sinf(D3DXToRadian(m_fAngleDegree));
		m_vec3Origin.z = m_vec3Origin.z + 10.0f * delta * cosf(D3DXToRadian(m_fAngleDegree));
	}
	if (GetKeyState('S') & 0x8000){
		//m_fAngleDegree += 10.0f * delta;
		m_vec3Origin.y;
		m_vec3Origin.x = m_vec3Origin.x - 10.0f * delta * sinf(D3DXToRadian(m_fAngleDegree));
		m_vec3Origin.z = m_vec3Origin.z - 10.0f * delta * cosf(D3DXToRadian(m_fAngleDegree));
	}
}

void cMyCube::render(){
	//float fAngle = 0;
	//fAngle += 0.1f;
	D3DXMATRIXA16 matWorld, matR, matT;
	D3DXMatrixRotationY(&matR, D3DXToRadian(m_fAngleDegree));
	D3DXMatrixTranslation(&matT, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);

	matWorld = matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

}
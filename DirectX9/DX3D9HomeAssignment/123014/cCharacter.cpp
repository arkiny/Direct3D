#include "stdafx.h"
#include "cCharacter.h"
#include "cCube.h"

cCharacter::cCharacter() :
m_vForward(0, 0, 1.0f),
m_vPosition(0.0f, 0.0f, 0.0f),
m_fSpeed(10.0f),
m_matWorldT()
{
	D3DXMatrixIdentity(&m_matWorldT);
}


cCharacter::~cCharacter()
{
	for (auto a : m_vecCube){
		SAFE_DELETE(a);
	}
}

void cCharacter::init(){

	LPDIRECT3DTEXTURE9 m_pTexture;

	D3DXCreateTextureFromFile(
		g_pD3DDevice,
		L"../Resource/Iron_Man_Skin_2.png",
		&m_pTexture);

	cCube* p;

	p = new cCube;
	p->init(2.0f, 2.0f, 2.0f, cCube::Cube_Part::PT_head);
	p->setPosition(D3DXVECTOR3(0, m_vPosition.y + 2.5f, 0));
	p->SetTexture(m_pTexture);
	m_vecCube.push_back(p);

	p = new cCube;
	p->init(2.0f, 3.0f, 1.0f, cCube::Cube_Part::PT_body);
	p->SetTexture(m_pTexture);
	m_vecCube.push_back(p);

	p = new cCube;
	p->init(1.0f, 3.0f, 1.0f, cCube::Cube_Part::PT_arm_left); // actually right
	p->setPosition(D3DXVECTOR3(m_vPosition.x+1.5f, 0, 0));
	p->SetTexture(m_pTexture);
	m_vecCube.push_back(p);

	p = new cCube;
	p->init(1.0f, 3.0f, 1.0f, cCube::Cube_Part::PT_arm_right); // actually right
	p->setPosition(D3DXVECTOR3(m_vPosition.x- 1.5f, 0, 0));
	p->SetTexture(m_pTexture);
	m_vecCube.push_back(p);

	p = new cCube;
	p->init(1.0f, 3.0f, 1.0f, cCube::Cube_Part::PT_leg_left); // actually right
	p->setPosition(D3DXVECTOR3(m_vPosition.x + 0.5f, m_vPosition.y - 3.0f, 0));
	p->SetTexture(m_pTexture);
	m_vecCube.push_back(p);

	p = new cCube;
	p->init(1.0f, 3.0f, 1.0f, cCube::Cube_Part::PT_leg_right); // actually right
	p->setPosition(D3DXVECTOR3(m_vPosition.x - 0.5f, m_vPosition.y - 3.0f, 0));
	p->SetTexture(m_pTexture);
	m_vecCube.push_back(p);

	SAFE_RELEASE(m_pTexture);

	for (auto parts : m_vecCube){
		parts->setWorldMatrix(&m_matWorldT);
	}
}

void cCharacter::update(float delta){
	D3DXMATRIXA16 matRot, matTrans;
	D3DXMatrixIdentity(&matTrans);

	if (GetKeyState('A') & 0x8000){
		m_fAngleDegree -= 90.0f * delta;
	}
	if (GetKeyState('D') & 0x8000){
		m_fAngleDegree += 90.0f * delta;
	}
	if (GetKeyState('W') & 0x8000){
		m_vPosition += m_vForward*m_fSpeed*delta;
	}
	if (GetKeyState('S') & 0x8000){
		m_vPosition -= m_vForward*m_fSpeed*delta;
	}	

	D3DXMatrixRotationY(&matRot, D3DXToRadian(m_fAngleDegree));
	m_vForward = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vForward, &m_vForward, &matRot);
	D3DXMatrixTranslation(&matTrans, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorldT = matRot * matTrans;

	for (auto a : m_vecCube){
		a->update(delta);
	}
}

void cCharacter::render(){
	for (auto a : m_vecCube){
		a->render();
	}
}
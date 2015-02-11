#include "stdafx.h"
#include "cParticlesFire.h"


cParticlesFire::cParticlesFire()
{
}


cParticlesFire::~cParticlesFire()
{
}

void cParticlesFire::Setup(){
	for (int i = 0; i < 100; ++i)
	{
		ST_PC_VERTEX v;
		v.c = D3DCOLOR_XRGB(128, 80, 13);
		/*ST_PARTICLE stP;
		stP._vertex.c = D3DCOLOR_XRGB(30, 80, 128);*/
		//v.p = D3DXVECTOR3(0, 0, 100 - 10 * i);
		//v.p = D3DXVECTOR3(0, 0, 10 * i);

		D3DXVECTOR3 vDirection(0, 1, 0);
		D3DXMATRIXA16 rot, rotX, rotY, rotZ;
		D3DXMatrixRotationX(&rotX, D3DXToRadian(rand() % 361));
		D3DXMatrixRotationY(&rotY, D3DXToRadian(rand() % 361));
		D3DXMatrixRotationZ(&rotZ, D3DXToRadian(rand() % 361));
		rot = rotX*rotY*rotZ;
		D3DXMATRIXA16 localMat;
		localMat = rot;
		D3DXVECTOR3 localPos;
		D3DXVec3TransformCoord(&localPos, &vDirection, &localMat);
		localPos = localPos * ((rand() % 200) / 2000.0f);
		v.p = localPos;

		ST_PARTICLE stP;
		stP._vInitialPos = v.p;
		stP._lifeSpan = (rand() % 400) / 200.0f;
		stP._currentTime = 0.0f;
		stP._speed = (rand() % 200) / 200.0f;

		/*D3DXMatrixRotationX(&rotX, D3DXToRadian(rand() % 361));
		D3DXMatrixRotationY(&rotY, D3DXToRadian(rand() % 361));
		D3DXMatrixRotationZ(&rotZ, D3DXToRadian(rand() % 361));*/

		D3DXMatrixRotationX(&rotX, D3DXToRadian(0));
		D3DXMatrixRotationY(&rotY, D3DXToRadian(0));
		D3DXMatrixRotationZ(&rotZ, D3DXToRadian(0));

		rot = rotX*rotY*rotZ;
		localMat = rot;
		D3DXVECTOR3 vDir;
		D3DXVec3TransformNormal(&vDir, &vDirection, &localMat);
		stP._direction = vDir;

		m_vecVertex.push_back(v);
		m_vecMoveInfo.push_back(stP);
	}
}

void cParticlesFire::Update(float fDelta){
	for (size_t i = 0; i < m_vecVertex.size(); i++){
		m_vecVertex[i].p = m_vecVertex[i].p + (m_vecMoveInfo[i]._direction * m_vecMoveInfo[i]._speed * fDelta);

		float alpha = 1.0f - (m_vecMoveInfo[i]._currentTime / m_vecMoveInfo[i]._lifeSpan);

		if (alpha < 0.0f){
			alpha = 0.0f;
		}
		m_vecVertex[i].c = D3DXCOLOR(128 / 255.0f, 80 / 255.0f, 13 / 255.0f, alpha);
		m_vecMoveInfo[i]._currentTime += fDelta;

		if (m_vecMoveInfo[i]._currentTime > m_vecMoveInfo[i]._lifeSpan){
			m_vecMoveInfo[i]._currentTime = 0.0f;
			m_vecVertex[i].p = m_vecMoveInfo[i]._vInitialPos;

			m_vecMoveInfo[i]._lifeSpan = (rand() % 400) / 200.0f;
			m_vecMoveInfo[i]._currentTime = 0.0f;
			m_vecMoveInfo[i]._speed = (rand() % 200) / 200.0f;
			D3DXMATRIXA16 rot, rotX, rotY, rotZ;
			D3DXMatrixRotationX(&rotX, D3DXToRadian(0));
			D3DXMatrixRotationY(&rotY, D3DXToRadian(0));
			D3DXMatrixRotationZ(&rotZ, D3DXToRadian(0));

			rot = rotX*rotY*rotZ;

			D3DXVECTOR3 vDirection(0, 1, 0);
			D3DXMATRIXA16 localMat;
			localMat = rot;
			D3DXVECTOR3 vDir;
			D3DXVec3TransformNormal(&vDir, &vDirection, &localMat);
			m_vecMoveInfo[i]._direction = vDir;

		}
	}
}
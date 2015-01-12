#include "stdafx.h"
#include <math.h>
#include "cTeapot.h"
#include "cMtlTex.h"
#include "cVertexPoints.h"

#define SPEED 2

D3DXVECTOR3& linearInterpolition(D3DXVECTOR3& prev, D3DXVECTOR3& next, float delta){
	return	prev + (next - prev) * delta;
}

D3DXVECTOR3& bezierInterpolition(D3DXVECTOR3& first, D3DXVECTOR3& second, D3DXVECTOR3& third, float delta){
	D3DXVECTOR3 prev = first + (second - first) * delta;
	D3DXVECTOR3 next = second + (third - second) * delta;
	return linearInterpolition(prev, next, delta);
}

cTeapot::cTeapot() :
m_pMesh(NULL),
m_pMtlTex(NULL),
m_vecPos(0, 0, 0),
m_vecTarget(0, 0, 0),
m_vecTarget2(0, 0, 0),
m_vecFront(0, 0, 0),
m_vecFront2(0,0,0),
m_vecPos3(0,0,0)//,
//m_vecStart(0,0,0)
{
}


cTeapot::~cTeapot()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMtlTex);
}

void cTeapot::setup(cVertexPoints* points, eINTERPOLATIONTYPE type){
	fPrevTime = GetTickCount() * 0.001f;
	m_pTargets = points;
	D3DXCreateTeapot(g_pD3DDevice, &m_pMesh, NULL);
	m_pMtlTex = new cMtlTex;
	m_pMtlTex->pTex = NULL;
	m_pMtlTex->stMtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMtlTex->stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMtlTex->stMtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMtlTex->stMtl.Emissive = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMtlTex->stMtl.Power = 5.0f;
	m_eType = type;

	if (m_eType == eINTERPOLATIONTYPE::eLinear){
		m_vecPos = m_pTargets->getPointAt(0);
		m_vecStart = m_pTargets->getPointAt(0);
		m_vecTarget = m_pTargets->getPointAt(1);
		m_nTargetIndex = 1;
		float fl1 = m_vecTarget.x - m_vecPos.x;
		float fl2 = sqrtf((m_vecTarget.x - m_vecPos.x) * (m_vecTarget.x - m_vecPos.x) + (m_vecPos.z - m_vecTarget.z) * (m_vecPos.z - m_vecTarget.z));
		float angle = acosf(fl1 / fl2);

		if (m_nTargetIndex > 3 || m_nTargetIndex == 0){
			m_fAngle = -angle;
		}
		else {
			m_fAngle = angle;
		}
	}
	else {
		m_vecPos	= m_pTargets->getPointAt(0);
		m_vecStart = m_vecPos;
		m_vecTarget = m_pTargets->getPointAt(1);
		m_vecTarget2 = m_pTargets->getPointAt(2);
		m_nTargetIndex = 2;
	}
}

void cTeapot::setPos(D3DXVECTOR3& vec){
	m_vecPos = vec;
}

void cTeapot::update(float delta){	
	if (m_eType == eINTERPOLATIONTYPE::eLinear){
		float currTime = GetTickCount() * 0.001f;
		float tick = currTime - fPrevTime;
		fPrevTime = currTime;
		fAccum += tick * SPEED;
		if (fAccum >= 1.0f){
			linearInterpolition(m_vecPos, m_vecTarget, fAccum);
			m_vecPos = m_vecTarget;
			m_vecStart = m_vecTarget;
			m_nTargetIndex++;
			if (m_nTargetIndex > 5){
				m_nTargetIndex = 0;
				m_vecTarget = m_pTargets->getPointAt(m_nTargetIndex);
			}
			else {
				m_vecTarget = m_pTargets->getPointAt(m_nTargetIndex);
			}

			float fl1 = m_vecTarget.x - m_vecPos.x;
			float fl2 = sqrtf((m_vecTarget.x - m_vecPos.x) * (m_vecTarget.x - m_vecPos.x) + (m_vecPos.z - m_vecTarget.z) * (m_vecPos.z - m_vecTarget.z));
			float angle = acosf(fl1 / fl2);

			if (m_nTargetIndex > 3 || m_nTargetIndex == 0){
				m_fAngle = -angle;
			}
			else {
				m_fAngle = angle;
			}

			fAccum = 0.0f;
		}
		else {
			m_vecPos = linearInterpolition(m_vecStart, m_vecTarget, fAccum);
		}	

	}
	else if (m_eType = eINTERPOLATIONTYPE::eBezier){
		float currTime = GetTickCount() * 0.001f;
		float tick = currTime - fPrevTime;
		fPrevTime = currTime;
		fAccum += (tick*SPEED/2.0f);

		if (fAccum >= 1.0f){
			bezierInterpolition(m_vecPos, m_vecTarget, m_vecTarget2, fAccum);
			
			m_vecPos = m_vecTarget;
			m_vecStart = m_vecTarget;

			if (m_nTargetIndex == 2){
				m_vecPos = m_pTargets->getPointAt(2);
				m_vecStart = m_vecPos;

				m_vecTarget = m_pTargets->getPointAt(3);
				m_vecTarget2 = m_pTargets->getPointAt(4);
				m_nTargetIndex = 4;
				
			}
			else if (m_nTargetIndex == 4){
				m_vecPos = m_pTargets->getPointAt(4);
				m_vecStart = m_vecPos;

				m_vecTarget = m_pTargets->getPointAt(5);
				m_vecTarget2 = m_pTargets->getPointAt(0);
				m_nTargetIndex = 0;
				
			}
			else if (m_nTargetIndex == 0){
				m_vecPos = m_pTargets->getPointAt(0);
				m_vecStart = m_vecPos;

				m_vecTarget = m_pTargets->getPointAt(1);
				m_vecTarget2 = m_pTargets->getPointAt(2);
				m_nTargetIndex = 2;				
			}
			fAccum = 0.0f;
		}
		else {
			m_vecPos = bezierInterpolition(m_vecStart, m_vecTarget, m_vecTarget2, fAccum);
			
			float fl1 = m_vecTarget2.x - m_vecPos.x;
			float fl2 = 
				sqrtf((m_vecTarget2.x - m_vecPos.x) * (m_vecTarget2.x - m_vecPos.x) 
				+ (m_vecPos.z - m_vecTarget2.z) * (m_vecPos.z - m_vecTarget2.z));
			
			float angle = acosf(fl1 / fl2);

			if (m_nTargetIndex > 3 || m_nTargetIndex == 0){
				m_fAngle = -angle;
			}
			else {
				m_fAngle = angle;
			}

		}
	}
}



void cTeapot::render(){
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	D3DXMATRIXA16 matT, matR, matF;
	D3DXMatrixRotationY(&matR, m_fAngle);
	if (m_eType == eINTERPOLATIONTYPE::eBezier){
		D3DXMatrixTranslation(&matT, m_vecPos.x, m_vecPos.y, m_vecPos.z);
	}
	else{
		D3DXMatrixTranslation(&matT, m_vecPos.x, m_vecPos.y, m_vecPos.z);
	}
	
	matF = matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matF);
	g_pD3DDevice->SetMaterial(&m_pMtlTex->stMtl);
	g_pD3DDevice->SetTexture(0, NULL);
	m_pMesh->DrawSubset(0);
}
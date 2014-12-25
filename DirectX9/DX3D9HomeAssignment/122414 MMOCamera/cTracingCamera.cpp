#include "stdafx.h"
#include <math.h>
#include "cTracingCamera.h"


cTracingCamera::cTracingCamera() :
m_vEye(0, 30, -40), m_vLookAt(0, 0, 0), m_vUp(0, 1, 0), m_fAngleDegree(0.0f)
{
	m_vlength = m_vEye - m_vLookAt; // actually direction
	
	float radAngle = asinf(m_vlength.y / D3DXVec3Length(&m_vlength));
	m_fAngleDegree = -D3DXToDegree(radAngle);
}


cTracingCamera::~cTracingCamera()
{
}

void cTracingCamera::init(){
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cTracingCamera::moveforward(float unit){
	D3DXMATRIXA16 matR;
	
	D3DXVec3Normalize(&m_vecForward, &m_vlength);

	if (unit < 0){
		if (D3DXVec3Length(&m_vlength) > 8.0f){
			m_vEye += m_vecForward*unit;
			D3DXMATRIXA16 matView;
			D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
			g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
			m_vlength = m_vEye - m_vLookAt;
		}
	}
	else {
		if (D3DXVec3Length(&m_vlength) < 60.0f){
			m_vEye += m_vecForward*unit;
			D3DXMATRIXA16 matView;
			D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
			g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
			m_vlength = m_vEye - m_vLookAt;
		}
	}
}

void cTracingCamera::rotateX(float degree){
	D3DXMATRIXA16 matT, matR;
	D3DXVECTOR3 lookAtcalc;
	
	// translate to origin (local space)
	D3DXMatrixTranslation(&matT, -m_vLookAt.x, -m_vLookAt.y, -m_vLookAt.z);
	D3DXVec3TransformCoord(&lookAtcalc, &m_vEye, &matT);

	// Rotate
	D3DXMatrixRotationY(&matR, D3DXToRadian(degree));
	D3DXVec3TransformCoord(&lookAtcalc, &lookAtcalc, &matR);

	// translate to world space
	D3DXMatrixTranslation(&matT, m_vLookAt.x, m_vLookAt.y, m_vLookAt.z);
	D3DXVec3TransformCoord(&m_vEye, &lookAtcalc, &matT);

	m_vlength = m_vEye - m_vLookAt;
	
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cTracingCamera::rotateY(float degree){
	if (degree > 0){
		if (m_fAngleDegree < 80.0f){
			
			m_fAngleDegree += degree;
			
			D3DXMATRIXA16 matT, matR;
			D3DXVECTOR3 lookAtcalc;
			// translate to origin (local space)
			D3DXMatrixTranslation(&matT, -m_vLookAt.x, -m_vLookAt.y, -m_vLookAt.z);
			D3DXVec3TransformCoord(&lookAtcalc, &m_vEye, &matT);

			// Get Axis from current known variable (looking direction, upside)
			D3DXVECTOR3 axis, normalUp, normalDir;
			D3DXVec3Normalize(&normalUp, &m_vUp);
			D3DXVec3Normalize(&normalDir, &m_vlength);
			D3DXVec3Cross(&axis, &normalUp, &normalDir);

			// Rotate around the Axis
			D3DXMatrixRotationAxis(&matR, &axis, D3DXToRadian(degree));
			D3DXVec3TransformCoord(&lookAtcalc, &lookAtcalc, &matR);

			// translate to world space
			D3DXMatrixTranslation(&matT, m_vLookAt.x, m_vLookAt.y, m_vLookAt.z);
			D3DXVec3TransformCoord(&m_vEye, &lookAtcalc, &matT);

			// update direction
			m_vlength = m_vEye - m_vLookAt;

			D3DXMATRIXA16 matView;
			D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
			g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
		}
	}
	else if (degree < 0){
		if (m_fAngleDegree > -80.0f){
			
			m_fAngleDegree += degree;

			D3DXMATRIXA16 matT, matR;
			D3DXVECTOR3 lookAtcalc;
			// translate to origin (local space)
			D3DXMatrixTranslation(&matT, -m_vLookAt.x, -m_vLookAt.y, -m_vLookAt.z);
			D3DXVec3TransformCoord(&lookAtcalc, &m_vEye, &matT);

			// Get Axis from current known variable (looking direction, upside)
			D3DXVECTOR3 axis, normalUp, normalDir;
			D3DXVec3Normalize(&normalUp, &m_vUp);
			D3DXVec3Normalize(&normalDir, &m_vlength);
			D3DXVec3Cross(&axis, &normalUp, &normalDir);

			// Rotate around the Axis
			D3DXMatrixRotationAxis(&matR, &axis, D3DXToRadian(degree));
			D3DXVec3TransformCoord(&lookAtcalc, &lookAtcalc, &matR);

			// translate to world space
			D3DXMatrixTranslation(&matT, m_vLookAt.x, m_vLookAt.y, m_vLookAt.z);
			D3DXVec3TransformCoord(&m_vEye, &lookAtcalc, &matT);

			// update direction
			m_vlength = m_vEye - m_vLookAt;

			D3DXMATRIXA16 matView;
			D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
			g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
		}
	}	
}

void cTracingCamera::updatePosition(D3DXVECTOR3& objPos){
	m_vLookAt = D3DXVECTOR3(objPos.x, objPos.y+2.0f, objPos.z);

	m_vEye = m_vLookAt + m_vlength;

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}
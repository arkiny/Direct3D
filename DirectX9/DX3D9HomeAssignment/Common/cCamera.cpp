#include "stdafx.h"
#include "cCamera.h"

cCamera::cCamera() :
vEye(0, 3, -10),
vLookAt(0, 0, 0),
vUp(0, 100, 0)
{
	m_fViewRangeX = -10.0f;
	m_fViewRangeZ = 2.0f;
}


cCamera::~cCamera()
{
}

void cCamera::init(){
	g_pD3DDevice->GetViewport(&vp);
	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, vp.Width / (float)vp.Height, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::update(float delta){
	bool change = false;
	D3DXMATRIXA16 matRotate, matTrans, matFinal;
	D3DXVECTOR4 new_vec4;

	if (GetKeyState('A') & 0x8000){
		m_fAngleDegree -= 90.0f * delta;
		vEye.x = vLookAt.x + m_fViewRangeX * sinf(D3DXToRadian(m_fAngleDegree));
		vEye.y = vEye.y;
		vEye.z = vLookAt.z + m_fViewRangeX * cosf(D3DXToRadian(m_fAngleDegree));
		change = true;
	}
	if (GetKeyState('D') & 0x8000){
		m_fAngleDegree += 90.0f * delta;
		vEye.x = vLookAt.x + m_fViewRangeX * sinf(D3DXToRadian(m_fAngleDegree));
		vEye.y = vEye.y;
		vEye.z = vLookAt.z + m_fViewRangeX * cosf(D3DXToRadian(m_fAngleDegree));
		change = true;
	}

	if (GetKeyState('W') & 0x8000){
	//	m_fAngleDegree += 10.0f * delta;
		vEye.y;
		vEye.x = vEye.x + 10.0f * delta * sinf(D3DXToRadian(m_fAngleDegree));
		vEye.z = vEye.z + 10.0f * delta * cosf(D3DXToRadian(m_fAngleDegree));
		vLookAt.y;
		vLookAt.x = vLookAt.x + 10.0f * delta * sinf(D3DXToRadian(m_fAngleDegree));
		vLookAt.z = vLookAt.z + 10.0f * delta * cosf(D3DXToRadian(m_fAngleDegree));
		change = true;
	}

	if (g_pControl->getMouseScrollInfo(g_pControl->up)){
		vEye.y;
		vEye.x = vEye.x + 10.0f * delta * sinf(D3DXToRadian(m_fAngleDegree));
		vEye.z = vEye.z + 10.0f * delta * cosf(D3DXToRadian(m_fAngleDegree));
		vLookAt.y;
		vLookAt.x = vLookAt.x + 10.0f * delta * sinf(D3DXToRadian(m_fAngleDegree));
		vLookAt.z = vLookAt.z + 10.0f * delta * cosf(D3DXToRadian(m_fAngleDegree));
		change = true;
	}

	if (GetKeyState('S') & 0x8000){
		//m_fAngleDegree += 10.0f * delta;
		vEye.y;
		vEye.x = vEye.x - 10.0f * delta * sinf(D3DXToRadian(m_fAngleDegree));
		vEye.z = vEye.z - 10.0f * delta * cosf(D3DXToRadian(m_fAngleDegree));
		vLookAt.y;
		vLookAt.x = vLookAt.x - 10.0f * delta * sinf(D3DXToRadian(m_fAngleDegree));
		vLookAt.z = vLookAt.z - 10.0f * delta * cosf(D3DXToRadian(m_fAngleDegree));
		change = true;
	}


	if (change){
		//D3DXMATRIXA16 matViewU, matR, matT;
		/*D3DXMatrixRotationY(&matR, D3DXToRadian(m_fAngleDegree));
		D3DXMatrixTranslation(&matT, vEye.x, vEye.y, vEye.z);*/
		//matViewU = matR * matT;

		D3DXMatrixLookAtLH(&matFinal, &vEye, &vLookAt, &vUp);
		g_pD3DDevice->SetTransform(D3DTS_VIEW, &matFinal);
		change = false;
	}
}

void cCamera::movefoward(float speed){
	D3DXMATRIXA16 matRotate, matTrans, matFinal;
	D3DXVECTOR4 new_vec4;
	vEye.y;
	vEye.x = vEye.x + speed * sinf(D3DXToRadian(m_fAngleDegree));
	vEye.z = vEye.z + speed * cosf(D3DXToRadian(m_fAngleDegree));
	vLookAt.y;
	vLookAt.x = vLookAt.x + speed * sinf(D3DXToRadian(m_fAngleDegree));
	vLookAt.z = vLookAt.z + speed * cosf(D3DXToRadian(m_fAngleDegree));
	D3DXMatrixLookAtLH(&matFinal, &vEye, &vLookAt, &vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matFinal);
}
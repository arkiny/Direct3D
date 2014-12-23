#include "stdafx.h"
#include "cCamera.h"

cCamera::cCamera() :
vEye(0, 0, -10),
vLookAt(0, 0, 0),
vUp(0, 100, 0)
{
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
	if (g_pControl->getKeyControlInfo(VK_LEFT)){
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(90.0f*delta));
		D3DXMatrixTranslation(&matTrans, 0.0, 0.0, 0.0);
		//vEye.x += 10*delta;
		matFinal = matRotate*matTrans;
		D3DXVec3Transform(&new_vec4, &vEye, &matFinal);
		vEye.x = new_vec4.x;
		vEye.y = new_vec4.y; 
		vEye.z = new_vec4.z;
		change = true;
	}
	if (g_pControl->getKeyControlInfo(VK_RIGHT)){
		//vEye.x -= 10 * delta;
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(-90.0f*delta));
		D3DXMatrixTranslation(&matTrans, 0.0, 0.0, 0.0);
		matFinal = matRotate*matTrans;
		D3DXVec3Transform(&new_vec4, &vEye, &matFinal);
		vEye.x = new_vec4.x;
		vEye.y = new_vec4.y;
		vEye.z = new_vec4.z;
		change = true;
	}
	if (g_pControl->getKeyControlInfo(VK_UP)){
		//vEye.y += 10 * delta;
		D3DXMatrixRotationX(&matRotate, D3DXToRadian(90.0f*delta));
		D3DXMatrixTranslation(&matTrans, 0.0, 0.0, 0.0);
		matFinal = matRotate*matTrans;
		D3DXVec3Transform(&new_vec4, &vEye, &matFinal);
		vEye.x = new_vec4.x;
		vEye.y = new_vec4.y;
		vEye.z = new_vec4.z;
		change = true;
	}
	if (g_pControl->getKeyControlInfo(VK_DOWN)){
		//vEye.y -= 10 * delta;
		D3DXMatrixRotationX(&matRotate, D3DXToRadian(-90.0f*delta));
		D3DXMatrixTranslation(&matTrans, 0.0, 0.0, 0.0);
		matFinal = matRotate*matTrans;
		D3DXVec3Transform(&new_vec4, &vEye, &matFinal);
		vEye.x = new_vec4.x;
		vEye.y = new_vec4.y;
		vEye.z = new_vec4.z;
		change = true;
	}
	if (g_pControl->getKeyControlInfo(0x57)){
		//vEye.z += 10 * delta;
		D3DXMatrixRotationX(&matRotate, D3DXToRadian(0.0f));
		D3DXMatrixTranslation(&matTrans, 0.0, 0.0, 10.0*delta);
		matFinal = matRotate*matTrans;
		D3DXVec3Transform(&new_vec4, &vEye, &matFinal);
		vEye.x = new_vec4.x;
		vEye.y = new_vec4.y;
		vEye.z = new_vec4.z;
		change = true;
	}
	if (g_pControl->getKeyControlInfo(0x53)){
		//vEye.z -= 10 * delta;
		D3DXMatrixRotationX(&matRotate, D3DXToRadian(0.0f));
		D3DXMatrixTranslation(&matTrans, 0.0, 0.0, -10.0*delta);
		matFinal = matRotate*matTrans;
		D3DXVec3Transform(&new_vec4, &vEye, &matFinal);
		vEye.x = new_vec4.x;
		vEye.y = new_vec4.y;
		vEye.z = new_vec4.z;
		change = true;
	}
	if (change){
		init();
		change = false;
	}
}
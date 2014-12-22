#include "stdafx.h"
#include "cCamera.h"

cCamera::cCamera() :
vEye(-10, 10, -10),
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
	if (g_pControl->getKeyControlInfo(VK_LEFT)){
		vEye.x += 10*delta;
		change = true;
	}
	if (g_pControl->getKeyControlInfo(VK_RIGHT)){
		vEye.x -= 10 * delta;
		change = true;
	}
	if (g_pControl->getKeyControlInfo(VK_UP)){
		vEye.y += 10 * delta;
		change = true;
	}
	if (g_pControl->getKeyControlInfo(VK_DOWN)){
		vEye.y -= 10 * delta;
		change = true;
	}
	if (g_pControl->getKeyControlInfo(0x57)){
		vEye.z += 10 * delta;
		change = true;
	}
	if (g_pControl->getKeyControlInfo(0x53)){
		vEye.z -= 10 * delta;
		change = true;
	}
	if (change){
		init();
		change = false;
	}
}
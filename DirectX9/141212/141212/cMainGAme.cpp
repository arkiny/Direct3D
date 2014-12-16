#include "stdafx.h"
#include "cMainGAme.h"


cMainGAme::cMainGAme()
{
	m_pD3D = NULL;
	g_pD3DDevice = NULL;
}


cMainGAme::~cMainGAme()
{
	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(g_pD3DDevice);
}


void cMainGAme::init(){
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DCAPS9 stCaps;
	int nVertexProcess;

	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);
	if (stCaps.DevCaps && D3DDEVCAPS_HWTRANSFORMANDLIGHT){
		nVertexProcess = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else{
		nVertexProcess = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;

	m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		nVertexProcess,
		&stD3DPP,
		&g_pD3DDevice);

}
void cMainGAme::update(){

}
void cMainGAme::render(){
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255),1.0f, 0);
	g_pD3DDevice->BeginScene();
	///

	///
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
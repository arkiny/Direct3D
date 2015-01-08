#include "StdAfx.h"
#include "cDeviceManager.h"


cDeviceManager::cDeviceManager(void)
	: m_pD3D(NULL)
	, m_pD3DDevice(NULL)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9	stCaps;
	int			nVertexProcessing;
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);
	if(stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed				= TRUE;
	stD3DPP.BackBufferFormat		= D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil	= TRUE;
	stD3DPP.AutoDepthStencilFormat	= D3DFMT_D24S8;


	m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		nVertexProcessing,
		&stD3DPP,
		&m_pD3DDevice);
}


cDeviceManager::~cDeviceManager(void)
{
}

void cDeviceManager::Destroy()
{
	SAFE_RELEASE(m_pD3D);
	//SAFE_RELEASE(m_pD3DDevice);
	ULONG ul = m_pD3DDevice->Release();
	assert(ul == 0 && "디바이스를 통해 생성된 객체 중 해제되지 않은 객체가 있습니다.");
}

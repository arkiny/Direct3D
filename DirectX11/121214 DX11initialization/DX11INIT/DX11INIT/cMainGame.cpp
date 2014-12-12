#include "stdafx.h"
#include "cMainGame.h"

//#include <assert.h>
#define HR hr=

cMainGame::cMainGame()
{
	md3dDevice = NULL;
	md3dImmediateContext = NULL;
}


cMainGame::~cMainGame()
{
	if (md3dDevice){
		md3dDevice->Release();
		md3dDevice = NULL;
	}
	if (md3dImmediateContext){
		md3dImmediateContext->Release();
		md3dImmediateContext = NULL;
	}
}


void cMainGame::setup(){
	UINT createDeviceFlags = 0;
	D3D_FEATURE_LEVEL featureLevel;
	
	//HRESULT D3D11CreateDevice(
	//	IDXGIAdapter *pAdapter,
	//	D3D_DRIVER_TYPE DriverType,
	//	HMODULE Software,
	//	UINT Flags,
	//	CONST D3D_FEATURE_LEVEL *pFeatureLevels,
	//	UINT FeatureLevels,
	//	UINT SDKVersion,
	//	ID3D11Device **ppDevice,
	//	D3D_FEATURE_LEVEL *pFeatureLevel,
	//	ID3D11DeviceContext **ppImmediateContext
	//	);
	HRESULT hr = D3D11CreateDevice(
		NULL,  // default adapter (main monitor)
		D3D_DRIVER_TYPE_HARDWARE, // using hardware rendering
		0, // no software device
		createDeviceFlags, // will create device flag debuglevel layer maybe
		0, 0, // default feature level array, test feature level
		D3D11_SDK_VERSION, // current sdk version
		&md3dDevice, // returns created device
		&featureLevel, // returns first supported feature level in featurelevel array
		&md3dImmediateContext // returns the created device context
		);

	UINT m4xMsaaQuality;
	hr = md3dDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
	//(m4xMsaaQuality > 0);

	DXGI_SWAP_CHAIN_DESC sd;
	bool mEnable4xMsaa = true;
	sd.BufferDesc.Width = 1024; // use window's client area dims
	sd.BufferDesc.Height = 768;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	if (mEnable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		// m4xMsaaQuality is returned via CheckMultisampleQualityLevels().
		sd.SampleDesc.Quality = m4xMsaaQuality - 1;
	} // No MSAA
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = g_hWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	IDXGIDevice* dxgiDevice = 0;
	HR(md3dDevice->QueryInterface(__uuidof(IDXGIDevice),
		(void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = 0;
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)dxgiAdapter);


	HR();
		// Finally got the IDXGIFactory interface.
	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory),
		(void**))dxgiFactory));
	// Now, create the swap chain.
	IDXGISwapChain* mSwapChain;
	HR(dxgiFactory->CreateSwapChain(md3dDevice, )&sd, )&mSwapChain));
	// Release our acquired COM interfaces (because we are done with them).
	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);
}
void cMainGame::update(){

}
void cMainGame::render(){
	
}
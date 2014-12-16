#include "stdafx.h"
#include "cDeviceManager.h"

cDeviceManager::cDeviceManager() :
m_pD3D11Device(NULL),
m_pD3D11DIC(NULL),
m_pSwapChain(NULL),
m_pDepthStencilBuffer(NULL),
m_pDepthStencilView(NULL),
m_RenderTargetView(NULL)
{
	ZeroMemory(&m_stScreenViewPort, sizeof(D3D11_VIEWPORT));

	UINT createDeviceFlags = 0;
#if defined(_DEBUG) || defined(DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(
		0,							// default adapter
		D3D_DRIVER_TYPE_HARDWARE,	// driver type
		//D3D_DRIVER_TYPE_REFERENCE : reference device(only for develop)
		//D3D_DRIVER_TYPE_SOFTWARE : emulate 3D hardware with software
		//D3D_DRIVER_TYPE_WARP : using D10 platform : does not support D11
		0,							// no software device,
		createDeviceFlags,			// for debug messages
		0, 0,						// Array of feature levels(versions?)
		D3D11_SDK_VERSION,			// literally sdk version
		&m_pD3D11Device,
		&featureLevel,
		&m_pD3D11DIC
		);

	// immdiate context is main rendering thread
	// Have any additional deferred contexts on separate worker threads.
	// p115

	if (FAILED(hr)){
		MessageBox(0, L"D3D11CreateDevice Failed", 0, 0);
		assert(SUCCEEDED(hr));
	}
	if (featureLevel != D3D_FEATURE_LEVEL_11_0){
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		assert(SUCCEEDED(hr));
	}

	// check 4X MSAA quility Support from hardware
	// All Direct3D 11 capable devices support 4X MSAA for all render 
	// target formats, so we only need to check quality support.

	HR(m_pD3D11Device->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality));
	assert(m_4xMsaaQuality > 0);

	// Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = m_nClientWidth;
	sd.BufferDesc.Height = m_nClientHeight;
	// Rate
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (m_bEnable4xMsaa){
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = g_hWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	// To correctly create the swap chain, we must use the IDXGIFactory that was
	// used to create the device.  If we tried to use a different IDXGIFactory instance
	// (by calling CreateDXGIFactory), we get an error: "IDXGIFactory::CreateSwapChain: 
	// This function is being called with a device from a different IDXGIFactory."

	IDXGIDevice* dxgiDevice = 0;
	HR(m_pD3D11Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	HR(dxgiFactory->CreateSwapChain(m_pD3D11Device, &sd, &m_pSwapChain));

	SAFE_RELEASE(dxgiDevice);
	SAFE_RELEASE(dxgiAdapter);
	SAFE_RELEASE(dxgiFactory);

	// currently do not bind a resource to pipeline stage directly
	// Resize the swap chain and recreate the render target view.
	ID3D11Texture2D* backBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(&backBuffer)); // get swapChain buffer
	m_pD3D11Device->CreateRenderTargetView(backBuffer, 0, &m_RenderTargetView);
	SAFE_RELEASE(backBuffer);

	// Create the depth/stencil buffer and view.
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = m_nClientWidth;
	depthStencilDesc.Height = m_nClientHeight;
	depthStencilDesc.MipLevels = 1; // number of mipmap levels. it will cover at texture
	depthStencilDesc.ArraySize = 1; // number of texture in texture array
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // format of texels
	//SampleDesc : the number of multismaples and quility level
	//usage -
	//D3D11_USAGE_DEFAULT - CPU cannot read of write on the gpu
	//D3D11_USAGE_IMMUTABLE - Resurce will be read only by gpu
	//D3D11_USAGE_DYNAMIC- should avoid
	//D3D11_USAGE_STAGING- copy cpu to gpu - slow, should avoid
	//bindflag -
	//D3D11_BIND_RENDER_TARGET: The texture will be bound as a render target to the pipeline.
	//D3D11_BIND_SHADER_RESOURCE : The texture will be bound as a shader resource to the pipeline.
	// cpu Acces flag
	//

	// Use 4X MSAA? --must match swap chain MSAA values.
	if (m_bEnable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	// No MSAA
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	HR(m_pD3D11Device->CreateTexture2D(
		&depthStencilDesc, // descripton of texture to create
		0,
		&m_pDepthStencilBuffer // return pointer to depth/stencil buffer
		));

	HR(m_pD3D11Device->CreateDepthStencilView(
		m_pDepthStencilBuffer, // resource we want to create a view to
		0,
		&m_pDepthStencilView // return depth/stencil view
		));

	m_pD3D11DIC->OMSetRenderTargets(1, &m_RenderTargetView, m_pDepthStencilView);
	m_stScreenViewPort.TopLeftX = 0;
	m_stScreenViewPort.TopLeftY = 0;
	m_stScreenViewPort.Width = static_cast<float>(m_nClientWidth);
	m_stScreenViewPort.Height = static_cast<float>(m_nClientHeight);
	m_stScreenViewPort.MinDepth = 0.0f;
	m_stScreenViewPort.MaxDepth = 1.0f;

	m_pD3D11DIC->RSSetViewports(1, &m_stScreenViewPort);
}


cDeviceManager::~cDeviceManager()
{

}

void cDeviceManager::Destroy(){
	SAFE_RELEASE(m_pDepthStencilBuffer);
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_RELEASE(m_RenderTargetView);
	SAFE_RELEASE(m_pDepthStencilBuffer);

	//SAFE_RELEASE(m_pSwapChain);
	if (m_pD3D11DIC)
		m_pD3D11DIC->ClearState();

	SAFE_RELEASE(m_pD3D11DIC);
	SAFE_RELEASE(m_pD3D11Device);
}

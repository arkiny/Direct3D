#pragma once

#define g_pDevice cDeviceManager::GetInstance()->GetDevice()
#define g_pDeviceContext cDeviceManager::GetInstance()->GetDC()
#define g_pSwapChain cDeviceManager::GetInstance()->GetSwapChain()
#define g_pRTView cDeviceManager::GetInstance()->GetRT()
#define g_pDSView cDeviceManager::GetInstance()->GetDS()

class cDeviceManager
{
	SINGLETONE(cDeviceManager);
private:
	ID3D11Device*			m_pD3D11Device;
	ID3D11DeviceContext*	m_pD3D11DIC;
	IDXGISwapChain*			m_pSwapChain;

	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11Texture2D*		m_pDepthStencilBuffer;
	ID3D11DepthStencilView* m_pDepthStencilView;
	
	D3D11_VIEWPORT			m_stScreenViewPort;

	UINT					m_4xMsaaQuality;

	int						m_nClientHeight = 720;
	int						m_nClientWidth = 1280;

	bool					m_bEnable4xMsaa = true;

public:
	ID3D11Device* GetDevice(){ return m_pD3D11Device; }
	ID3D11DeviceContext* GetDC() { return m_pD3D11DIC; }
	IDXGISwapChain* GetSwapChain() { return m_pSwapChain; }
	ID3D11RenderTargetView* GetRT() { return m_RenderTargetView; }
	ID3D11DepthStencilView* GetDS() { return m_pDepthStencilView; }

	void Destroy();
};


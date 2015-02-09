#include "stdafx.h"
#include "cButton.h"


cButton::cButton():
m_pTextureNormal(NULL),
m_pTextureOn(NULL),
m_pTextureClick(NULL)
{
}


cButton::~cButton()
{
	SAFE_RELEASE(m_pTextureNormal);
	SAFE_RELEASE(m_pTextureOn);
	SAFE_RELEASE(m_pTextureClick);
}

void cButton::Setup(std::string sFolder, std::string sFile, std::string sExtension){
	cUserInterface::Setup(sFolder, sFile, sExtension);
	HRESULT hr;
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		(sFolder + sFile + sExtension).c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		NULL,
		NULL,
		&m_pTextureNormal);

	std::string ss;
	ss = sFolder + sFile + "On" + sExtension;
	hr=D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		ss.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		NULL,
		NULL,
		&m_pTextureOn);
	_ASSERT(hr == S_OK); 

	ss = sFolder + sFile + "Click" + sExtension;
	hr = D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		ss.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		NULL,
		NULL,
		&m_pTextureClick);
	_ASSERT(hr == S_OK);
}

void cButton::Update(float delta){
	cUserInterface::Update(delta);
	D3DXVECTOR3 worldPos = *m_pParentLeftTop + m_pTransform->GetPosition();

	if (m_pMouseLoc->x >= m_stOriRect.left	&& m_pMouseLoc->x <= m_stOriRect.right &&
		m_pMouseLoc->y >= m_stOriRect.top && m_pMouseLoc->y <= m_stOriRect.bottom){
		m_bCursorOn = true;
	}
	else {
		m_bCursorOn = false;
	}

	if (m_bClicked){
		if (m_bCursorOn && !*m_pClicked){
			m_bActivated = true;
			m_bClicked = false;
		}
		else {
			m_bActivated = false;
			m_bClicked = false;
		}
	}

	if (m_bCursorOn && *m_pClicked){
		if (m_pTextureClick && m_pTexture != m_pTextureClick){
			m_pTexture->Release();
			m_pTexture = m_pTextureClick;
			m_pTexture->AddRef();
		}
		m_bClicked = true;
	}
	else if (m_bCursorOn){
		if (m_pTextureOn && m_pTextureOn != m_pTexture){
			m_pTexture->Release();
			m_pTexture = m_pTextureOn;
			m_pTexture->AddRef();
		}
	}
	else {
		if (m_pTextureNormal && m_pTexture != m_pTextureNormal){
			m_pTexture->Release();
			m_pTexture = m_pTextureNormal;
			m_pTexture->AddRef();
		}
	}
}
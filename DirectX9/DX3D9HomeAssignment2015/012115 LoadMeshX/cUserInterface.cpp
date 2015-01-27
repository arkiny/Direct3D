#include "stdafx.h"
#include "cUserInterface.h"


cUserInterface::cUserInterface() 
	:
	m_pTexture(NULL),
	m_pSprite(NULL),
	m_pParentLeftTop(NULL),
	m_pDelegate(NULL)
{
	ZeroMemory(&m_stImageInfo,	sizeof(m_stImageInfo));
	ZeroMemory(&m_stRect,		sizeof(m_stRect));
}


cUserInterface::~cUserInterface()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSprite);
	for (auto p : m_setChildUI){
		SAFE_RELEASE(p);
	}
}

void cUserInterface::Setup(std::string sFolder, std::string sFile){
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		(sFolder + sFile).c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo,
		NULL,
		&m_pTexture);
	SetRect(&m_stRect, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);
}

void cUserInterface::Update(float delta){
	for (auto p : m_setChildUI){
		p->Update(delta);
	}
}

void cUserInterface::Render(){
	if (m_pSprite)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		
		if (m_pParentLeftTop){
			D3DXVECTOR3 worldPos = *m_pParentLeftTop + m_pTransform->GetPosition();
			D3DXMATRIXA16 mat;
			D3DXMatrixTranslation(&mat, worldPos.x, worldPos.y, worldPos.z);
			m_pSprite->SetTransform(&mat);
		}
		else {
			m_pSprite->SetTransform(GetTransformMatrix());
		}		
		m_pSprite->Draw(m_pTexture,
			&m_stRect,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_XRGB(255, 255, 255));
		m_pSprite->End();
	}

	for (auto p : m_setChildUI){
		p->Render();
	}
}

void cUserInterface::AddChild(cUserInterface* pChild){
	if (m_setChildUI.find(pChild) == m_setChildUI.end()){
		pChild->SetParentLeftTop(m_pTransform->getPosPointer());
		m_setChildUI.insert(pChild);
	}
}

void cUserInterface::SetParentLeftTop(D3DXVECTOR3* pos){
	m_pParentLeftTop = pos;
}

void cUserInterface::SetPosition(D3DXVECTOR3& pos){
	m_pTransform->SetPosition(pos);
}

D3DXVECTOR3& cUserInterface::GetLeftTopPosition(){
	return m_pTransform->GetPosition();
}

void cUserInterface::UserInterfaceActivation(cUserInterface* pSender){
	int a = 0;
}

void cUserInterface::UserInterfaceFinished(cUserInterface* pSender){
	int a = 0;
}
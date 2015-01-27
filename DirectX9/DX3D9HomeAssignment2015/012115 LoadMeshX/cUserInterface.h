#pragma once

class cUserInterface;

__interface iUserInterfaceDelegate{
	virtual void UserInterfaceActivation(cUserInterface* pSender) = 0;
	virtual void UserInterfaceFinished(cUserInterface* pSender) = 0;
};

class cUserInterface : public cGameObject, public iUserInterfaceDelegate
{
protected:
	std::set<cUserInterface*>			m_setChildUI;
	LPDIRECT3DTEXTURE9					m_pTexture;
	LPD3DXSPRITE						m_pSprite;
	D3DXIMAGE_INFO						m_stImageInfo;
	RECT								m_stRect;
	D3DXVECTOR3*						m_pParentLeftTop;
	SYNTHESIZE(iUserInterfaceDelegate*, m_pDelegate, Delegate);

public:
	cUserInterface();
	virtual ~cUserInterface();

	virtual void Setup(std::string sFolder, std::string sFile);
	virtual void Update(float delta);
	virtual void Render();
	virtual void AddChild(cUserInterface* pChild);

	virtual void SetParentLeftTop(D3DXVECTOR3* pos);
	virtual void SetPosition(D3DXVECTOR3& pos);

	virtual D3DXVECTOR3& GetLeftTopPosition();

public:
	virtual void UserInterfaceActivation(cUserInterface* pSender) override;
	virtual void UserInterfaceFinished(cUserInterface* pSender) override;
};


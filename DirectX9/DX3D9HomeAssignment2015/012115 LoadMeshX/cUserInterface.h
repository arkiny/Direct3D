#pragma once
#include "iUserInterfaceDelegate.h"

class cUserInterface : public cGameObject
{
protected:
	std::set<cUserInterface*>			m_setChildUI;
	LPDIRECT3DTEXTURE9					m_pTexture;
	LPD3DXSPRITE						m_pSprite;
	D3DXIMAGE_INFO						m_stImageInfo;
	RECT								m_stRect;
	RECT								m_stOriRect;
	D3DXVECTOR3*						m_pParentLeftTop;
	POINT*								m_pMouseLoc;
	bool*								m_pClicked;
	SYNTHESIZE(iUserInterfaceDelegate*, m_pDelegate, Delegate);

private:
	
	
public:
	cUserInterface();
	virtual ~cUserInterface();

	virtual void Setup(std::string sFolder, std::string sFile, std::string sExtension);
	
	virtual void Update(float delta);
	virtual void UpdateRectangle(D3DXVECTOR3* parentMat);
	
	virtual void Render();
	virtual void Render(D3DXVECTOR3* parentMat);

	virtual void AddChild(cUserInterface* pChild);

	virtual void SetParentLeftTop(D3DXVECTOR3* pos);
	virtual void SetPosition(D3DXVECTOR3& pos);

	virtual D3DXVECTOR3& GetLeftTopPosition();

	virtual void SetMousePosPointer(POINT* mousPos);
	virtual void SetMouseClickInfo(bool* mousclick);
};


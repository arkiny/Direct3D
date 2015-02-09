#pragma once
#include "cUserInterface.h"

class cButton : public cUserInterface
{
protected:
	bool								m_bActivated = false;
	bool								m_bClicked = false;
	bool								m_bCursorOn = false;

	LPDIRECT3DTEXTURE9					m_pTextureNormal;
	LPDIRECT3DTEXTURE9					m_pTextureOn;
	LPDIRECT3DTEXTURE9					m_pTextureClick;

public:
	cButton();
	virtual ~cButton();
	virtual void Setup(std::string sFolder, std::string sFile, std::string sExtension);
	virtual void Update(float delta);
};


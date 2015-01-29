#pragma once
#include "cUserInterface.h"
class cTextBox : public cUserInterface
{
protected:
	std::string*						m_pCaption;
	LPD3DXFONT							m_pFont;
	RECT								m_recFontRect;

public:
	cTextBox();
	virtual ~cTextBox();

	virtual void Setup(std::string sFolder, std::string sFile, std::string sExtension) override;
	virtual void Render(D3DXVECTOR3* parentPos) override;

	void SetCaptionTarget(std::string* pTarget){
		m_pCaption = pTarget;
	}
};


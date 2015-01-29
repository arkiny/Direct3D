#include "stdafx.h"
#include "cTextBox.h"


cTextBox::cTextBox() :
m_pFont(NULL),
m_pCaption(NULL)
{
	ZeroMemory(&m_recFontRect, sizeof(RECT));
}


cTextBox::~cTextBox()
{
	SAFE_RELEASE(m_pFont);
}

void cTextBox::Setup(std::string sFolder, std::string sFile, std::string sExtension){
	cUserInterface::Setup(sFolder, sFile, sExtension);
	D3DXCreateFont(g_pD3DDevice,		//D3D Device
		16,								//Font height
		0,								//Font width
		FW_NORMAL,						//Font Weight
		1,								//MipLevels
		false,							//Italic
		DEFAULT_CHARSET,				//CharSet
		OUT_DEFAULT_PRECIS,				//OutputPrecision
		ANTIALIASED_QUALITY,			//Quality
		DEFAULT_PITCH | FF_DONTCARE,	//PitchAndFamily
		"Consolas",						//pFacename,
		&m_pFont);						//ppFont
}

void cTextBox::Render(D3DXVECTOR3* parentPos){
	cUserInterface::Render(parentPos);
	if (m_pFont){
		if (m_pCaption){
			SetRect(
				&m_recFontRect, 
				m_stOriRect.left + 10.0f, 
				m_stOriRect.top + 10.0f, 
				m_stOriRect.right - 10.0f, 
				m_stOriRect.bottom - 10.0f);
			m_pFont->DrawText(NULL,							//pSprite
				m_pCaption->c_str(),						//pString
				-1,											//Count
				&m_recFontRect,								//pRect
				DT_LEFT | DT_NOCLIP,						//Format,
				D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));			//Color
		}
	}		
}
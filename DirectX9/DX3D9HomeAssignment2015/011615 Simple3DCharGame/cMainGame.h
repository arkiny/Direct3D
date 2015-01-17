#pragma once

#include "gIObject.h"

class cAxis;
class cGrid;
class cCamera;
class cPyramid;
class cCharacter;
class cCard;

class cMainGame : public cObject, public iActionDelegate
{
private:
	POINT								m_mousePos;

	cAxis*								m_cAxis;
	cGrid*								m_cGrid;
	cCamera*							m_cCamera;
	cPyramid*							m_pPyramid;
	cCharacter*							m_pCharacter;

	LPD3DXFONT							m_pFont;
	RECT								m_recFontRect;

	std::vector<cCard*>					m_vecSteppedCard;
	std::vector<cCard*>					m_vecCards;
	
	int									m_nScore;
	float								m_fAccumTime = 0.0f;
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update(float delta);
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void OnActionFinish(cAction* pSender);

	void CardCollideHandler(cCharacter* pCharacter, cCard* pChard);
};


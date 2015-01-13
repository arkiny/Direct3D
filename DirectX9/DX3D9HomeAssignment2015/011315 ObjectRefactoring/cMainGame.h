#pragma once

#include "gIObject.h"

class cAxis;
class cGrid;
class cCamera;
class cPyramid;
class cNTeapot;
class cAPoint;

class cMainGame : public cObject
{
private:
	POINT								m_mousePos;

	cAxis*								m_cAxis;
	cGrid*								m_cGrid;
	cCamera*							m_cCamera;
	cPyramid*							m_pPyramid;

	cNTeapot*							m_pTeapot;
	std::vector<cAPoint*>				m_vecAPoints;

	std::vector<ST_PN_VERTEX>			m_vecTest;
	LPD3DXFONT							m_pFont;
	RECT								m_recFontRect;

public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update(float delta);
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


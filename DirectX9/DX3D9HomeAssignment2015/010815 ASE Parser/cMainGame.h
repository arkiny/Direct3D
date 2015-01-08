#pragma once

class cCamera;
class cGroup;
class cMesh;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update(float delta);
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
private:
	POINT m_mousePos;
	iMap* m_pMap;
	
	std::vector<cGroup*>	m_vecGroupBox;
	std::vector<cGroup*>	m_vecGroup;
	std::vector<cGroup*>	m_vecSurface;

	cCamera*				m_pCamera;

	std::vector<ST_PN_VERTEX>			m_vecTest;
	LPD3DXFONT							m_pFont;
	RECT								m_recFontRect;

	float m_fAccumTime = 0.0f;
};


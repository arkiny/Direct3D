#pragma once

class cCircleRHW;

class cMainGame
{
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	cCircleRHW*					m_pCircle1;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


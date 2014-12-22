#pragma once

class cMyCube;
class cCamera;

class cMainGame
{
private:
	//std::vector<ST_PC_VERTEX>	m_vecVertex;
	cMyCube* m_cCube;
	cMyCube* m_cCube2;
	cCamera* m_cCamera;
public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update(float delta);
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


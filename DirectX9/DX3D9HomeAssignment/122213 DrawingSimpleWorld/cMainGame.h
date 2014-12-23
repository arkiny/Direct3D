#pragma once

class cMyCube;
class cCamera;
class cAxis;
class cGrid;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	void update(float delta);
	void setup();
	void render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	cMyCube* m_cCube;
	cCamera* m_cCamera;
	cAxis* m_cAxis;
	cGrid* m_cGrid;
};


#pragma once

class cMyCube;

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
};


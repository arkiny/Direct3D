#pragma once

class cAxis;
class cGrid;
class cMyCube;
class cTracingCamera;
class cCharacter;

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
	cAxis* m_cAxis;
	cGrid* m_cGrid;
	cCharacter* m_cCharacter;
	cTracingCamera* m_cCamera;

	bool m_bClicked;
	POINT m_mousePos;
};


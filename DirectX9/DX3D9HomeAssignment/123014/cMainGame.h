#pragma once

class cAxis;
class cGrid;
class cCube;
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

	POINT m_mousePos;
};


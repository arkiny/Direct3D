#pragma once

#include "gIObject.h"

class cAxis;
class cGrid;
class cCamera;
//class cCharacter;
class cPlayer;
class cBoxfromFile;


class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update(float delta);
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	void CollisionCheck(cPlayer* player);

private:

	// Grid Picking
	gIObject* getBoxInfoFromGrid(int x, int z);

	POINT m_mousePos;

	std::vector<gIObject*> m_vecBox;

	int			m_nScore = 0;
	float		m_fTimeLeft = 30.0f;

	cPlayer* m_pPlayer;
	cBoxfromFile* m_pBoxFile;
	//cCharacter* m_cCharacter;
	cAxis* m_cAxis;
	cGrid* m_cGrid;
	cCamera* m_cCamera;
	LPD3DXFONT							m_pFont;
	RECT								m_recFontRect;

	float m_fAccumTime = 0.0f;
	//PlayerObj - State based 
	//ObjectList - Box List
	//CoordinateInfo - Box List based on Grid coordinate
};


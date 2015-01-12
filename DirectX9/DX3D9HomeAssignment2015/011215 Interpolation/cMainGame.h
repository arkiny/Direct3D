#pragma once

#include "gIObject.h"

class cAxis;
class cGrid;
class cCamera;
class cPyramid;
class cTeapot;
class cVertexPoints;

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

	// Grid Picking
	//gIObject* getBoxInfoFromGrid(int x, int z);

	POINT m_mousePos;

	//std::vector<gIObject*> m_vecBox;

	int			m_nScore = 0;
	float		m_fTimeLeft = 30.0f;

	cAxis* m_cAxis;
	cGrid* m_cGrid;
	cCamera* m_cCamera;
	cPyramid* m_pPyramid;
	cTeapot* m_pTeapot;
	cTeapot* m_pTeapoat2;
	cVertexPoints* m_pVertex;

	std::vector<ST_PN_VERTEX> m_vecTest;
	LPD3DXFONT							m_pFont;
	RECT								m_recFontRect;

	float m_fAccumTime = 0.0f;
	//PlayerObj - State based 
	//ObjectList - Box List
	//CoordinateInfo - Box List based on Grid coordinate
};


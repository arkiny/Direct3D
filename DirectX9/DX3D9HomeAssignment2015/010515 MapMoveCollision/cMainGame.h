#pragma once

#include "gIObject.h"

class cAxis;
class cGrid;
class cCamera;
class cPyramid;

//class cCharacter;
class cPlayer;
//class cBoxfromFile;
class cObjectOldFromParser;
class cGroup;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update(float delta);
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	void CollisionCheck(cPlayer* player){}

	bool moveCheck(cPlayer* player, D3DXVECTOR3& target, float& y);

	float heightCheck(cPlayer* player);

private:

	// Grid Picking
	//gIObject* getBoxInfoFromGrid(int x, int z);

	POINT m_mousePos;

	//std::vector<gIObject*> m_vecBox;

	int			m_nScore = 0;
	float		m_fTimeLeft = 30.0f;

	cPlayer* m_pPlayer;
	//cBoxfromFile* m_pBoxFile;
	//cCharacter* m_cCharacter;
	cAxis* m_cAxis;
	cGrid* m_cGrid;
	cCamera* m_cCamera;
	cPyramid* m_pPyramid;
	//cObjectOldFromParser* m_pObject;
	//cObjectOldFromParser* m_pObject2;
	//cObjectOldFromParser* m_pObject3;

	std::vector<cGroup*>	m_vecGroup;
	std::vector<cGroup*>	m_vecSurface;


	std::vector<ST_PN_VERTEX> m_vecTest;
	LPD3DXFONT							m_pFont;
	RECT								m_recFontRect;

	float m_fAccumTime = 0.0f;
	//PlayerObj - State based 
	//ObjectList - Box List
	//CoordinateInfo - Box List based on Grid coordinate
};


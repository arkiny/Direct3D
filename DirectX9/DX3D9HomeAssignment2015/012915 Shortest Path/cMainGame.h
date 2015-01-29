#pragma once

#include "gIObject.h"

class cAxis;
class cGrid;
class cCamera;
class cPyramid;
class cCharacter;
class cHeightMap;
class cSkinnedMeshObject;
class cAPoint;
//
class cGraph;
class cDjikstraSP;
class cEdge;
//
class cMainGame : public cObject, public iActionDelegate
{

private:
	POINT								m_mousePos;

	cAxis*								m_cAxis;
	cGrid*								m_cGrid;
	cCamera*							m_cCamera;
	cPyramid*							m_pPyramid;
	cCharacter*							m_pCharacter;
	cHeightMap*							m_pHeightMap;
	cSkinnedMeshObject*					m_pSkinnedMeshObject;
	
	int									m_nCurrentNode = -1;
	int									m_nDestination = -1;

	std::vector<cAPoint*>				m_pvecPoints;
	

	cGraph*								m_pGraph;
	std::vector<cEdge*>					m_vecEdges;

	LPD3DXFONT							m_pFont;
	RECT								m_recFontRect;

	bool								m_bIntShow = true;
	int									m_nScore;
	float								m_fAccumTime = 0.0f;

	POINT								m_stMouseLocation;
	bool								m_bClicked = false;

public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update(float delta);
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	virtual void OnActionFinish(cAction* pSender);
	virtual void OnActionMoveTargetUpdated(cAction* pSender, int TargetNode);
};


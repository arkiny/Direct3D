#pragma once

//class cPlain;
//class cSkinnedMeshObject;
//class cTileMap;
//class cPlayer;

class cBox;
class cAxis;
class cGrid;
class cCamera;
class cPyramid;
class cSphere;

class cMainGame : public cObject, public iActionDelegate
{
private:

	std::vector<cSphere*>				m_vecSpheres;

	POINT								m_mousePos;

	cAxis*								m_cAxis;
	cGrid*								m_cGrid;
	cCamera*							m_cCamera;
	cPyramid*							m_pPyramid;

	cSphere*							m_pSphere;

	bool								m_bCharacterSelected = false;



	int									m_nCurrentNode = -1;
	int									m_nDestination = -1;

	int m_nWidth = 0;
	int m_nHeight = 0;
	 
	LPD3DXFONT							m_pFont;
	RECT								m_recFontRect;

	bool								m_bIntShow = true;
	int									m_nScore;
	float								m_fAccumTime = 0.0f;

	POINT								m_stMouseLocation;
	bool								m_bClicked = false;

private:
	//cBox*				getBoxInfoFromGrid(int x, int z);

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


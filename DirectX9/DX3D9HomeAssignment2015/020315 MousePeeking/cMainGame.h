#pragma once

class cAxis;
class cGrid;
class cCamera;
class cPyramid;
class cPlain;
class cSphere;
class cSkinnedMeshObject;
class cTileMap;
class cPlayer;
class cBox;

class cMainGame : public cObject, public iActionDelegate
{

private:
	POINT								m_mousePos;

	cAxis*								m_cAxis;
	cGrid*								m_cGrid;
	cCamera*							m_cCamera;
	cPyramid*							m_pPyramid;
	cPlain*								m_pPlain;
	cSphere*							m_pSphere;

	//cCharacter*							m_pCharacter;
	//cHeightMap*							m_pHeightMap;
	//std::vector<cAPoint*>					m_pvecPoints;
	//cGraph*								m_pGraph;
	//std::vector<cEdge*>					m_vecEdges;

	//
	cPlayer* m_pPlayer;
	std::vector<cBox*> m_vecBox;
	cBox* getBoxInfoFromGrid(int x, int z);
	cTileMap* m_pTileMap;
	//

	cSkinnedMeshObject*					m_pSkinnedMeshObject; // selected;
	std::vector<cSkinnedMeshObject*>	m_vecSkinnedMeshObjects;

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


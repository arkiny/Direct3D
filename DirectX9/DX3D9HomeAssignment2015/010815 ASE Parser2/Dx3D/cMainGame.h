#pragma once

class cCube;
class cGrid;
class cCamera;
class cCubeMan;
class cGroup;
class iMap;
class cIndexCube;
class cMtlTex;
class cASELoader;
class cASEModelLoader;
class stMeshInfo;
class cAseParser;

class cMainGame
{
private:
	cGrid*					m_pGrid;
	cCamera*				m_pCamera;
	cCubeMan*				m_pCubeMan;
	iMap*					m_pMap;
	cIndexCube*				m_pIndexCube;
	LPD3DXFONT				m_pFont;
	std::vector<cGroup*>	m_vecGroup;
	std::vector<cGroup*>	m_vecSurface;
	LPD3DXMESH				m_pMesh;
	std::vector<cMtlTex*>	m_vecMtlTex2;
	cASELoader*				m_pASELoader;
	cASEModelLoader*		m_pASEModelLoader;
	std::vector<LPD3DXMESH> m_vecMesh;
	std::vector<cMtlTex*>	m_vecMtlTex;
	std::vector<stMeshInfo*> m_vecMeshInfo;
	cAseParser*				m_pAseParser;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


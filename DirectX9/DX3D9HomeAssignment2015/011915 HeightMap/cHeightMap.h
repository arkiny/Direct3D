#pragma once

class cMtlTex;

class cHeightMap : public cGameObject
{
private:
	std::vector<ST_PNT_VERTEX>	m_vecVertex;
	LPD3DXMESH					m_pMesh;
	std::vector<int>			m_vecIndex;
	cMtlTex*					m_pMtlTex;

	std::vector<DWORD>			m_vecHeight;
public:
	cHeightMap();
	~cHeightMap();

	void Setup();
	void Update(float delta);
	void Render();
};


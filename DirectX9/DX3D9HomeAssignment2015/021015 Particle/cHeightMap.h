#pragma once
#include "iMap.h"

class cMtlTex;

class cHeightMap : public cGameObject, public iMap
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
	virtual float GetHeight(OUT bool& isLand, IN D3DXVECTOR3* pvPosition);
};


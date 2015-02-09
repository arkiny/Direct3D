#pragma once
#include "iMap.h"
class cPlain : public iMap
{
private:
	std::vector<ST_PN_VERTEX>	m_vecVertices;
	std::vector<D3DXVECTOR3>	m_vecPoints;
	
	D3DMATERIAL9				m_stMaterial;

public:
	cPlain();
	~cPlain();
	
	std::vector<D3DXVECTOR3>& GetVerticesPoints();

	void Setup();
	void Render();
	virtual float GetHeight(OUT bool& isLand, IN D3DXVECTOR3* pvPosition);
};


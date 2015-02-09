#pragma once
#include "gIObject.h"

class cTile;
class cBox : public gIOBJECT_BOX
{
public:
	cBox();
	~cBox();

	void init();
	void update(float delta);
	void render();

	bool collidewith(gIObject* obj);
	bool collidewithPoint(D3DXVECTOR3& pos);

	D3DXVECTOR3& getWorldPosition();
	GRIDPOSITION& getGridPosition();

	void setPositionByGrid(GRIDPOSITION& gridpos);
	void setPositionByWorldCoord(D3DXVECTOR3& pos);

	void getHit(int dmg);
	void setHP(int hp) { m_hp = hp; }
	int getHP(){ return m_hp; }

	void setTile(cTile* pTile);
	void Destroy(){ delete this; }
	std::vector<D3DXVECTOR3>& GetSurfacePoints(){ return m_vecSuface; }

private:
	cTile*						m_pTile;

	//LPD3DXMESH					m_p3DFont;

	//LPD3DXMESH					m_pF;
	//LPD3DXMESH					m_pG;
	//LPD3DXMESH					m_pH;

	D3DMATERIAL9				m_stFMtl;

	//std::vector<ST_PC_VERTEX>	m_vecLineVertex;
	std::vector<ST_PC_VERTEX>	m_vecVertex;

	std::vector<D3DXVECTOR3>	m_vecSuface;

	std::vector<ST_PC_VERTEX>	m_vecSufaceDebug;

	int							m_hp = 0;
	D3DXVECTOR3					m_vPosition;
	GRIDPOSITION				m_stGridPosition;

	float						m_vSize = 1.0f;
};


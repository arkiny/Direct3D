#pragma once
#include "gIObject.h"
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
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	int							m_hp = 0;
	D3DXVECTOR3					m_vPosition;
	GRIDPOSITION				m_stGridPosition;
	float						m_vSize = 5.0f;
};


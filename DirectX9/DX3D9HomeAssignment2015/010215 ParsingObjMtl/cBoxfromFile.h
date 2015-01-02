#pragma once

class cObjectParser;

class cBoxfromFile {
public:
	cBoxfromFile();
	~cBoxfromFile();

	void init();
	void update(float delta);
	void render();

	/*bool collidewith(gIObject* obj);
	bool collidewithPoint(D3DXVECTOR3& pos);*/

	D3DXVECTOR3& getWorldPosition();
	GRIDPOSITION& getGridPosition();

	void setPositionByGrid(GRIDPOSITION& gridpos);
	void setPositionByWorldCoord(D3DXVECTOR3& pos);

	void getHit(int dmg);
	void setHP(int hp) { m_hp = hp; }
	int getHP(){ return m_hp; }

private:
	LPDIRECT3DTEXTURE9			m_pTexture;
	std::vector<ST_PNT_VERTEX>	m_vecVertex;
	int							m_hp;
	D3DXVECTOR3					m_vPosition;
	GRIDPOSITION				m_stGridPosition;

	cObjectParser*				m_pObjectParser;

};
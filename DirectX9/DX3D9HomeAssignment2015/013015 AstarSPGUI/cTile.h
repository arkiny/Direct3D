#pragma once

struct ST_FGHINFO{
	float m_fG;
	float m_fH;
	float m_fF;
	ST_FGHINFO() : m_fF(0), m_fH(0), m_fG(0){};
	ST_FGHINFO(float f, float g, float h) : m_fF(f), m_fH(g), m_fG(h){};
};


class cTile
{
public:
	enum eTILETYPE{
		TILE_EMPTY,
		TILE_BLOCK,
		TILE_START,
		TILE_DEST,
		TILE_OPENED,
		TILE_CLOSED,
		TILE_PATH
		};

private:

	eTILETYPE	 m_eType;
	ST_FGHINFO	 m_stFGHINFO;

	POINT m_stPosition;
	POINT m_stParentPos;

public:
	cTile();
	~cTile();
	// Tile Add
	cTile(int x, int y);
	
	void Check(cTile* pFromTile, float fCheckG);

	// Getter
	POINT&		GetPosition(){ return m_stPosition; }
	eTILETYPE	GetType() { return m_eType; }
	ST_FGHINFO& GetFGH() { return m_stFGHINFO; }
	POINT&		GetParentPosition() { return m_stParentPos; }

	// Setter
	void SetType(eTILETYPE etype) { m_eType = etype; }
	void SetFGH(float _f, float _g, float _h) { m_stFGHINFO = { _f, _g, _h }; }
	void SetFGH(ST_FGHINFO& in) { m_stFGHINFO = in; }
	void SetParentPos(POINT& p){ m_stParentPos = p; }
};


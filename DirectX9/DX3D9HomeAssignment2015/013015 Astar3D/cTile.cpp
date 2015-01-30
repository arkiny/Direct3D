#include "stdafx.h"
#include "cTile.h"

cTile::cTile() :
	m_stFGHINFO(0,0,0),
	m_eType(TILE_EMPTY)
{
	ZeroMemory(&m_stParentPos, sizeof(POINT));
	ZeroMemory(&m_stPosition, sizeof(POINT));
}


cTile::~cTile()
{

}

cTile::cTile(int x, int y) :
	m_stFGHINFO(0, 0, 0),
	m_eType(TILE_EMPTY)
{
	// = { 0, 0 };
	m_stPosition = { x, y };
	m_stParentPos = m_stPosition;
}

void cTile::Check(cTile* pFromTile, float fCheckG){
	if (fCheckG < m_stFGHINFO.m_fG){
		m_stParentPos = pFromTile->GetPosition();
		m_stFGHINFO.m_fG = fCheckG;
		m_stFGHINFO.m_fF = m_stFGHINFO.m_fG + m_stFGHINFO.m_fH;
	}
	else{

	}
}
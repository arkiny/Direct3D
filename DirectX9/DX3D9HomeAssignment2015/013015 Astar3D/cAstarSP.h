#pragma once

class cTile;
class cTileMap;

class cAstarSP
{
private:
	cTile*		m_pCurrentTile = NULL;
	cTileMap*	m_pTileMap;
	POINT		m_stStartTile;
	POINT		m_stDestination;

	std::set<cTile*> m_vecClosedTiles;
	std::set<cTile*> m_vecOpenTiles;

	void Init();
	void ExpandList(cTile* from);
public:
	cAstarSP();
	~cAstarSP();

	cAstarSP(cTileMap* pTileMap, POINT stStile, POINT stDtile);

	// Calculate
	void CalculatePath();
	
	// OUT
	void PathToString();
	void GetPathPointVector(
		OUT std::vector<cTile*>& vecPathTiles, 
		OUT std::vector<cTile*>& vecOpenTiles,
		OUT std::vector<cTile*>& vecClosedTiles);
};


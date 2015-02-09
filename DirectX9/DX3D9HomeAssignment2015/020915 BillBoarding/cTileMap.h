#pragma once

class cTile;

class cTileMap
{
private:
	std::vector<cTile*> m_vecTiles;
	int m_nWidth, m_nHeight;
public:
	cTileMap();
	~cTileMap();

	cTileMap(int height, int width);
	cTile* GetTilePointer(int x, int y);
	void SetTileType(int x, int y, int type);
	void TileMapToString();
	POINT& GetBorder() { 
		POINT ret = { m_nWidth, m_nHeight };
		return ret;
	}
};


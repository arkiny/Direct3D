#include "stdafx.h"
#include "cTileMapLoader.h"
#include "cTileMap.h"
#include "cTile.h"


cTileMapLoader::cTileMapLoader()
{
}


cTileMapLoader::~cTileMapLoader()
{
}

void cTileMapLoader::LoadFromFile(std::string sFilePath, OUT cTileMap* tileMap, int Width, int Height, POINT& start, POINT& dest){
	/*m_pTileMap->SetTileType(0, 3, 1);
	m_pTileMap->SetTileType(1, 3, 1);
	m_pTileMap->SetTileType(2, 3, 1);*/
	
	FILE* pf = NULL;
	fopen_s(&pf, sFilePath.c_str(), "r");
	_ASSERT(pf != NULL);
	int x = 0;
	int y = 0;
	while (!feof(pf)){
		char input = getc(pf);
		if (input < 33) continue;
		if (input == 'E'){
			tileMap->SetTileType(x, y, cTile::eTILETYPE::TILE_EMPTY);
		}
		else if (input == 'S'){
			tileMap->SetTileType(x, y, cTile::eTILETYPE::TILE_START);
			start.x = x;
			start.y = y;
		}
		else if (input == 'D'){
			tileMap->SetTileType(x, y, cTile::eTILETYPE::TILE_DEST);
			dest.x = x;
			dest.y = y;
		}
		else if (input == 'B'){
			tileMap->SetTileType(x, y, cTile::eTILETYPE::TILE_BLOCK);
		}
		x++;
		if (x % Width == 0){
			x = 0;
			y++;
		}
	}
}
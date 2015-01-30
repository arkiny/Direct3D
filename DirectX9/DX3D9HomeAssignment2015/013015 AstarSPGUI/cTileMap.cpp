#include "stdafx.h"
#include "cTileMap.h"
#include "cTile.h"


cTileMap::cTileMap() :
m_nWidth(0), m_nHeight(0)
{
}


cTileMap::~cTileMap()
{
	for (auto p : m_vecTiles){
		delete p;
	}
}

cTileMap::cTileMap(int height, int width) 
	: m_vecTiles(height * width),
	m_nWidth(width), m_nHeight(height)
{
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			m_vecTiles[y*width + x] = new cTile(x, y);
		}
	}
}

void cTileMap::SetTileType(int x, int y, int type){
	m_vecTiles[y*m_nWidth + x]->SetType((cTile::eTILETYPE)type);
}

cTile* cTileMap::GetTilePointer(int x, int y){
	if (x < 0 || y < 0 || x >= m_nWidth || y >= m_nHeight){
		return NULL;
	}
	return m_vecTiles[y*m_nWidth + x];
}

void cTileMap::TileMapToString(){
	for (int y = 0; y < m_nHeight; y++){
		for (int x = 0; x < m_nWidth; x++){
			/*POINT curtilePos = m_vecTiles[y*m_nWidth + x]->GetPosition();
			std::cout << "(" << curtilePos.x << "," << curtilePos.y << ")\t";*/
			cTile::eTILETYPE type = m_vecTiles[y*m_nWidth + x]->GetType();
			switch (type)
			{
			case cTile::TILE_EMPTY:
				std::cout << "¡à";
				break;
			case cTile::TILE_BLOCK:
				std::cout << "¡á";
				break;
			case cTile::TILE_START:
				std::cout << "¨ß";
				break;
			case cTile::TILE_DEST:
				std::cout << "¨Ð";
				break;
			case cTile::TILE_OPENED:
				std::cout << "¨Û";
				break;
			case cTile::TILE_CLOSED:
				std::cout << "¨Ï";
				break;
			case cTile::TILE_PATH:
				std::cout << "¡Ú";
				break;
			default:
				break;
			}
		}
		std::cout << std::endl;
	}
}
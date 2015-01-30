#pragma once

class cTileMap;

class cTileMapLoader
{
public:
	cTileMapLoader();
	~cTileMapLoader();

	void LoadFromFile(std::string sFilePath, OUT cTileMap* tileMap, int Width, int Height, OUT POINT& start, OUT POINT& dest);
};


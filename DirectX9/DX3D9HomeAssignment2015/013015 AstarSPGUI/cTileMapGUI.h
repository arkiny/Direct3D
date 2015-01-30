#pragma once

class cTileMap;

class cTileMapGUI
{
private:
	// tileMap Loader should save data here
	cTileMap* m_pTileMap;

public:
	cTileMapGUI();
	~cTileMapGUI();

	// load and calculate here
	void Setup();
	void updateMap(RECT &clientRect);
	void render(HDC hdc);
};


// 013015 AStar Algorithm Proto.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "cTileMap.h"
#include "cTile.h"
#include "cAstarSP.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cTileMap a(7, 6); // height width
	a.SetTileType(0, 3, 1);
	a.SetTileType(1, 3, 1);
	a.SetTileType(2, 3, 1);
	a.TileMapToString();
	
	POINT start = { 0, 1 };
	POINT dest = { 0, 4 };
	cAstarSP sp(&a, start, dest);


	sp.CalculatePath();
	//sp.PathToString();

	std::vector<cTile*> path;
	std::vector<cTile*> closed;
	std::vector<cTile*> opened;

	sp.GetPathPointVector(path, opened, closed);
	//	
	

	

	std::cout << std::endl << "Opened :" << std::endl;
	for (size_t i = 0; i < opened.size(); i++){
		a.SetTileType(opened[i]->GetPosition().x, opened[i]->GetPosition().y, cTile::eTILETYPE::TILE_OPENED);
		//std::cout << "(" << opened[i]->GetPosition().x << "," << opened[i]->GetPosition().y << ")";
	}
	std::cout << std::endl << "Closed :" << std::endl;
	for (size_t i = 0; i < closed.size(); i++){
		a.SetTileType(closed[i]->GetPosition().x, closed[i]->GetPosition().y, cTile::eTILETYPE::TILE_CLOSED);
		//std::cout << "(" << closed[i]->GetPosition().x << "," << closed[i]->GetPosition().y << ")";
	}
	std::cout << "Path :" << std::endl;
	for (size_t i = 0; i < path.size(); i++){
		a.SetTileType(path[i]->GetPosition().x, path[i]->GetPosition().y, cTile::eTILETYPE::TILE_PATH);
		std::cout << "(" << path[i]->GetPosition().x << "," << path[i]->GetPosition().y << ")";
	}
	std::cout << std::endl;
	a.TileMapToString();

	system("pause");
	

	return 0;
}


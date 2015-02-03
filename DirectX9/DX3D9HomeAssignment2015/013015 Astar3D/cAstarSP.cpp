#include "stdafx.h"
#include "cAstarSP.h"
#include "cTile.h"
#include "cTileMap.h"
#include <algorithm>
#include <iostream>

cAstarSP::cAstarSP() :
m_pTileMap(NULL)
{
	ZeroMemory(&m_stStartTile, sizeof(POINT));
	ZeroMemory(&m_stDestination, sizeof(POINT));
}


cAstarSP::~cAstarSP()
{
}

cAstarSP::cAstarSP(cTileMap* pTileMap, POINT stStile, POINT stDtile) :
m_pTileMap(pTileMap),
m_stStartTile(stStile),
m_stDestination(stDtile)
{	 
	
}

void cAstarSP::Init(){
	cTile* StartTile = m_pTileMap->GetTilePointer(m_stStartTile.x, m_stStartTile.y);
	ST_FGHINFO StartTileFGH = StartTile->GetFGH();

	StartTileFGH.m_fH = fabs(StartTile->GetPosition().x - (float)m_stDestination.x) 
		+ abs(StartTile->GetPosition().y - (float)m_stDestination.y);
	StartTileFGH.m_fG = 0.0f;
	StartTileFGH.m_fF = StartTileFGH.m_fH + StartTileFGH.m_fG;
	StartTile->SetFGH(StartTileFGH);
	m_vecOpenTiles.insert(StartTile);
}

void cAstarSP::CalculatePath(){
	Init();
	while (!m_vecOpenTiles.empty()){		
		cTile* minTile = NULL;
		float minf = 99999.9f;

		for (auto p : m_vecOpenTiles){
			if (minf > p->GetFGH().m_fF){
				minf = p->GetFGH().m_fF;
				minTile = p;
			}
		}

		m_vecClosedTiles.insert(minTile);
		m_vecOpenTiles.erase(minTile);
		

		if (minTile->GetPosition().x == m_stDestination.x && minTile->GetPosition().y == m_stDestination.y){
			//Find Path
			break;
		}		
		ExtendList(minTile);
			
	}	
	// No Path;
}


void cAstarSP::ExtendList(cTile* from){
	// 8 way updates
	POINT parentPoint = from->GetPosition();
	//std::vector<POINT> eightWay;
	std::vector<cTile*> vecTiles;
	//std::list<cTile*> lstTiles;
	std::set<cTile*> setTiles;
	for (int y = -1; y < 2; y++){
		for (int x = -1; x < 2; x++){
			// exception list
			// if 8 way expansion meet border
			POINT a = { parentPoint.x + x, parentPoint.y + y };
			if (x == 0 && y == 0){
				continue;
			}
			if (parentPoint.x + x < 0 || parentPoint.x + x >= m_pTileMap->GetBorder().x ||
				parentPoint.y + y < 0 || parentPoint.y + y >= m_pTileMap->GetBorder().y){
				continue;
			}
			if (m_pTileMap->GetTilePointer(parentPoint.x + x, parentPoint.y + y)->GetType() == cTile::eTILETYPE::TILE_BLOCK){
				continue;
			}
			else{
				//vecTiles.push_back(m_pTileMap->GetTilePointer(a.x, a.y));
				setTiles.insert(m_pTileMap->GetTilePointer(a.x, a.y));
			}
		}
	}

	// exception 2, up left right down could be block
	// up is a block,		ignore(does not add) (-1, -1), (0, -1), (1, -1)
	// down is a block,		ignore(does not add) (-1, 1), (0, 1), (1, 1)
	// left is a block,		ignore(does not add) (-1, -1), (-1, 0), (-1, 1)
	// right is a block,	ignore(does not add) (1, -1), (1, 0), (1, 1)
	if (parentPoint.y - 1 >= 0 || parentPoint.y - 1 < m_pTileMap->GetBorder().y){
		cTile* targetTile = m_pTileMap->GetTilePointer(parentPoint.x, parentPoint.y - 1);
		if (targetTile && targetTile->GetType() == cTile::eTILETYPE::TILE_BLOCK){
			if (targetTile && setTiles.find(targetTile) != setTiles.end()){
				setTiles.erase(targetTile);
			}		
			targetTile = m_pTileMap->GetTilePointer(parentPoint.x - 1, parentPoint.y - 1);
			if (targetTile && setTiles.find(targetTile) != setTiles.end()){
				setTiles.erase(targetTile);
			}
			targetTile = m_pTileMap->GetTilePointer(parentPoint.x + 1, parentPoint.y - 1);
			if (targetTile && setTiles.find(targetTile) != setTiles.end()){
				setTiles.erase(targetTile);
			}			
		}
	}
	if (parentPoint.y + 1 >= 0 || parentPoint.y + 1 < m_pTileMap->GetBorder().y){
		cTile* targetTile = m_pTileMap->GetTilePointer(parentPoint.x, parentPoint.y + 1);
		if (targetTile && targetTile->GetType() == cTile::eTILETYPE::TILE_BLOCK){
			if (targetTile && setTiles.find(targetTile) != setTiles.end()){
				setTiles.erase(targetTile);
			}
			targetTile = m_pTileMap->GetTilePointer(parentPoint.x - 1, parentPoint.y + 1);
			if (targetTile && setTiles.find(targetTile) != setTiles.end()){
				setTiles.erase(targetTile);
			}
			targetTile = m_pTileMap->GetTilePointer(parentPoint.x + 1, parentPoint.y + 1);
			if (targetTile && setTiles.find(targetTile) != setTiles.end()){
				setTiles.erase(targetTile);
			}
		}

	}
	if (parentPoint.x - 1 >= 0 || parentPoint.x - 1  < m_pTileMap->GetBorder().x){

		//m_pTileMap->GetTilePointer(parentPoint.x - 1, parentPoint.y);

		cTile* targetTile = m_pTileMap->GetTilePointer(parentPoint.x - 1, parentPoint.y);
		if (targetTile && targetTile->GetType() == cTile::eTILETYPE::TILE_BLOCK){
			if (targetTile && setTiles.find(targetTile) != setTiles.end()){
				setTiles.erase(targetTile);
			}
			targetTile = m_pTileMap->GetTilePointer(parentPoint.x - 1, parentPoint.y + 1);
			if (targetTile && setTiles.find(targetTile) != setTiles.end()){
				setTiles.erase(targetTile);
			}
			targetTile = m_pTileMap->GetTilePointer(parentPoint.x - 1, parentPoint.y - 1);
			if (targetTile && setTiles.find(targetTile) != setTiles.end()){
				setTiles.erase(targetTile);
			}
		}

	}

	if (parentPoint.x + 1 >= 0 || parentPoint.x + 1  < m_pTileMap->GetBorder().x){
		//m_pTileMap->GetTilePointer(parentPoint.x + 1, parentPoint.y);
		cTile* targetTile = m_pTileMap->GetTilePointer(parentPoint.x + 1, parentPoint.y);
		if (targetTile && targetTile->GetType() == cTile::eTILETYPE::TILE_BLOCK){
			if (targetTile && setTiles.find(targetTile) != setTiles.end()){
				setTiles.erase(targetTile);
			}
			targetTile = m_pTileMap->GetTilePointer(parentPoint.x + 1, parentPoint.y + 1);
			if (targetTile && setTiles.find(targetTile) != setTiles.end()){
				setTiles.erase(targetTile);
			}
			targetTile = m_pTileMap->GetTilePointer(parentPoint.x + 1, parentPoint.y - 1);
			if (targetTile && setTiles.find(targetTile) != setTiles.end()){
				setTiles.erase(targetTile);
			}
		}
	}

	for (auto p : setTiles){
		//m_vecOpenTiles.push_back(p);
		if (m_vecClosedTiles.find(p) == m_vecClosedTiles.end()){
			if (m_vecOpenTiles.find(p) != m_vecOpenTiles.end()){
				//p->Check()
				float checkG = from->GetFGH().m_fG
					+ sqrt((p->GetPosition().x - from->GetPosition().x) *  (p->GetPosition().x - from->GetPosition().x) +
					(p->GetPosition().y - from->GetPosition().y) *  (p->GetPosition().y - from->GetPosition().y));
				p->Check(from, checkG);
			}
			else {
				ST_FGHINFO stInfo;
				stInfo.m_fH = abs(p->GetPosition().x - m_stDestination.x) + abs(p->GetPosition().y - m_stDestination.y);
				
				stInfo.m_fG
					= from->GetFGH().m_fG
					+ sqrt((p->GetPosition().x - from->GetPosition().x) *  (p->GetPosition().x - from->GetPosition().x) +
					(p->GetPosition().y - from->GetPosition().y) *  (p->GetPosition().y - from->GetPosition().y));
				
				stInfo.m_fF = stInfo.m_fG + stInfo.m_fH;
				p->SetFGH(stInfo);
				p->SetParentPos(parentPoint);
				m_vecOpenTiles.insert(p);
				//p->SetFGH();
			}
		}
	}


	//for (size_t i = 0; i < eightWay.size(); i++p){
	//	if (eightWay[i].x < 0 || eightWay[i].x >= m_pTileMap->GetBorder().x ||
	//		eightWay[i].y < 0 || eightWay[i].y >= m_pTileMap->GetBorder().y){

	//	}
	//}

	//if (parentPoint.x + x < 0 || parentPoint.x + x >= m_pTileMap->GetBorder().x ||
	//	parentPoint.y + y < 0 || parentPoint.y + y >= m_pTileMap->GetBorder().y){
	//	continue;
	//}
}

void cAstarSP::PathToString(){
	cTile* p = m_pTileMap->GetTilePointer(m_stDestination.x, m_stDestination.y);

	std::cout << "Dest<- ";
	while (true){
		std::cout << "(" << p->GetPosition().x << "," << p->GetPosition().y << "), ";
		p = m_pTileMap->GetTilePointer(p->GetParentPosition().x, p->GetParentPosition().y);

		if (p->GetPosition().x == m_stStartTile.x &&p->GetPosition().y == m_stStartTile.y){
			break;
		}
	}

	std::cout << "(" << p->GetPosition().x << "," << p->GetPosition().y << ")<-Start" << std::endl;
}

void cAstarSP::GetPathPointVector(
	OUT std::vector<cTile*>& vecPathTiles,
	OUT std::vector<cTile*>& vecOpenTiles,
	OUT std::vector<cTile*>& vecClosedTiles){

	cTile* p = m_pTileMap->GetTilePointer(m_stDestination.x, m_stDestination.y);

	//std::cout << "Dest<- ";
	//std::cout << "(" << p->GetPosition().x << "," << p->GetPosition().y << "), ";
	//std::cout << "(" << p->GetPosition().x << "," << p->GetPosition().y << ")<-Start" << std::endl;

	while (true){
		vecPathTiles.push_back(p);
		p = m_pTileMap->GetTilePointer(p->GetParentPosition().x, p->GetParentPosition().y);
		if (p->GetPosition().x == m_stStartTile.x &&p->GetPosition().y == m_stStartTile.y){
			break;
		}
	}
	vecPathTiles.push_back(p);
	//std::reverse(vecPathTiles.begin(), vecPathTiles.end());
	
	for (auto p : m_vecClosedTiles){
		vecClosedTiles.push_back(p);
	}
	
	for (auto p : m_vecOpenTiles){
		vecOpenTiles.push_back(p);
	}
}
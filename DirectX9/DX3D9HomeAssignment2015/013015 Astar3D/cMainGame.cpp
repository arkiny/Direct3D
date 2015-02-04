#include "stdafx.h"
#include <sstream>

#include "cMainGame.h"
#include "../Common/cAxis.h"
#include "../Common/cGrid.h"

#include "cBox.h"
#include "cPlayer.h"
//#include "cCharacter.h"
#include "cCamera.h"
#include "cPlayer.h"
#include "cTileMap.h"
#include "cTile.h"
#include "cAstarSP.h"
#include "cTileMapLoader.h"

cMainGame::cMainGame() :
m_cAxis(NULL),
m_cGrid(NULL),
m_cCamera(NULL)
{
	srand(GetTickCount());
	GetCursorPos(&m_mousePos);
}

cMainGame::~cMainGame()
{
	gIOBJECT_BOX* p;
	while (!m_vecBox.empty()){
		p = (gIOBJECT_BOX*)m_vecBox.back();
		m_vecBox.pop_back();
		p->Destroy();
	}
	SAFE_DELETE(m_pPlayer);

	SAFE_DELETE(m_pTileMap);
	SAFE_RELEASE(m_pFont);
	SAFE_DELETE(m_cAxis);
	SAFE_DELETE(m_cGrid);
	SAFE_DELETE(m_cCamera);
	
	cDeviceManager* pDevice = cDeviceManager::GetInstance();
	pDevice->Destroy();
}

void cMainGame::Init(){
	m_cAxis = new cAxis(100.0f);
	m_cAxis->init();

	m_cGrid = new cGrid(100.0f, 100);
	m_cGrid->init();

	m_pPlayer = new cPlayer;
	m_pPlayer->Setup(this);

	m_cCamera = new cCamera;
	m_cCamera->Setup();
	m_cCamera->SetTarget(&m_pPlayer->GetPosition());
	
	//cTileMap a(7, 6); // height width
	//a.SetTileType(0, 3, 1);
	//a.SetTileType(1, 3, 1);
	//a.SetTileType(2, 3, 1);
	m_pTileMap = new cTileMap(16, 16);
	//m_pTileMap->SetTileType(0, 3, 1);
	//m_pTileMap->SetTileType(1, 3, 1);
	//m_pTileMap->SetTileType(2, 3, 1); 
	m_nWidth = m_pTileMap->GetBorder().x;
	m_nHeight = m_pTileMap->GetBorder().y;

	cTileMapLoader loader;
	POINT start;
	POINT dest;

	loader.LoadFromFile("data.txt", m_pTileMap, m_pTileMap->GetBorder().x, m_pTileMap->GetBorder().y, start, dest);
	cAstarSP sp(m_pTileMap, start, dest);


	sp.CalculatePath();
	//sp.PathToString();

	std::vector<cTile*> path;
	std::vector<cTile*> closed;
	std::vector<cTile*> opened;

	sp.GetPathPointVector(path, opened, closed);
	
		
	for (size_t i = 0; i < opened.size(); i++){
		m_pTileMap->SetTileType(opened[i]->GetPosition().x, opened[i]->GetPosition().y, cTile::eTILETYPE::TILE_OPENED);
	}
	for (size_t i = 0; i < closed.size(); i++){
		m_pTileMap->SetTileType(closed[i]->GetPosition().x, closed[i]->GetPosition().y, cTile::eTILETYPE::TILE_CLOSED);
	}
	for (size_t i = 0; i < path.size(); i++){
		m_pTileMap->SetTileType(path[i]->GetPosition().x, path[i]->GetPosition().y, cTile::eTILETYPE::TILE_PATH);
	}
	m_pTileMap->SetTileType(start.x, start.y, cTile::eTILETYPE::TILE_START);
	m_pTileMap->SetTileType(dest.x, dest.y, cTile::eTILETYPE::TILE_DEST);


	gIObject* _box;
	m_vecBox.resize(m_nWidth * m_nHeight);

	
	for (int i = 0; i < m_nHeight; i++){
		for (int j = 0; j < m_nWidth; j++){
			_box = new cBox;
			_box->init();
			GRIDPOSITION a = { j, 0, m_nHeight - i - 1 };
			_box->setPositionByGrid(a);
			gIOBJECT_BOX* p = (gIOBJECT_BOX*)_box;
			p->setHP(3.0f);
			p->setTile(m_pTileMap->GetTilePointer(j, i));
			m_vecBox[j +  i* m_nWidth] = _box;
		}
	}	


	D3DXCreateFont(g_pD3DDevice,     //D3D Device
		40,               //Font height
		0,                //Font width
		FW_NORMAL,        //Font Weight
		1,                //MipLevels
		false,            //Italic
		DEFAULT_CHARSET,  //CharSet
		OUT_DEFAULT_PRECIS, //OutputPrecision
		ANTIALIASED_QUALITY, //Quality
		DEFAULT_PITCH | FF_DONTCARE,//PitchAndFamily
		"Arial",          //pFacename,
		&m_pFont);         //ppFont

	SetRect(&m_recFontRect, 0, 0, 400, 200);

	//D3DXMATRIX matProj;
	//D3DVIEWPORT9 vp;
	//g_pD3DDevice->GetViewport(&vp);
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, vp.Width / (float)vp.Height, 1.0f, 1000.0f);
	//g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);


	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vDir = D3DXVECTOR3(1.5, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

gIObject* cMainGame::getBoxInfoFromGrid(int x, int z){
	if (x < m_nHeight && z < m_nWidth && x >= 0 && z >= 0){
		return m_vecBox[z + x * m_nWidth];
	}
	else {
		return NULL;
	}	
}

void cMainGame::Update(float delta){
	// random generate
	m_fAccumTime += delta;
	m_fTimeLeft -= delta;
	
	//if (m_fTimeLeft < 0.0f){
	//	std::wstringstream s;
	//	s << "Your Score is " << m_nScore;
	//	MessageBox(g_hWnd, s.str().c_str(), L"Game End", MB_OK);
	//	PostQuitMessage(NULL);
	//}
	//
	//// random generate
	//if (m_fAccumTime > 1.0f){
	//	m_fAccumTime = 0.0f;
	//	int x = rand() % 20;
	//	int z = rand() % 20; 
	//	gIOBJECT_BOX* p = (gIOBJECT_BOX*)getBoxInfoFromGrid(x, z);
	//	// prevent duplicate
	//	if (p){
	//		if (p->getHP() <= 0){
	//			p->setHP(3);
	//		}
	//	}
	//}
	//
	m_pPlayer->Update(delta);
	m_cCamera->Update();
}

void cMainGame::Render(){
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//D3DCOLOR_XRGB(47, 121, 112),
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);
	g_pD3DDevice->BeginScene();

	// 그림을 그린다.
	m_cGrid->render();
	m_cAxis->render();
	
	for (auto box : m_vecBox){
		box->render();
	}


	/*std::wstringstream s;
	s.precision(2);
	GRIDPOSITION playercord = m_pPlayer->getGridCoord();
	s << std::fixed << "x : " << playercord.x << std::endl
		<< "y : " << playercord.y << std::endl
		<< "z : " << playercord.z << std::endl
		<< "TimeLeft : " << m_fTimeLeft << std::endl
		<< "Score : " << m_nScore << std::endl;*/

	//m_pFont->DrawText(NULL,				 //pSprite
	//	s.str().c_str(),	 //pString
	//	-1,					//Count
	//	&m_recFontRect,		//pRect
	//	DT_LEFT | DT_NOCLIP,//Format,
	//	0xFFFFFFFF);		//Color

	//m_pPlayer->Render();
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	if (m_cCamera)
		m_cCamera->WndProc(hWnd, message, wParam, lParam);
}


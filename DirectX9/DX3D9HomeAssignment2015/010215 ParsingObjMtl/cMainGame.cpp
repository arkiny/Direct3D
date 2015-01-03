#include "stdafx.h"
#include <sstream>

#include "cMainGame.h"
#include "../Common/cAxis.h"
#include "../Common/cGrid.h"

#include "cBox.h"
//#include "cCharacter.h"
#include "cCamera.h"
#include "cPlayer.h"
#include "cBoxfromFile.h"
#include "cObjectFromParser.h"

cMainGame::cMainGame() :
m_cAxis(NULL),
m_cGrid(NULL),
m_cCamera(NULL),
m_pObject(NULL),
m_pObject2(NULL),
m_pObject3(NULL)/*,
m_pPlayer(NULL),
m_pBoxFile(NULL)*/
{
	srand(GetTickCount());
	GetCursorPos(&m_mousePos);
}

cMainGame::~cMainGame()
{
	//	gIObject* p;
	//while (!m_vecBox.empty()){
	//	p = m_vecBox.back();
	//	m_vecBox.pop_back();
	//	delete p;
	//}
	SAFE_RELEASE(m_pFont);
	//SAFE_DELETE(m_pBoxFile)
	//SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pObject);
	SAFE_DELETE(m_pObject2);
	SAFE_DELETE(m_pObject3);
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

//	m_pPlayer = new cPlayer;
//	m_pPlayer->Setup(this);
////	m_cCharacter->setPosition(D3DXVECTOR3(0.0, 4.5f, 0.0f));
//
//	m_pBoxFile = new cBoxfromFile;
//	m_pBoxFile->init();

	m_cCamera = new cCamera;
	m_cCamera->Setup();
	//m_cCamera->SetTarget(&m_pPlayer->GetPosition());
	
	D3DXMATRIX matS, matR, matT, matF;


	D3DXMatrixTranslation(&matT, -10.0f, 5.0, -15.0f);
	m_pObject = new cObjectFromParser;
	m_pObject->setup("../Resource/obj/box.obj");
	m_pObject->setMatrix(matT);

	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationX(&matR, D3DXToRadian(270.0f));
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, -40.0f);
	matF = matS*matR*matT;

	m_pObject2 = new cObjectFromParser;
	m_pObject2->setup("../Resource/obj/Map.obj");
	m_pObject2->setMatrix(matF);

	m_pObject3 = new cObjectFromParser;
	m_pObject3->setup("../Resource/obj/map_surface.obj");
	m_pObject3->setMatrix(matF);
	//gIObject* _box;
	//m_vecBox.resize(20 * 20);
	//for (int i = 0; i < 20; i++){
	//	for (int j = 0; j < 20; j++){
	//		_box = new cBox;
	//		_box->init();
	//		GRIDPOSITION a = { i, 0, j };
	//		_box->setPositionByGrid(a);
	//		m_vecBox[j + i * 20] = _box;
	//	}
	//}	

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
		L"Arial",          //pFacename,
		&m_pFont);         //ppFont

	SetRect(&m_recFontRect, 0, 0, 400, 200);

	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vDir = D3DXVECTOR3(1.5, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	

	//D3DXMATRIX matProj;
	//D3DVIEWPORT9 vp;
	//g_pD3DDevice->GetViewport(&vp);
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, vp.Width / (float)vp.Height, 1.0f, 1000.0f);
	//g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);

	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

//gIObject* cMainGame::getBoxInfoFromGrid(int x, int z){
//	if (x < 20 && z < 20 && x >= 0 && z >= 0){
//		return m_vecBox[z + x * 20];
//	}
//	else {
//		return NULL;
//	}	
//}

void cMainGame::Update(float delta){
	//// random generate
	//m_fAccumTime += delta;
	//m_fTimeLeft -= delta;
	//
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
	//m_pPlayer->Update(delta);
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
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_cGrid->render();
	m_cAxis->render();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_pObject->render();
	m_pObject2->render();
	m_pObject3->render();
	//for (auto box : m_vecBox){
	//	box->render();
	//}

	//m_pBoxFile->render();

	//std::wstringstream s;
	//s.precision(2);
	//GRIDPOSITION playercord = m_pPlayer->getGridCoord();
	//s << std::fixed << "x : " << playercord.x << std::endl
	//	<< "y : " << playercord.y << std::endl
	//	<< "z : " << playercord.z << std::endl
	//	<< "TimeLeft : " << m_fTimeLeft << std::endl
	//	<< "Score : " << m_nScore << std::endl;

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

//void cMainGame::CollisionCheck(cPlayer* player){
//	GRIDPOSITION playerPos = player->getGridCoord();
//	D3DXVECTOR3 fistPos = player->getFistPosition();
//
//	std::vector<gIObject*> box;
//	
//	
//	gIOBJECT_BOX* p;
//	
//	for (int i = -1; i < 2; i++){
//		p = ((gIOBJECT_BOX*)getBoxInfoFromGrid(playerPos.x + i, playerPos.z - 1));
//		if (p){
//			if (p->getHP() > 0){
//				box.push_back(p);
//			}
//		}
//
//		p = ((gIOBJECT_BOX*)getBoxInfoFromGrid(playerPos.x + i, playerPos.z));
//		if (p){
//			if (p->getHP() > 0){
//				box.push_back(p);
//			}
//		}
//
//		p = ((gIOBJECT_BOX*)getBoxInfoFromGrid(playerPos.x + i, playerPos.z + 1));
//		if (p){
//			if (p->getHP() > 0){
//				box.push_back(p);
//			}
//		}
//	}
//	
//	p = nullptr;
//
//	while (!box.empty()){
//		// collision check here
//		p = ((gIOBJECT_BOX*)box.back());
//
//		if (p->collidewithPoint(fistPos)){
//			p->getHit(1);
//			if (p->getHP() == 0){
//				m_nScore++;
//			}
//		}
//
//		box.pop_back();
//	}
//}

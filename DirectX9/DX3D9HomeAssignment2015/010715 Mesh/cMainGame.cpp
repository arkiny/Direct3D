#include "stdafx.h"
#include <sstream>

#include "cMainGame.h"
#include "../Common/cAxis.h"
#include "../Common/cGrid.h"

//#include "cBox.h"
//#include "cCharacter.h"
#include "cCamera.h"
#include "cPlayer.h"
//#include "cObjectFromParser.h"
#include "cPyramid.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "iMap.h"
#include "cCubeIndexBuffer.h"
#include "cMesh.h"

cMainGame::cMainGame() :
m_cAxis(NULL),
m_cGrid(NULL),
m_cCamera(NULL),
//m_pObject(NULL),
//m_pObject2(NULL),
//m_pObject3(NULL),
m_pPyramid(NULL),
m_pPlayer(NULL),
m_pMap(NULL),
m_pIndexBuffCube(NULL),
m_pMesh(NULL)
/*m_pBoxFile(NULL)*/
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
	SAFE_DELETE(m_pPyramid);
	//SAFE_DELETE(m_pBoxFile)
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pMesh);
	//SAFE_DELETE(m_pObject);
	//SAFE_DELETE(m_pObject2);
	//SAFE_DELETE(m_pObject3);
	SAFE_DELETE(m_pIndexBuffCube); 
	for each(auto p in m_vecGroup)
	{
		SAFE_DELETE(p);
	}

	for each(auto p in m_vecSurface)
	{
		SAFE_DELETE(p);
	}
	for each(auto p in m_vecGroupBox)
	{
		SAFE_DELETE(p);
	}

	g_pTextureManager->Destroy();

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
	

	m_cCamera = new cCamera;
	m_cCamera->Setup();
	m_cCamera->SetTarget(&m_pPlayer->GetPosition());
	
	D3DXMATRIX matS, matR, matT, matF;

	cObjLoader ObjLoader;
	std::string sFolder("../Resource/");
	sFolder += std::string("obj/");

	ObjLoader.Load(m_vecGroupBox, sFolder, std::string("box.obj"));
	ObjLoader.Load(m_vecGroup, sFolder, std::string("Map.obj"));	
	ObjLoader.Load(m_vecSurface, sFolder, std::string("map_surface.obj"));

	for each(auto p in m_vecSurface)
	{
		p->Buffering();
	}	
	for each(auto p in m_vecGroup)
	{
		p->Buffering();
	}	
	for each(auto p in m_vecGroupBox)
	{
		p->Buffering();
	}

	D3DXMATRIXA16 matWorld;
	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.f);
	matWorld = matS * matR;
	cObjMap* pMap = new cObjMap;
	pMap->Load(sFolder, std::string("map_surface.obj"), &matWorld);
	m_pMap = pMap;
	m_pPlayer->Setup(this, m_pMap);


	m_pPyramid = new cPyramid;
	m_pPyramid->setup();

	m_pIndexBuffCube = new cCubeIndexBuffer;
	m_pIndexBuffCube->init();

	m_pMesh = new cMesh;
	ObjLoader.Load(*m_pMesh->getGroup(), sFolder, std::string("map.obj"));
	m_pMesh->init();

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

	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vDir = D3DXVECTOR3(1.5, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);

}


void cMainGame::Update(float delta){
	m_pPlayer->Update(delta);
	m_cCamera->Update();
}

//bool cMainGame::moveCheck(cPlayer* player, D3DXVECTOR3& target, float& yo){
//
//	D3DXMATRIXA16 matWorld, matT, matS, matR;
//	D3DXMatrixTranslation(&matT, -5.0f, 0.0f, 5.0f);
//	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
//	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.f);
//	matWorld = matT * matS * matR;
//
//	//std::vector<cGroup*>	m_vecSurface;
//	D3DXVECTOR3 a, b, c;
//	float _dist = 2000.0f;
//	D3DXVECTOR3 playerpos = player->GetPosition();
//	D3DXVECTOR3 startingPoint = D3DXVECTOR3(target.x, _dist-playerpos.y, target.z);
//	float playerheight = playerpos.y;
//	//startingPoint.y = (1000.0f - startingPoint.y) + startingPoint.y;
//	int n = 0;
//	for (UINT i = 0; i < m_vecSurface.size(); i++){
//		std::vector<ST_PNT_VERTEX> t_vertexes = m_vecSurface[i]->m_vecVertex;
//
//		for (int k = 0; k < t_vertexes.size(); k++){
//			D3DXVec3TransformCoord(&t_vertexes[k].p, &t_vertexes[k].p, &matWorld);
//		}
//
//		for (UINT j = 0; j < m_vecSurface[i]->m_vecVertex.size(); j++){
//			a = t_vertexes[j].p;
//			j++;
//			b = t_vertexes[j].p;
//			j++;
//			c = t_vertexes[j].p;
//
//			float x, y, fDist;
//
//			if (D3DXIntersectTri(&a, &b, &c, &startingPoint, &D3DXVECTOR3(0, -1.0f, 0), &x, &y, &fDist)){
//			//	player->setPos(D3DXVECTOR3(target.x, a.y, target.z));
//								
//				//player->setPos(angle*l);
//				if (player->isJumping()){
//					yo = _dist - (fDist + (player->GetPosition().y - player->getHeight()));
//				}
//				else {
//					yo = _dist - (fDist + (player->GetPosition().y - player->getHeight()));
//				}
//				return true;
//			}
//		}
//	}
//	//n = n * 3;
//	//int k = 0;
//
//	//for (UINT i = 0; i < m_vecTest.size(); i++){
//	//	a = m_vecTest[i].p;
//	//	i++;
//	//	b = m_vecTest[i].p;
//	//	i++;
//	//	c = m_vecTest[i].p;
//
//	//	if (D3DXIntersectTri(&a, &b, &c, &startingPoint, &D3DXVECTOR3(0, -1.0f, 0), &target.x, &target.z, &_dist)){
//	//		return true;
//	//	}
//	//}
//	return false;
//}
//
//float cMainGame::heightCheck(cPlayer* player){
//	return 0.0f;
//}

void cMainGame::Render(){
	D3DXMATRIXA16 matRot, matWorld;

	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//D3DCOLOR_XRGB(47, 121, 112),
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);
	g_pD3DDevice->BeginScene();

	

	

	
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	float meshStart = (float)GetTickCount();
	for (int i = 0; i < 1000; i++){
		m_pMesh->render();
	}
	float meshEnd = (float)GetTickCount();
	float meshdiff = meshEnd - meshStart;

	float groupStart = (float)GetTickCount();
	for (int i = 0; i < 1000; i++){
		for each(auto p in m_vecGroup)
		{
			p->Render();
		}
	}
	float groupEnd = (float)GetTickCount();
	float groupdiff = groupEnd - groupStart;


	std::stringstream s;
	s.precision(2);
	s << std::fixed << "Mesh : " << meshdiff << std::endl
		<< "Group : " << groupdiff << std::endl;

	m_pFont->DrawText(NULL,				 //pSprite
		s.str().c_str(),	 //pString
		-1,					//Count
		&m_recFontRect,		//pRect
		DT_LEFT | DT_NOCLIP,//Format,
		0xFFFFFFFF);		//Color

	//if (GetKeyState(VK_TAB) & 0x8000)
	//{
	//	// 그림을 그린다.
	//	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	//	m_cGrid->render();
	//	m_cAxis->render();

	//	m_pPyramid->render();
	//	m_pPlayer->Render();

	//	m_pIndexBuffCube->render();

	//	///

	//	//D3DXMATRIXA16 matRot, matWorld;
	//	//D3DXMatrixIdentity(&matWorld);
	//	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	//	//g_pD3DDevice->SetTexture(0, NULL);
	//	//g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);

	//	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
	//	//	m_vecTest.size() / 3,
	//	//	&m_vecTest[0],
	//	//	sizeof(ST_PN_VERTEX));

	//	///

	//	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//	for each(auto p in m_vecGroupBox)
	//	{
	//		p->Render();
	//	}


	//	D3DXMATRIXA16 matT, matS, matR;
	//	D3DXMatrixTranslation(&matT, -5.0f, 0.0f, 5.0f);
	//	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	//	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.f);
	//	matWorld = matT * matS *  matR;
	//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//	for each(auto p in m_vecSurface)
	//	{
	//		p->Render();
	//	}
	//	D3DXMatrixIdentity(&matWorld);
	//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//}
	//else
	//{
	//	D3DXMATRIXA16 matT, matS, matR;
	//	D3DXMatrixTranslation(&matT, -5.0f, 0.0f, 5.0f);
	//	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	//	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.f);
	//	matWorld = matS * matR * matT;
	//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//	for each(auto p in m_vecGroup)
	//	{
	//		p->Render();
	//	}
	//	D3DXMatrixIdentity(&matWorld);
	//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//}

	

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	if (m_cCamera)
		m_cCamera->WndProc(hWnd, message, wParam, lParam);
}

#include "stdafx.h"
#include <sstream>
#include "cMainGame.h"
#include "../Common/cAxis.h"
#include "../Common/cGrid.h"
#include "cCamera.h"
#include "cPlayer.h"
#include "cPyramid.h"
#include "cCubeIndexBuffer.h"
#include "cMesh.h"
#include "cTeaPot.h"
#include "cVertexPoints.h"

cMainGame::cMainGame() :
m_cAxis(NULL),
m_cGrid(NULL),
m_cCamera(NULL),
m_pPyramid(NULL),
m_pTeapot(NULL),
m_pVertex(NULL),
m_pTeapoat2(NULL)
{
	srand(GetTickCount());
	GetCursorPos(&m_mousePos);
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pVertex);
	SAFE_DELETE(m_pTeapot);
	SAFE_DELETE(m_pPyramid);
	SAFE_DELETE(m_cAxis);
	SAFE_DELETE(m_cGrid);
	SAFE_DELETE(m_cCamera);
	SAFE_DELETE(m_pTeapoat2)

	SAFE_RELEASE(m_pFont);
	g_pTextureManager->Destroy();
	
	cDeviceManager* pDevice = cDeviceManager::GetInstance();
	pDevice->Destroy();
}

void cMainGame::Init(){
	m_cAxis = new cAxis(100.0f);
	m_cAxis->init();

	m_cGrid = new cGrid(100.0f, 100);
	m_cGrid->init();

	m_cCamera = new cCamera;
	m_cCamera->Setup();

	m_pPyramid = new cPyramid;
	m_pPyramid->setup();


	m_pVertex = new cVertexPoints;
	m_pVertex->setup();

	m_pTeapot = new cTeapot;
	m_pTeapot->setup(m_pVertex, cTeapot::eINTERPOLATIONTYPE::eBezier);
	m_pTeapot->setPos(m_pVertex->getPointAt(0));

	m_pTeapoat2 = new cTeapot;
	m_pTeapoat2->setup(m_pVertex, cTeapot::eINTERPOLATIONTYPE::eLinear);
	m_pTeapoat2->setPos(m_pVertex->getPointAt(0));

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
	m_cCamera->Update();
	m_pTeapot->update(delta);
	m_pTeapoat2->update(delta);
}

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
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_cGrid->render();
	m_cAxis->render();
	m_pPyramid->render();

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	m_pVertex->render();
	m_pTeapot->render();

	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	m_pTeapoat2->render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	if (m_cCamera)
		m_cCamera->WndProc(hWnd, message, wParam, lParam);
}

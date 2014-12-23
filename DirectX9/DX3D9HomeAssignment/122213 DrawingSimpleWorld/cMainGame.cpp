#include "stdafx.h"

#include <malloc.h>
#include "cMainGame.h"
#include "../Common/cMyCube.h"
#include "../Common/cCamera.h"

#include "cAxis.h"
#include "cGrid.h"

cMainGame::cMainGame() :
m_cAxis(NULL),
m_cCamera(NULL),
m_cCube(NULL),
m_cGrid(NULL)
{
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_cAxis);
	SAFE_DELETE(m_cCube);
	SAFE_DELETE(m_cCamera);
	SAFE_DELETE(m_cGrid)
	cDeviceManager* pDevice = cDeviceManager::GetInstance();
	pDevice->Destroy();
}

void cMainGame::setup(){
	m_cCamera = new cCamera;
	m_cCamera->init();

	m_cCube = new cMyCube(D3DXVECTOR3(0, 1, 0), 2.0f);
	m_cCube->init();

	m_cAxis = new cAxis(100.0f);
	m_cAxis->init();

	m_cGrid = new cGrid(100.0f, 100);
	m_cGrid->init();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::update(float delta){
	m_cCube->update(delta);
	m_cCamera->update(delta);
}

void cMainGame::render(){
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
	m_cCube->render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		cControl::GetInstance()->OnKeyDown(wParam);
		break;

	case WM_KEYUP:
		cControl::GetInstance()->OnKeyUP(wParam);
		break;

	case WM_LBUTTONDOWN:
		cControl::GetInstance()->OnKeyDown(wParam);
		cControl::GetInstance()->OnMouseClick(lParam);
		break;

	case WM_LBUTTONUP:
		// 이상하게 wParam에서 마우스 뗄때는 감지를 못한다.
		// 0으로 wParam값이 나옴
		cControl::GetInstance()->OnKeyUP(VK_LBUTTON);
		break;

	case WM_RBUTTONDOWN:
		cControl::GetInstance()->OnKeyDown(wParam);
		break;

	case WM_RBUTTONUP:
		cControl::GetInstance()->OnKeyUP(VK_RBUTTON);
		break;


		//case WM_LBUTTONDBLCLK:
		//	m_pControl->onKeyDown(wParam);
		//	break;

	case WM_MOUSEMOVE:
		cControl::GetInstance()->OnMouseMove(lParam);
		break;
		break;
	}
}

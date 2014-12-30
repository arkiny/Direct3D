#include "stdafx.h"
#include "cMainGame.h"
#include "../Common/cAxis.h"
#include "../Common/cGrid.h"
#include "../Common/cTracingCamera.h"
#include "cCharacter.h"

cMainGame::cMainGame() :
m_cAxis(NULL),
m_cGrid(NULL),
m_cCamera(NULL),
m_cCharacter(NULL),
m_bClicked(false)
{
	GetCursorPos(&m_mousePos);
	//m_mousePos = { 0, 0 };
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_cAxis);
	SAFE_DELETE(m_cGrid);
	SAFE_DELETE(m_cCamera);
	SAFE_DELETE(m_cCharacter);
	cDeviceManager* pDevice = cDeviceManager::GetInstance();
	pDevice->Destroy();
}

void cMainGame::Init(){

	m_cAxis = new cAxis(100.0f);
	m_cAxis->init();

	m_cGrid = new cGrid(100.0f, 100);
	m_cGrid->init();

	m_cCamera = new cTracingCamera;
	m_cCamera->init();

	m_cCharacter = new cCharacter;
	m_cCharacter->init();

	D3DXMATRIX matProj;
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, vp.Width / (float)vp.Height, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::Update(float delta){
	m_cCamera->updatePosition(m_cCharacter->getPosition());
	m_cCharacter->update(delta);
	if (GetKeyState(VK_SPACE) & 0x8000){
		//m_fAngleDegree += 10.0f * delta;
		m_cCamera->backlook(m_cCharacter->getForward());
	}
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
	m_cCharacter->render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
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

	case WM_MOUSEMOVE:{
		cControl::GetInstance()->OnMouseMove(lParam);
		int mX = LOWORD(lParam);
		int mY = HIWORD(lParam);
		if (wParam == MK_RBUTTON){
			float fDeltaX = (mX - m_mousePos.x) / 10.0f;
			float fDeltaY = -(mY - m_mousePos.y) / 10.0f;

			if (mX > m_mousePos.x){
				m_cCamera->rotateX(fDeltaX);
			}
			else if (mX < m_mousePos.x){
				m_cCamera->rotateX(fDeltaX);
			}
			else {
				// do nothing
			}
			if (mY > m_mousePos.y){
				m_cCamera->rotateY(fDeltaY);
			}
			else if (mY < m_mousePos.y){
				m_cCamera->rotateY(fDeltaY);
			}
			else {
				// do nothing
			}

		}
		m_mousePos = { mX, mY };
		break;
	}
	case WM_MOUSEWHEEL:
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0){
			// wheel up
			m_cCamera->moveforward(-5.0f);
		}
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0){
			// wheel down
			m_cCamera->moveforward(5.0f);
		}
		break;
	}
}
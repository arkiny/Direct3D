#include "StdAfx.h"
#include "cMainGame.h"
#include "cMyCube.h"
#include "cCamera.h"
cMainGame::cMainGame(void)
{
	m_cCube = NULL;
	m_cCube2 = NULL;
	m_cCamera = NULL;
}


cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_cCube);
	SAFE_DELETE(m_cCube2);
	SAFE_DELETE(m_cCamera);
	cDeviceManager* pDevice = cDeviceManager::GetInstance();
	pDevice->Destroy();
}

void cMainGame::Setup()
{
	m_cCube = new cMyCube(D3DXVECTOR3(0, 0, 0), 2.0f);
	m_cCube->init();

	m_cCube2 = new cMyCube(D3DXVECTOR3(0, -3.0, 0), 4.0f);
	m_cCube2->init();

	m_cCamera = new cCamera;
	m_cCamera->init();

	/*D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	D3DXVECTOR3 vEye(-10, 10, -10), vLookAt(0, 0, 0), vUp(0, 100, 0);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, vp.Width / (float)vp.Height, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);*/

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}


void cMainGame::Update(float delta)
{
	m_cCamera->update(delta);
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//D3DCOLOR_XRGB(47, 121, 112),
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);
	g_pD3DDevice->BeginScene();

	// 그림을 그린다.

	//m_pCircle1->Render();
	m_cCube->render();
	m_cCube2->render();

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

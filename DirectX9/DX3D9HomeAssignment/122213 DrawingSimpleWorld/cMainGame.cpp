#include "stdafx.h"
#include "cMainGame.h"
#include "../Common/cMyCube.h"
#include "../Common/cCamera.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{

}

void cMainGame::setup(){
	m_cCube = new cMyCube(D3DXVECTOR3(0,0,0), 2.0f);
	m_cCube->init();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::update(float delta){
	m_cCube->update(delta);
}

void cMainGame::render(){
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//D3DCOLOR_XRGB(47, 121, 112),
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);
	g_pD3DDevice->BeginScene();
	
	// �׸��� �׸���.
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
		// �̻��ϰ� wParam���� ���콺 ������ ������ ���Ѵ�.
		// 0���� wParam���� ����
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

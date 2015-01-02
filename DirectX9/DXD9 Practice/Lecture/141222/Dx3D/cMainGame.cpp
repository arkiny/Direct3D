#include "StdAfx.h"
#include "cMainGame.h"
#include "cCircleRHW.h"

cMainGame::cMainGame(void)
	: m_pCircle1(NULL)
{
}


cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCircle1);
	cDeviceManager* pDevice = cDeviceManager::GetInstance();
	pDevice->Destroy();
}

void cMainGame::Setup()
{
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	m_pCircle1 = new cCircleRHW;
	m_pCircle1->Setup(D3DXVECTOR2(vp.Width / 2, vp.Height / 2), 200);


	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 1, 0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(1, 0, 0);
	m_vecVertex.push_back(v);

	D3DXVECTOR3 vEye(0, 1, -4), vLookAt(0, 1, 0), vUp(0, 1, 0);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, vp.Width / (float)vp.Height, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}


void cMainGame::Update()
{

}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//D3DCOLOR_XRGB(47, 121, 112),
		D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);
	g_pD3DDevice->BeginScene();

	// 그림을 그린다.
	
	//m_pCircle1->Render();
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			int nX = LOWORD(lParam);
			int nY = HIWORD(lParam);
			m_pCircle1->SetCenter(D3DXVECTOR2(nX, nY));
		}
		
		break;
	}
}

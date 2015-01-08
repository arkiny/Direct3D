#include "StdAfx.h"
#include "cCamera.h"


cCamera::cCamera(void)
	: m_vEye(0, 0, -10)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_fAngleX(0.0f)
	, m_fAngleY(0.0f)
	, m_isLButtonDown(false)
	, m_pvTarget(NULL)
	, m_fDist(10.0f)
{
}


cCamera::~cCamera(void)
{
}

void cCamera::Setup()
{
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, vp.Width / (float)vp.Height, 1.0f, 10000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update()
{
	m_vEye = D3DXVECTOR3(0, 0, -m_fDist);

	D3DXMATRIXA16 matRotX, matRotY;
	D3DXMatrixRotationX(&matRotX, m_fAngleX);
	D3DXMatrixRotationY(&matRotY, m_fAngleY);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matRotX);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matRotY);
	if(m_pvTarget)
	{
		m_vEye += (*m_pvTarget);
		m_vLookAt = (*m_pvTarget);
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			m_ptPrevMouse.x = LOWORD(lParam);
			m_ptPrevMouse.y = HIWORD(lParam);
			m_isLButtonDown = true;
		}
		break;
	case WM_LBUTTONUP:
		{
			m_isLButtonDown = false;
		}
		break;
	case WM_MOUSEMOVE:
		{
			if(m_isLButtonDown)
			{
				POINT ptCurrMouse;
				ptCurrMouse.x = LOWORD(lParam);
				ptCurrMouse.y = HIWORD(lParam);
				
				float fDeltaX = (ptCurrMouse.x - m_ptPrevMouse.x) / 100.f;
				float fDeltaY = (ptCurrMouse.y - m_ptPrevMouse.y) / 100.f;
				
				m_fAngleX += fDeltaY;
				m_fAngleY += fDeltaX;

				if(m_fAngleX >= D3DX_PI / 2.f - 0.0001f)
					m_fAngleX = D3DX_PI / 2.f - 0.0001f;

				if(m_fAngleX <= -D3DX_PI / 2.f + 0.0001f)
					m_fAngleX = -D3DX_PI / 2.f + 0.0001f;

				m_ptPrevMouse = ptCurrMouse; 
			}
		}
		break;
	case WM_MOUSEWHEEL:
		{
			m_fDist -= GET_WHEEL_DELTA_WPARAM(wParam) / 100.f;
			if(m_fDist < 0.1f)
				m_fDist = 0.1f;
		}
		break;
	}
}

void cCamera::SetTarget( D3DXVECTOR3* pvTarget )
{
	m_pvTarget = pvTarget;
}

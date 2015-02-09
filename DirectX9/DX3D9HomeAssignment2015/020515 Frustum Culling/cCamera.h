#pragma once
class cCamera
{
private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;

	POINT			m_ptPrevMouse;
	bool			m_isRButtonDown;
	float			m_fAngleX;
	float			m_fAngleY;
	D3DXVECTOR3*	m_pvTarget;
	float			m_fDist;

public:
	cCamera(void);
	~cCamera(void);

	void Setup();
	void Update(float delta);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetTarget(D3DXVECTOR3* pvTarget);
	D3DXMATRIXA16& GetTransformMatrix();
};


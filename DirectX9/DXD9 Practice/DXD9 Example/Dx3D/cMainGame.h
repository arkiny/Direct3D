#pragma once
class cMainGame
{
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	g_pD3DDevice;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
};


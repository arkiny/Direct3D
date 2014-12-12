#pragma once
class cMainGAme
{
public:
	cMainGAme();
	~cMainGAme();
	void init();
	void update();
	void render();
private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 g_pD3DDevice;
};


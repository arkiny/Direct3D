#pragma once
class cCubeIndexBuffer
{
private:
	D3DXVECTOR3					m_vPosition;
	IDirect3DVertexBuffer9*		m_pVertexBuffer;
	IDirect3DIndexBuffer9*		m_pIndexBuffer;
	int							m_nNumTri;
	float						m_fSize;

public:
	cCubeIndexBuffer();
	~cCubeIndexBuffer();

	void init();
	void update(float delta);
	void render();
};


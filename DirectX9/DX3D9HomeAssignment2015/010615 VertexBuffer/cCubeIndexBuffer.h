#pragma once
class cCubeIndexBuffer
{
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXVECTOR3					m_vPosition;
	IDirect3DVertexBuffer9*		m_pVertexBuffer;
	IDirect3DIndexBuffer9*		m_pIndexBuffer;
	float						m_fSize;

public:
	cCubeIndexBuffer();
	~cCubeIndexBuffer();

	void init();
	void update(float delta);
	void render();
};


#pragma once
class cPyramid
{
public:
	cPyramid();
	~cPyramid();

	void setup();
	void render();

private:
	IDirect3DVertexBuffer9*		m_pVertexBufferY;

	D3DMATERIAL9				m_stMaterialLineX;
	D3DMATERIAL9				m_stMaterialLineY;
	D3DMATERIAL9				m_stMaterialLineZ;

	std::vector<ST_PN_VERTEX>	m_vecVertexLineYPyramid;
	float						m_fEdgeLength;
};


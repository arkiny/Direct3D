#pragma once

class cIndexCube
{
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	int						m_nNumTri;
	int						m_nNumVertex;
public:
	cIndexCube(void);
	~cIndexCube(void);

	void Setup();
	void Render();
};


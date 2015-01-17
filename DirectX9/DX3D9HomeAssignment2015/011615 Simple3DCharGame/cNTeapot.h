#pragma once

class cAction;
class cNTeapot : public cGameObject
{
protected:
	LPD3DXMESH					m_pMesh;
	D3DMATERIAL9				m_stMtl;

public:
	cNTeapot();
	~cNTeapot();
	void Setup(D3DXCOLOR c);
	void Render();	
};


#pragma once

class cMtlTex;
class cZealot
{
private:
	D3DXFRAME* m_pFrame;
	D3DXVECTOR3 m_vPosition;
	LPD3DXMESH m_pMesh;
	cMtlTex* m_pMtlTex;

public:
	cZealot();
	~cZealot();

	void Setup();
	void Update(float delta);
	//void CalculateWorldTM(D3DXMATRIXA16* pParent, D3DXFRAME_DR* pFrameDR);
	void Render();
	void RenderingAllFrame(D3DXMATRIXA16* pParentWorldTM, D3DXFRAME* frame);
};


#pragma once

class cAPoint : public cGameObject
{
protected:
	LPD3DXMESH		m_pMesh;
	D3DMATERIAL9	m_stMtl;
	int				m_nPointInfo;

	D3DMATERIAL9	m_stFMtl;
	LPD3DXMESH		m_p3DFont;
	
public:
	cAPoint();
	virtual ~cAPoint();
	
	void Setup	(D3DXCOLOR& c, D3DXVECTOR3& pos);
	void Update	(float delta);
	void Render	();
	void SetPointInfo(int n);
};


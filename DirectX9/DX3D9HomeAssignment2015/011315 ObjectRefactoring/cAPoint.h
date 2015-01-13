#pragma once
class cAPoint : public cGameObject
{
protected:
	LPD3DXMESH		m_pMesh;
	D3DMATERIAL9	m_stMtl;
	
public:
	cAPoint();
	virtual ~cAPoint();
	
	void Setup	(D3DXCOLOR& c, D3DXVECTOR3& pos);
	void Update	(float delta);
	void Render	();
};


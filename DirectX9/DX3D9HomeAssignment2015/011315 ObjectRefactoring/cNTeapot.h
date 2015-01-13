#pragma once

class cAction;
class cNTeapot : public cGameObject
{
protected:
	LPD3DXMESH					m_pMesh;
	D3DMATERIAL9				m_stMtl;
	cAction*					m_pCurrAction;
	std::vector<D3DXVECTOR3>	m_vecTargetList;
	int							m_nCurrentIndex = 0;
	int							m_nTargetIndex = 1;

public:
	cNTeapot();
	virtual ~cNTeapot();
	void Setup(D3DXCOLOR c);

	void SetTargetList(const std::vector<D3DXVECTOR3>& vecP);	
	void SetNextTarget();

	void Update(float delta);
	void Render();	
};


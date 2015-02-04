#pragma once
class cSphere : public cGameObject
{
private:
	LPD3DXMESH		m_pMesh;
	D3DMATERIAL9	m_stMaterialNoneSelected;
	D3DMATERIAL9	m_stMaterialSelected;
	float			m_fRadius;
	bool			m_bSelected = false;

public:
	cSphere();
	virtual ~cSphere();

	virtual void Setup();
	virtual void Render();
	
	// Getter
	float GetRadius()			{ return m_fRadius; }

	// Setter
	void SetRadius(float fRad)	{ m_fRadius = fRad; }
	void SetSelcted(bool in)	{ m_bSelected = in; }
};


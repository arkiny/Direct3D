#pragma once
class cCube
{
private:
	std::vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DXMATRIXA16				m_matPrevT;
	D3DXMATRIXA16				m_matRot;
	D3DXMATRIXA16				m_matPostT;
	D3DXMATRIXA16				m_matWorldTM;
	float						m_fAngle;
	float						m_fAngleSpeed;
	std::vector<cCube*>			m_vecChildren;

public:
	cCube(void);
	~cCube(void);
	void Setup(float fWidth, float fHeight, float fDepth);
	void Update(D3DXMATRIXA16* pmatParentWorld = NULL);
	void Render();
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetTransform(D3DXMATRIXA16& matPrevT, D3DXMATRIXA16& matPostT);
	void AddChild(cCube* pChild);
	void Destroy();
	void SetAngleSpeed(float fSpeed)
	{
		m_fAngleSpeed = fSpeed;
	}
	void SetForcedAngle(float fAngle);

};


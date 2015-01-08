#pragma once

class cMtlTex;

class cGroup
{
private:
	cMtlTex*				m_pMtlTex;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	int						m_nNumTri;
public:
	//std::vector<ST_PNT_VERTEX> m_vecVertex;

public:
	cGroup(void);
	~cGroup(void);
	void SetMtlTex(cMtlTex* pMtlTex);
	void Render();
	void BuildVB(std::vector<ST_PNT_VERTEX>& vecVertex);

};


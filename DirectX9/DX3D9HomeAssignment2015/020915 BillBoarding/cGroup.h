#pragma once
class cMtlTex;

class cGroup
{
private:
	cMtlTex*					m_pMtlTex;
	IDirect3DVertexBuffer9*		m_pVertexBuffer;

public:
	std::vector<ST_PNT_VERTEX> m_vecVertex;

public:
	cGroup(void);
	~cGroup(void);
	void SetMtlTex(cMtlTex* pMtlTex);
	void Buffering();
	void Render();

	cMtlTex* GetMtlTex() { if (m_pMtlTex) return m_pMtlTex; return NULL; }
};
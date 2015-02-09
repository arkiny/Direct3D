#pragma once

class cMtlTex;

__declspec(align(16)) class cFrame : public cObject
{
	friend class cAseLoader;
private:
	std::string					m_sNodeName;
	std::string					m_sParentName;

	std::vector<ST_POS_SAMPLE>	m_vecPosTrack;
	std::vector<ST_ROT_SAMPLE>	m_vecRotTrack;

	std::vector<cFrame*>		m_vecChildren;
	std::vector<int>			m_vecFrame;

	D3DXMATRIXA16				m_matLocalTM;
	D3DXMATRIXA16				m_matWorldTM;
	LPD3DXMESH					m_pMesh;
	cMtlTex*					m_pMtlTex;

	float						m_fTotalAccum = 0.0f;
	
	float						m_fTransAccum = 0.0f;
	float						m_fRotAccum = 0.0f;
	float						m_fTRotAccum = 0.0f;
	int							m_nTrsIndex = 0;
	int							m_nRotIndex = 0;
	int							m_nTRotIndex = 0;
public:
	cFrame(void);
	~cFrame(void);

	// override keyword new
	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

		void operator delete(void* p)
	{
		_mm_free(p);
	}

	void AddChild(cFrame* pChild);
	void CalcLocalTM(D3DXMATRIXA16* pParent);
	void BuidlMesh(std::vector<ST_PNT_VERTEX>& vecVertex);
	void SetMtlTex(cMtlTex* pMtlTex);
	void Update(D3DXMATRIXA16* pmatParent, int nKey);
	void Render();
	void Destroy();

	void GetRotationMatrixFromAnimation(OUT D3DXMATRIXA16& mat, IN int nKey);
	void GetTranslationMatrixFromAnimation(OUT D3DXMATRIXA16& mat, IN int nKey);
};


#pragma once

class cMtlTex;

__declspec(align(16)) class cFrame
{
	friend class cAseLoader;
private:
	std::string					m_sNodeName;
	std::string					m_sParentName;

	stAseTrackAni				m_stNodeAni;
	std::vector<D3DXQUATERNION>	m_vecAccumRotQuat;

	std::vector<cFrame*>		m_vecChildren;
	D3DXMATRIXA16				m_matLocalTM;
	D3DXMATRIXA16				m_matWorldTM;
	LPD3DXMESH					m_pMesh;
	cMtlTex*					m_pMtlTex;
	
	float						m_fTransAccum = 0.0f;
	float						m_fRotAccum = 0.0f;
	int							m_nTrsIndex = 0;
	int							m_nRotIndex = 0;
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
	void Update(D3DXMATRIXA16* pmatParent, float delta);
	void Render();
	void Destroy();

	void CalcAccumRotTracks();

	void GetRotationMatrixFromAnimation(float delta, OUT D3DXMATRIXA16& mat);
	void GetTranslationMatrixFromAnimation(float delta, OUT D3DXMATRIXA16& mat);
	
};


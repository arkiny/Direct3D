#pragma once
class cMtlTex;

__declspec(align(16)) class cASEObject
{
private:
	std::vector<cASEObject*>	m_vecChilds;
	LPD3DXMESH					m_pMesh;
	LPD3DXMESH					m_pNodeMesh;

	D3DXMATRIXA16				m_matLocalMat;
	D3DXMATRIXA16				m_matWorldTM;

	D3DXMATRIXA16				m_matRot;
	D3DXMATRIXA16				m_matPostT;
	
	D3DXMATRIXA16				m_matOriginalWorld;
	float						m_fAngle;
	float						m_fXAngle;
	float						m_fAngleSpeed;

	stASENode					m_stNodeInfo;

	int nFrameR = 0;
	int nFrameUnitR = 1;
	int nFrameT = 0;
	int nFrameUnitT = 1;

public:
	cASEObject();
	~cASEObject();	

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

		void operator delete(void* p)
	{
		_mm_free(p);
	}

	std::string getParentName(){
		return m_stNodeInfo.NodeParent;
	}

	std::string getNodeName(){
		return m_stNodeInfo.NodeName;
	}

	void setup(stASENode& nodeinfo, D3DXMATRIXA16* pmatParentWorld = NULL);
	
	void update(float delta, D3DXMATRIXA16* pmatParentWorld = NULL);

	void render(std::vector<cMtlTex*>& m_vecMtl);

	void AddChild(cASEObject* pObj);

	void destroy();

	stASENode& getNodeInfo(){ return m_stNodeInfo; }
};


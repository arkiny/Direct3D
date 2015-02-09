#pragma once
class cGroup;
class cMtlTex;

class cMesh
{
public:
	cMesh();
	~cMesh();
	void init();
	void render();

	std::vector<cGroup*>* getGroup(){ return &m_vecGroup; }

private:
	std::vector<cGroup*>	m_vecGroup;
	LPD3DXMESH				m_pMesh;
	std::map<int, cMtlTex*> m_mapMtlData;
};


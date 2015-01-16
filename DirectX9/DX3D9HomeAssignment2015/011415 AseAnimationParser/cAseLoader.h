#pragma once

class cFrame;
class cMtlTex;

class cAseLoader
{
private:
	FILE*		m_fp;
	char		m_szToken[1024];
	cFrame*		m_pRootFrame;
	std::string	m_sFolder;
	stSceneInfo s;

	std::vector<cMtlTex*>			m_vecMtlTex;
	std::map<std::string, cFrame*>	m_mapFrame;
	
public:
	cAseLoader(void);
	~cAseLoader(void);

	cFrame* Load(std::string& sFolder, std::string& sFileName);

private:
	char*	GetToken();
	bool	IsWhite(char c);
	bool	IsEqual(char* szStr1, char* szStr2);
	int		GetInteger();
	float	GetFloat();
	void	SkipBlock();

	void	ProcessScene(stSceneInfo& s);

	void	ProcessMaterialList();
	void	ProcessMaterial(cMtlTex* pMtlTex);
	void	ProcessMapDiffuse(cMtlTex* pMtlTex);
	cFrame*	ProcessGeomObject();
	void	ProcessNodeTM(cFrame* pFrame);
	void	ProcessMesh(cFrame* pFrame);
	void	ProcessMeshVertexList(std::vector<D3DXVECTOR3>& vecV);
	void	ProcessMeshFaceList(OUT std::vector<ST_PNT_VERTEX>& vecVertex, IN std::vector<D3DXVECTOR3>& vecV);
	void	ProcessMeshTVertList(std::vector<D3DXVECTOR2>& vecVT);
	void	ProcessMeshTFaceList(OUT std::vector<ST_PNT_VERTEX>& vecVertex, IN std::vector<D3DXVECTOR2>& vecVT);
	void	ProcessMeshNormals(OUT std::vector<ST_PNT_VERTEX>& vecVertex);

	void	ProcessTMAnimation(IN OUT stAseTrackAni& stTrack);
	void	ProcessPosTrack(IN OUT stAseTrackAni& stTrack);
	void	ProcessRotTrack(IN OUT stAseTrackAni& stTrack);
	void	ProcessTCBRotTrack(IN OUT stAseTrackAni& stTrack);
};


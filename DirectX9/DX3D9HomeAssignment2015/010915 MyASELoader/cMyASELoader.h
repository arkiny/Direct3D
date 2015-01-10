#pragma once

class cMtlTex;

class cMyASELoader
{
private:
	char m_szToken[1024];
	FILE* m_fp;

private:
	bool isWhite(char c){
		return c < 33;
	}
	
	bool isEqual(char* szStr1, char* szStr2){
		return strcmp(szStr1, szStr2) == 0;
	}
	
	float GetFloat(){
		return (float)atof(GetToken());
	}

	int GetInteger(){
		return atoi(GetToken());
	}

	void SkipBlock();
	char* GetToken();

	void ParseBlockMaterialList();

	void ParseBlockMaterial(cMtlTex* pMtlTex);
	void ParseMapDiffuse(cMtlTex* pMtlTex);
	void ParseGeometry(stASENode& node);
	void ParseMesh(stASENode& node);

	// animation
	void ParseScene();
	void ParseTMAnimation(OUT stAseTrackAni& stAseT);
	void ParsePosTrack(OUT stAseTrack& stAseT);
	void ParseRotTrack(OUT stAseTrackAni& stAseT);
	void ParseSclTrack(OUT stAseTrack& stAseT);

	void ParseVertexList(std::vector<D3DXVECTOR3>& vec);
	void ParseFaceList(std::vector<D3DXVECTOR3>& vec, std::vector<ST_PNT_VERTEX>& vecPNT);
	void ParseTVertList(std::vector<D3DXVECTOR2>& vec);
	void ParseTFaceList(std::vector<D3DXVECTOR2>& vec, std::vector<ST_PNT_VERTEX>& vecPNT);
	
	void ParseNormals(std::vector<ST_PNT_VERTEX>& vecPNT);
	void ParseNodeTM(D3DXMATRIXA16& mat);

	//Data
	std::vector<cMtlTex*>					m_vecMtl;
	std::vector<stASENode>					m_vecASENode;
	std::vector<LPD3DXMESH>					m_vecMeshs;
	std::vector<int>						m_vecsubSet;
	stSceneInfo								m_stSceneInfo;

	bool m_bLoaded = false;
	bool m_bMeshed = false;

public:
	cMyASELoader();
	~cMyASELoader();
	
	std::vector<cMtlTex*> getMtlTex(){ return m_vecMtl; }
	std::vector<stASENode>& getASENodeList(){ return m_vecASENode; }
	void Load(std::string& folderName, std::string& fileName);
	void LoadMesh();
	void Render();
};


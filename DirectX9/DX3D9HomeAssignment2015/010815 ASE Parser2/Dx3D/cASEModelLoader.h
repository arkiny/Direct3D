#pragma once
#include <sstream>
#include <fstream>
struct stMeshInfo{
	std::vector<ST_PNT_VERTEX>	vecVertex;
	int ref = INT_MAX;
};

class cMtlTex;
class cASEModelLoader
{
public:
	cASEModelLoader();
	~cASEModelLoader();

	void LoadMesh(std::string& sFolder);
	std::vector<LPD3DXMESH>& getMeshes() { return vecMeshs; }
	std::vector<cMtlTex*>& getMtlTex() { return m_vecMtlTex; }
	std::vector<stMeshInfo*>& getMeshInfo() { return vecMeshInfo; }
private:
	std::stringstream m_ssBuf;
	std::vector<cMtlTex*> m_vecMtlTex;

	void SkipUntilTokenEnd(std::fstream& file);
	void ASE_MaterialList(std::fstream& file);
	cMtlTex* ASE_Material(std::fstream& file);
	void ASE_GEOMOBJECT(std::fstream& file);

	std::vector<LPD3DXMESH>		vecMeshs;
	std::vector<stMeshInfo*>	vecMeshInfo;
	std::vector<DWORD>			vecAttrID;
};


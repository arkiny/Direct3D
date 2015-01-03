#pragma once


struct obj_t{
	std::vector<D3DXVECTOR3> m_vecPoint;
	std::vector<D3DXVECTOR2> m_vecTexture;
	std::vector<D3DXVECTOR3> m_vecNormal;
	// per-mesh material ID
	std::vector<int>            material_ids;
	// face
	std::vector<unsigned int>   indices;
};

struct mtl_t{
	std::string mtlName;
	D3DMATERIAL9 stMTL;
	std::string fileName;
};

struct FiNalObjectInfo{
	std::vector<ST_PNT_VERTEX> m_vecVertex;
	D3DMATERIAL9 stMTL;
	std::string fileName;	
};

class cObjectParser
{
public:
	cObjectParser(const char* fileName = NULL);
	~cObjectParser();

	void LoadAndParse();
	void LoadMaterial(const char* fileName = NULL);

	std::vector<ST_PNT_VERTEX>& getObjectInfo(){
		return m_objectInfo[0].m_vecVertex;
	}

	LPDIRECT3DTEXTURE9 getTexture(){
		return m_mapTextureList.at(m_objectInfo[0].fileName);
	}

	D3DMATERIAL9& getMTL(){
		return m_objectInfo[0].stMTL;
	}

	std::vector<FiNalObjectInfo>& getObjectsInfo(){
		return m_objectInfo;
	}

	LPDIRECT3DTEXTURE9 getTexture(std::string fileName){
		return m_mapTextureList.at(fileName);
	}
	
private:
	std::string m_sFileName;
	obj_t m_stObjectInfo;

	D3DMATERIAL9 stMTL;

	std::vector<FiNalObjectInfo> m_objectInfo;

	std::vector<ST_PNT_VERTEX> m_vecVertex;
	std::map<std::string, mtl_t> m_mtlInfo;
	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTextureList;
};


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


class cObjectParser
{
public:
	cObjectParser(const char* fileName = NULL);
	~cObjectParser();
	void LoadAndParse();

private:
	std::string m_sFileName;
	std::string m_sMtlPath;
	obj_t m_stObjectInfo;

	std::vector<ST_PNT_VERTEX> m_vecVertex;
};


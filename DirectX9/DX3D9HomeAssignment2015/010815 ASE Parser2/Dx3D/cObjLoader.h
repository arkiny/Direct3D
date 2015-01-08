#pragma once

class cMtlTex;
class cGroup;

class cObjLoader
{
private:
	std::map<std::string, cMtlTex*> m_mapMtlTex;

public:
	cObjLoader(void);
	~cObjLoader(void);
	void Load(std::vector<cGroup*>& vecGroup, std::string& sFolder, std::string& sFileName);
	void LoadMtlLib(std::string& sFolder, std::string& sFileName);
	LPD3DXMESH LoadMesh(std::vector<cMtlTex*>& vecMtlTex, std::string& sFolder, std::string& sFileName);
};


#pragma once

class cMtlTex;
class cGroup;

class cObjLoader
{
private:
	std::map<std::string, cMtlTex*> m_mapMtlTex;

public:
	cObjLoader();
	~cObjLoader();
	void Load(std::vector<cGroup*>& vecGroup, std::string& sFolder, std::string& sFileName);
	void LoadMtlLib(std::string& sFolder, std::string& sFileName);
};


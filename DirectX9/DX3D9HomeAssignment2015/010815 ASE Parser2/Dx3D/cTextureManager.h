#pragma once

#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
	SINGLETONE(cTextureManager);
private:
	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;

public:
	LPDIRECT3DTEXTURE9 GetTexture(std::string sPath);
	LPDIRECT3DTEXTURE9 GetTexture(char* szPath);
	void Destroy();
};


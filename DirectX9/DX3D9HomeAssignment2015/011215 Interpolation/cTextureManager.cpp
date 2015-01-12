#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager(void)
{
}


cTextureManager::~cTextureManager(void)
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string sPath)
{
	if (m_mapTexture.find(sPath) == m_mapTexture.end())
	{
		HRESULT hr;
		hr = D3DXCreateTextureFromFile(g_pD3DDevice, sPath.c_str(), &m_mapTexture[sPath]);
#ifdef _DEBUG
		_ASSERT(hr == S_OK && "Texture Creating Error");
#endif
	}
	return m_mapTexture[sPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char* szPath)
{
	return GetTexture(std::string(szPath));
}

void cTextureManager::Destroy()
{
	for each (auto p in m_mapTexture)
	{
		SAFE_RELEASE(p.second);
	}
}

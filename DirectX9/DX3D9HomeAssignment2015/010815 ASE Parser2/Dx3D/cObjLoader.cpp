#include "StdAfx.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cGroup.h"
cObjLoader::cObjLoader(void)
{
}


cObjLoader::~cObjLoader(void)
{
}

void cObjLoader::Load( std::vector<cGroup*>& vecGroup, std::string& sFolder, std::string& sFileName )
{
	m_mapMtlTex.clear();

	FILE* fp;
	fopen_s(&fp, (sFolder + sFileName).c_str(), "r");
	
	std::vector<D3DXVECTOR3> vecV;
	std::vector<D3DXVECTOR2> vecVT;
	std::vector<D3DXVECTOR3> vecVN;
	std::string sMtlName;
	std::vector<ST_PNT_VERTEX> vecVertex;
	
	while(!feof(fp))
	{
		char szLineBuf[1024] = {0,};
		fgets(szLineBuf, 1024, fp);
		//OutputDebugString(szLineBuf);
		if(strlen(szLineBuf) == 0)
			continue;
		if(szLineBuf[0] == '#')
			continue;
		else if(szLineBuf[0] == 'm')
		{
			char szMtlLibFile[1024];
			sscanf(szLineBuf, "%*s %s", szMtlLibFile);
			LoadMtlLib(sFolder, std::string(szMtlLibFile));
		}
		else if(szLineBuf[0] == 'g')
		{
			if(!vecVertex.empty())
			{
				cGroup* pGroup = new cGroup;
				pGroup->BuildVB(vecVertex);
				pGroup->SetMtlTex(m_mapMtlTex[sMtlName]);
				vecGroup.push_back(pGroup);
				vecVertex.clear();
			}	
		}
		else if(szLineBuf[0] == 'v')
		{
			if(szLineBuf[1] == ' ')
			{
				float x, y, z;
				sscanf(szLineBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if(szLineBuf[1] == 't')
			{
				float u, v;
				sscanf(szLineBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if(szLineBuf[1] == 'n')
			{
				float x, y, z;
				sscanf(szLineBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if(szLineBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf(szLineBuf, "%*s %s", szMtlName);
			sMtlName = std::string(szMtlName);
		}
		else if(szLineBuf[0] == 'f')
		{
			int aIndex[3][3];
			sscanf(szLineBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2], 
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2], 
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);
			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];
				vecVertex.push_back(v);
			}
		}
	}
	
	for each(auto p in m_mapMtlTex)
	{
		SAFE_RELEASE(p.second);
	}
	fclose(fp);
}

void cObjLoader::LoadMtlLib( std::string& sFolder, std::string& sFileName )
{
	FILE* fp;
	fopen_s(&fp, (sFolder + sFileName).c_str(), "r");
	std::string sMtlName;
	int nAttrID = 0;
	while(!feof(fp))
	{
		char szLineBuf[1024] = {0,};
		fgets(szLineBuf, 1024, fp);

		if(strlen(szLineBuf) == 0)
			continue;

		if(szLineBuf[0] == '#')
			continue;
		else if(szLineBuf[0] == 'n')
		{
			char szMtlName[1024];
			sscanf(szLineBuf, "%*s %s", szMtlName);
			sMtlName = std::string(szMtlName);
			m_mapMtlTex[sMtlName] = new cMtlTex;
			m_mapMtlTex[sMtlName]->m_nAttrId = nAttrID++;
		}
		else if(szLineBuf[0] == 'K')
		{
			if(szLineBuf[1] == 'a')
			{
				float r, g, b;
				sscanf(szLineBuf, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->stMtl.Ambient.r = r;
				m_mapMtlTex[sMtlName]->stMtl.Ambient.g = g;
				m_mapMtlTex[sMtlName]->stMtl.Ambient.b = b;
				m_mapMtlTex[sMtlName]->stMtl.Ambient.a = 1.0f;
			}
			else if(szLineBuf[1] == 'd')
			{
				float r, g, b;
				sscanf(szLineBuf, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->stMtl.Diffuse.r = r;
				m_mapMtlTex[sMtlName]->stMtl.Diffuse.g = g;
				m_mapMtlTex[sMtlName]->stMtl.Diffuse.b = b;
				m_mapMtlTex[sMtlName]->stMtl.Diffuse.a = 1.0f;
			}
			else if(szLineBuf[1] == 's')
			{
				float r, g, b;
				sscanf(szLineBuf, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->stMtl.Specular.r = r;
				m_mapMtlTex[sMtlName]->stMtl.Specular.g = g;
				m_mapMtlTex[sMtlName]->stMtl.Specular.b = b;
				m_mapMtlTex[sMtlName]->stMtl.Specular.a = 1.0f;
			}
		}
		else if(szLineBuf[0] == 'm')
		{
			char szTexture[1024];
			sscanf(szLineBuf, "%*s %s", szTexture);
			std::string sFileName(szTexture);

			m_mapMtlTex[sMtlName]->pTex = g_pTextureManager->GetTexture(sFolder + szTexture);
		}
	}

	fclose(fp);
}

LPD3DXMESH cObjLoader::LoadMesh( std::vector<cMtlTex*>& vecMtlTex, std::string& sFolder, std::string& sFileName )
{
	m_mapMtlTex.clear();
	std::string sMtlName;

	FILE* fp;
	fopen_s(&fp, (sFolder + sFileName).c_str(), "r");

	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<D3DXVECTOR3>	vecVN;
	std::vector<ST_PNT_VERTEX>	vecVertex;
	std::vector<ST_PNT_VERTEX>	vecAllVertex;
	std::vector<DWORD>			vecAttrID;

	while(!feof(fp))
	{
		char szLineBuf[1024] = {0,};
		fgets(szLineBuf, 1024, fp);
		//OutputDebugString(szLineBuf);
		if(strlen(szLineBuf) == 0)
			continue;
		if(szLineBuf[0] == '#')
			continue;
		else if(szLineBuf[0] == 'm')
		{
			char szMtlLibFile[1024];
			sscanf(szLineBuf, "%*s %s", szMtlLibFile);
			LoadMtlLib(sFolder, std::string(szMtlLibFile));
		}
		else if(szLineBuf[0] == 'g')
		{
			if(!vecVertex.empty())
			{
				vecAllVertex.insert(vecAllVertex.end(), vecVertex.begin(), vecVertex.end());
				int nAttrId = m_mapMtlTex[sMtlName]->m_nAttrId;
				for (int i = 0; i < vecVertex.size() / 3; ++i)
				{
					vecAttrID.push_back(nAttrId);
				}
				vecVertex.clear();
			}	
		}
		else if(szLineBuf[0] == 'v')
		{
			if(szLineBuf[1] == ' ')
			{
				float x, y, z;
				sscanf(szLineBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if(szLineBuf[1] == 't')
			{
				float u, v;
				sscanf(szLineBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if(szLineBuf[1] == 'n')
			{
				float x, y, z;
				sscanf(szLineBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if(szLineBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf(szLineBuf, "%*s %s", szMtlName);
			sMtlName = std::string(szMtlName);
		}
		else if(szLineBuf[0] == 'f')
		{
			int aIndex[3][3];
			sscanf(szLineBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2], 
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2], 
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);
			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];
				vecVertex.push_back(v);
			}
		}
	}

	vecMtlTex.resize(m_mapMtlTex.size());
	for each(auto p in m_mapMtlTex)
	{
		vecMtlTex[p.second->m_nAttrId] = p.second;
	}

	fclose(fp);

	LPD3DXMESH pMesh = NULL;

	HRESULT hr = D3DXCreateMeshFVF(vecAllVertex.size() / 3,
		vecAllVertex.size(),
		D3DXMESH_MANAGED,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&pMesh);

	ST_PNT_VERTEX* pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecAllVertex[0], vecAllVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	WORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (size_t i = 0; i < vecAllVertex.size(); ++i)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttrID[0], vecAttrID.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdjBuffer(vecAllVertex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

	pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT | 
		D3DXMESHOPT_COMPACT | 
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuffer[0], 0, 0, 0);

// 	if(hr == E_FAIL)
// 		return NULL;

	return pMesh;
}

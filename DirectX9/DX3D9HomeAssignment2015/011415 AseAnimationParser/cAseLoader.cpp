#include "StdAfx.h"
#include "cAseLoader.h"
#include "../Common/Asciitok.h"
#include "cFrame.h"
#include "cMtlTex.h"

cAseLoader::cAseLoader(void)
	: m_pRootFrame(NULL)
{
}

cAseLoader::~cAseLoader(void)
{
}

cFrame* cAseLoader::Load(std::string& sFolder, std::string& sFileName)
{
	m_sFolder = sFolder;

	fopen_s(&m_fp, (sFolder + sFileName).c_str(), "r");

	while (char* szToken = GetToken())
	{
		if (IsEqual(szToken, ID_SCENE))
			SkipBlock();
		else if (IsEqual(szToken, ID_MATERIAL_LIST))
		{
			ProcessMaterialList();
		}
		else if (IsEqual(szToken, ID_GEOMETRY))
		{
			cFrame* pFrame = ProcessGeomObject();
			m_mapFrame[pFrame->m_sNodeName] = pFrame;
			if (m_pRootFrame)
			{
				if (pFrame->m_sParentName.length() > 0)
					m_mapFrame[pFrame->m_sParentName]->AddChild(pFrame);
			}
			else
			{
				m_pRootFrame = pFrame;
			}
		}
	}

	fclose(m_fp);

	for each(auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}
	return m_pRootFrame;
}

char* cAseLoader::GetToken()
{
	bool isQuote = false;
	int nCurrIndex = 0;

	while (unsigned char c = fgetc(m_fp))
	{
		if (feof(m_fp))
			break;

		if (IsWhite(c) && !isQuote)
		{
			if (nCurrIndex == 0)
				continue;
			else
				break;
		}

		if (c == '\"')
		{
			if (isQuote)
			{
				break;
			}
			else
			{
				isQuote = true;
				continue;
			}
		}

		m_szToken[nCurrIndex++] = c;
	}

	if (nCurrIndex == 0)
		return NULL;

	m_szToken[nCurrIndex] = '\0';

	return m_szToken;
}

bool cAseLoader::IsWhite(char c)
{
	return c < 33;
}

bool cAseLoader::IsEqual(char* szStr1, char* szStr2)
{
	return strcmp(szStr1, szStr2) == 0;
}

int cAseLoader::GetInteger()
{
	return atoi(GetToken());
}

float cAseLoader::GetFloat()
{
	return (float)atof(GetToken());
}

void cAseLoader::SkipBlock()
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMaterialList()
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			// 				D3DXVec3TransformCoord()
			// 				D3DXVec3TransformNormal()
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MATERIAL_COUNT))
		{
			m_vecMtlTex.resize(GetInteger());
			for (size_t i = 0; i < m_vecMtlTex.size(); ++i)
			{
				m_vecMtlTex[i] = new cMtlTex;
			}
		}
		else if (IsEqual(szToken, ID_MATERIAL))
		{
			int nMtlRef = GetInteger();
			ProcessMaterial(m_vecMtlTex[nMtlRef]);
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMaterial(cMtlTex* pMtlTex)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_AMBIENT))
		{
			pMtlTex->stMtl.Ambient.r = GetFloat();
			pMtlTex->stMtl.Ambient.g = GetFloat();
			pMtlTex->stMtl.Ambient.b = GetFloat();
			pMtlTex->stMtl.Ambient.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_DIFFUSE))
		{
			pMtlTex->stMtl.Diffuse.r = GetFloat();
			pMtlTex->stMtl.Diffuse.g = GetFloat();
			pMtlTex->stMtl.Diffuse.b = GetFloat();
			pMtlTex->stMtl.Diffuse.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_SPECULAR))
		{
			pMtlTex->stMtl.Specular.r = GetFloat();
			pMtlTex->stMtl.Specular.g = GetFloat();
			pMtlTex->stMtl.Specular.b = GetFloat();
			pMtlTex->stMtl.Specular.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_MAP_DIFFUSE))
		{
			ProcessMapDiffuse(pMtlTex);
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMapDiffuse(cMtlTex* pMtlTex)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_BITMAP))
		{

			char* szFileName = GetToken();
			std::string s = std::string("../Resource/");
			s += "ase/";
			s += szFileName;
			pMtlTex->pTex = g_pTextureManager->GetTexture(s.c_str());
			/*char* szFilename = GetToken();
			pMtlTex->pTex = g_pTextureManager->GetTexture(m_sFolder + std::string(szFilename));*/
		}
	} while (nLevel > 0);
}

cFrame* cAseLoader::ProcessGeomObject()
{
	cFrame* pFrame = new cFrame;
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_NODE_NAME))
		{
			pFrame->m_sNodeName = GetToken();
		}
		else if (IsEqual(szToken, ID_NODE_PARENT))
		{
			pFrame->m_sParentName = GetToken();
		}
		else if (IsEqual(szToken, ID_NODE_TM))
		{
			ProcessNodeTM(pFrame);
		}
		else if (IsEqual(szToken, ID_MESH))
		{
			ProcessMesh(pFrame);
		}
		else if (IsEqual(szToken, ID_TM_ANIMATION))
		{
			ProcessTMAnimation(pFrame->m_stNodeAni);
			pFrame->CalcAccumRotTracks();
		}
		else if (IsEqual(szToken, ID_MATERIAL_REF))
		{
			int nIndex = GetInteger();
			pFrame->SetMtlTex(m_vecMtlTex[nIndex]);
		}
	} while (nLevel > 0);

	return pFrame;
}

void cAseLoader::ProcessNodeTM(cFrame* pFrame)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_TM_ROW0))
		{
			pFrame->m_matWorldTM._11 = GetFloat();
			pFrame->m_matWorldTM._13 = GetFloat();
			pFrame->m_matWorldTM._12 = GetFloat();
			pFrame->m_matWorldTM._14 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW1))
		{
			pFrame->m_matWorldTM._31 = GetFloat();
			pFrame->m_matWorldTM._33 = GetFloat();
			pFrame->m_matWorldTM._32 = GetFloat();
			pFrame->m_matWorldTM._34 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW2))
		{
			pFrame->m_matWorldTM._21 = GetFloat();
			pFrame->m_matWorldTM._23 = GetFloat();
			pFrame->m_matWorldTM._22 = GetFloat();
			pFrame->m_matWorldTM._24 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW3))
		{
			pFrame->m_matWorldTM._41 = GetFloat();
			pFrame->m_matWorldTM._43 = GetFloat();
			pFrame->m_matWorldTM._42 = GetFloat();
			pFrame->m_matWorldTM._44 = 1.0f;
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMesh(cFrame* pFrame)
{
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<ST_PNT_VERTEX>	vecVertex;

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_NUMVERTEX))
		{
			vecV.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_NUMFACES))
		{
			vecVertex.resize(GetInteger() * 3);
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX_LIST))
		{
			ProcessMeshVertexList(vecV);
		}
		else if (IsEqual(szToken, ID_MESH_FACE_LIST))
		{
			ProcessMeshFaceList(vecVertex, vecV);
		}
		else if (IsEqual(szToken, ID_MESH_NUMTVERTEX))
		{
			vecVT.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_TVERTLIST))
		{
			ProcessMeshTVertList(vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_TFACELIST))
		{
			ProcessMeshTFaceList(vecVertex, vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_NORMALS))
		{
			ProcessMeshNormals(vecVertex);
		}
	} while (nLevel > 0);

	pFrame->BuidlMesh(vecVertex);
}

void cAseLoader::ProcessMeshVertexList(std::vector<D3DXVECTOR3>& vecV)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX))
		{
			int nNum = GetInteger();
			vecV[nNum].x = GetFloat();
			vecV[nNum].z = GetFloat();
			vecV[nNum].y = GetFloat();
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMeshFaceList(OUT std::vector<ST_PNT_VERTEX>& vecVertex,
	IN std::vector<D3DXVECTOR3>& vecV)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_FACE))
		{
			int nFaceIndex = GetInteger();
			GetToken(); // A:
			int nA = GetInteger();
			GetToken(); // B:
			int nB = GetInteger();
			GetToken(); // C:
			int nC = GetInteger();
			vecVertex[nFaceIndex * 3 + 0].p = vecV[nA];
			vecVertex[nFaceIndex * 3 + 1].p = vecV[nC];
			vecVertex[nFaceIndex * 3 + 2].p = vecV[nB];
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMeshTVertList(std::vector<D3DXVECTOR2>& vecVT)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_TVERT))
		{
			int nNum = GetInteger();
			vecVT[nNum].x = GetFloat();
			vecVT[nNum].y = 1.0f - GetFloat();
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMeshTFaceList(OUT std::vector<ST_PNT_VERTEX>& vecVertex, IN std::vector<D3DXVECTOR2>& vecVT)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_TFACE))
		{
			int nFaceIndex = GetInteger();
			int nA = GetInteger();
			int nB = GetInteger();
			int nC = GetInteger();
			vecVertex[nFaceIndex * 3 + 0].t = vecVT[nA];
			vecVertex[nFaceIndex * 3 + 1].t = vecVT[nC];
			vecVertex[nFaceIndex * 3 + 2].t = vecVT[nB];
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMeshNormals(OUT std::vector<ST_PNT_VERTEX>& vecVertex)
{
	int nFaceIndex = 0;
	int nIndexAtFace = 0;
	int aIndexCorr[] = { 0, 2, 1 };
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_FACENORMAL))
		{
			nFaceIndex = GetInteger();
			nIndexAtFace = 0;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEXNORMAL))
		{
			GetToken();
			float x = GetFloat();
			float z = GetFloat();
			float y = GetFloat();
			vecVertex[nFaceIndex * 3 + aIndexCorr[nIndexAtFace]].n = D3DXVECTOR3(x, y, z);
			++nIndexAtFace;
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessTMAnimation(IN OUT stAseTrackAni& stTrack){
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_POS_TRACK))
		{
			ProcessPosTrack(stTrack);
		}
		else if (IsEqual(szToken, ID_ROT_TRACK)){
			ProcessRotTrack(stTrack);
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessPosTrack(IN OUT stAseTrackAni& stTrack){
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_POS_SAMPLE))
		{
			stAseTrack vTrs;
			vTrs.nf = GetInteger();
			vTrs.x = GetFloat();
			vTrs.z = GetFloat();
			vTrs.y = GetFloat();
			vTrs.w = 0.0f;
			stTrack.vTrs.push_back(vTrs);
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessRotTrack(IN OUT stAseTrackAni& stTrack){
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_ROT_SAMPLE))
		{
			stAseTrack vRot;
			vRot.nf = GetInteger();
			vRot.x = GetFloat();
			vRot.z = GetFloat();
			vRot.y = GetFloat();
			vRot.w = GetFloat();
			stTrack.vRot.push_back(vRot);
		}
	} while (nLevel > 0);
}

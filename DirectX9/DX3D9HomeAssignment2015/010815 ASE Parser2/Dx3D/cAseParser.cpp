#include "stdafx.h"
#include "cAseParser.h"

#define MAX_PARSE_LINE	1024


void LcStr_Trim(char* sBuf)
{
	INT iLen = 0;

	INT	i = 0;
	INT iCnt = 0;

	iLen = strlen(sBuf);

	if (iLen <1)
		return;


	// 문자 \r \n제거
	for (i = iLen - 1; i >= 0; --i)
	{
		char* p = sBuf + i;

		if ('\n' == *p || '\r' == *p)
		{
			*(sBuf + i) = '\0';
		}

		++iCnt;

		if (iCnt>2)
			break;
	}


	// 우측의 공백 제거
	iCnt = 0;
	iLen = strlen(sBuf);

	for (i = iLen - 1; i >= 0; --i)
	{
		char* p = sBuf + i;

		if (' ' == *p || '\t' == *p)
			continue;

		*(sBuf + i + 1) = '\0';
		break;
	}

	iLen = i + 1 + 1;

	// 좌측의 공백제거
	char sT[MAX_PARSE_LINE] = { 0 };

	strncpy(sT, sBuf, iLen);

	for (i = 0; i < iLen; ++i)
	{
		char* p = sT + i;

		if (' ' == *p || '\t' == *p)
			continue;

		break;
	}

	strcpy(sBuf, sT + i);
}



void LcStr_Quot(char* sDst, const char* sSrc)
{
	INT iLen = strlen(sSrc);
	INT	nBgn = -1;
	INT bStrt = 0;
	INT iRead = 0;

	char* p = (char*)sSrc;

	while (0 != *p)
	{
		if ('\"' == *p && 0 == bStrt)
			bStrt = 1;

		else if ('\"' == *p && 1 == bStrt)
		{
			*(sDst + nBgn) = 0;
			break;
		}

		if (nBgn >= 0 && 1 == bStrt)
			*(sDst + nBgn) = *p;

		if (1 == bStrt)
			++nBgn;

		++p;
	}
}


cAseParser::cAseParser()
{
	m_pDev = NULL;

	m_nMtl = 0;
	m_pMtl = NULL;

	m_nGeo = 0;
	m_pGeo = NULL;
}


cAseParser::~cAseParser()
{
	Destroy();
}


void cAseParser::Destroy()
{
	m_nMtl = 0;
	m_nGeo = 0;

	if (m_pGeo)	{ delete[] m_pGeo;	m_pGeo = NULL; }
	if (m_pMtl)	{ delete[] m_pMtl;	m_pMtl = NULL; }
}


INT cAseParser::Create(LPDIRECT3DDEVICE9 p1, const char* p2, void* p3, void* p4)
{
	m_pDev = (LPDIRECT3DDEVICE9)p1;
	strcpy(m_sFile, (char*)p2);


	if (FAILED(Load()))
		return -1;

	//	Confirm();


	INT i = 0;

	for (i = 0; i<m_nGeo; ++i)
	{
		AseGeo*		pGeo = &m_pGeo[i];

		pGeo->iNix = GetNumIdx(i);						// Number of Index
		pGeo->iNvx = GetNumVtx(i);						// Number of Vertex
		pGeo->pVtx = GetPtVtx(i);

		pGeo->pIdx = (AseFce*)GetPtIdx(i);

		if (AseVtx::FVF == pGeo->dFVF)
			pGeo->dStrid = sizeof(AseVtx);

		else if (AseVtxN::FVF == pGeo->dFVF)
			pGeo->dStrid = sizeof(AseVtxN);

		else if (AseVtxUV::FVF == pGeo->dFVF)
			pGeo->dStrid = sizeof(AseVtxUV);

		else if (AseVtxNUV::FVF == pGeo->dFVF)
			pGeo->dStrid = sizeof(AseVtxNUV);
	}



	// Material Texture Load
	for (i = 0; i<m_nMtl; ++i)
	{
		AseMtl*		pMtl = &m_pMtl[i];

		if (strlen(pMtl->sTex))
		{
			char sFile[_MAX_PATH];

			DWORD		color = 0x00FFFFFF;
			DWORD		Filter = (D3DX_FILTER_TRIANGLE | D3DX_FILTER_MIRROR);
			DWORD		MipFilter = (D3DX_FILTER_TRIANGLE | D3DX_FILTER_MIRROR);
			D3DFORMAT	d3dFormat = D3DFMT_UNKNOWN;

			//"../../Resource/ase/woman/woman_01_all.ase"
			sprintf(sFile, "../../Resource/ase/woman/%s", pMtl->sTex);

			if (FAILED(D3DXCreateTextureFromFileEx(m_pDev
				, sFile
				, D3DX_DEFAULT
				, D3DX_DEFAULT
				, D3DX_DEFAULT
				, 0
				, d3dFormat
				, D3DPOOL_MANAGED
				, Filter
				, MipFilter
				, color
				, &pMtl->pImg
				, NULL
				, &pMtl->pTex
				)))
			{
				MessageBox(GetActiveWindow(), "Cannot Read Model Texture", "Error", 0);
			}
		}
	}

	return 0;
}


INT cAseParser::FrameMove()
{
	return 0;
}




void cAseParser::Render()
{
	if (!m_pGeo)
		return;


	m_pDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	INT	i = 0;
	int a = 0;
	for (i = 0; i<m_nGeo; ++i)
	{
		AseGeo*		pGeo = &m_pGeo[i];

		if (NULL == pGeo->pVtx)
			continue;

		m_pDev->SetFVF(pGeo->dFVF);

		m_pDev->SetFVF(pGeo->dFVF);

		LPDIRECT3DTEXTURE9	pTx = NULL;

		if (pGeo->nMtlRef >= 0)
			pTx = m_pMtl[pGeo->nMtlRef].pTex;

		if (NULL == pTx)
			continue;


		m_pDev->SetTexture(0, pTx);

		m_pDev->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST
			, 0						// Minimum Vertex Index
			, pGeo->iNvx			// Number vertex indices
			, pGeo->iNix			// Primitive Count
			, pGeo->pIdx			// IndexData pointer
			, D3DFMT_INDEX16		// Index Data format
			, pGeo->pVtx			// Vetex stream zero data
			, pGeo->dStrid			// Vertex Stream Zero Stride
			);
	}

	m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);					// 다시 Solid
	m_pDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

INT cAseParser::GetNumMtl()
{
	return m_nMtl;
}


INT cAseParser::GetNumGeo()
{
	return m_nGeo;
}

INT cAseParser::GetNumVtx(INT nGeo)
{
	AseGeo* pGeo = &m_pGeo[nGeo];

	if (AseVtx::FVF == pGeo->dFVF)
		return pGeo->iNumVtx;

	else if (AseVtxN::FVF == pGeo->dFVF)
		return pGeo->iNumVtx;

	else if (AseVtxUV::FVF == pGeo->dFVF)
		return pGeo->iNumTvtx;

	else if (AseVtxNUV::FVF == pGeo->dFVF)
		return pGeo->iNumTvtx;

	return  0;
}

INT cAseParser::GetNumIdx(INT nGeo)
{
	AseGeo* pGeo = &m_pGeo[nGeo];

	if (AseVtx::FVF == pGeo->dFVF)
		return pGeo->iNumFce;

	else if (AseVtxN::FVF == pGeo->dFVF)
		return pGeo->iNumFce;

	else if (AseVtxUV::FVF == pGeo->dFVF)
		return pGeo->iNumTfce;

	else if (AseVtxNUV::FVF == pGeo->dFVF)
		return pGeo->iNumTfce;

	return  0;
}

void*  cAseParser::GetPtVtx(INT nGeo)
{
	AseGeo* pGeo = &m_pGeo[nGeo];

	if (AseVtx::FVF == pGeo->dFVF)
		return pGeo->pLstVtx;

	else if (AseVtxN::FVF == pGeo->dFVF)
		return pGeo->pVtxN;

	else if (AseVtxUV::FVF == pGeo->dFVF)
		return pGeo->pVtxUV;

	else if (AseVtxNUV::FVF == pGeo->dFVF)
		return pGeo->pVtxNUV;

	return  NULL;
}

void*  cAseParser::GetPtIdx(INT nGeo)
{
	AseGeo* pGeo = &m_pGeo[nGeo];

	if (AseVtx::FVF == pGeo->dFVF)
		return pGeo->pLstFce;

	else if (AseVtxN::FVF == pGeo->dFVF)
		return pGeo->pLstFce;

	else if (AseVtxUV::FVF == pGeo->dFVF)
		return pGeo->pLstTfce;

	else if (AseVtxNUV::FVF == pGeo->dFVF)
		return pGeo->pLstTfce;

	return  NULL;
}



enum	EAseKey
{
	MTRL_LST,	// 0
	MTRL_CNT,	// 1
	MTRL_INF,	// 2

	MTRL_MAPDIF,	// 3
	MTRL_TEXDIF,	// 4

	GEOOBJECT,	// 5
	NODE_NAME,	// 6
	MTRL_REF,	// 7

	NODE_TM,	// 8
	TM_ROW0,	// 8
	TM_ROW1,	// 8
	TM_ROW2,	// 8
	TM_ROW3,	// 8
	TM_POS,	// 8
	TM_ROT,	// 8
	TM_RTA,	// 8
	TM_SCL,	// 8

	MESH_INFOS,	// 9
	MESH_NUMVTX,	// 10
	MESH_NUMFCE,	// 11
	MESH_VTXLST,	// 12
	MESH_VTXREC,	// 13
	MESH_FCELST,	// 14
	MESH_FCEREC,	// 15

	MESH_NUMTVTX,	// 16
	MESH_TVTXLST,	// 17
	MESH_TVTXREC,	// 18

	MESH_NUMTFCE,	// 19
	MESH_TFCELST,	// 20
	MESH_TFCEREC,	// 21

	MESH_NORMAL,	// 22
	MESH_FCENRL,	// 23

	TM_ANIMATION,
	ROT_TRACK,
	ROT_SAMPLE,
	SCALE_TRACK,
	SCALE_SAMPLE,
	POS_TRACK,
	POS_SAMPLE,

	ROT_TCB,
	ROT_TCB_KEY,
};



// Parsing Keyword
cAseParser::AseKey	Keywords[] =
{
	"*MATERIAL_LIST {",	// MTRL_LST
	"*MATERIAL_COUNT",	// MTRL_CNT
	"*MATERIAL ",	// MTRL_INF

	"*MAP_DIFFUSE {",	// MTRL_MAPDIF
	"*BITMAP",	// MTRL_TEXDIF

	"*GEOMOBJECT {",	// GEOOBJECT
	"*NODE_NAME",	// NODE_NAME
	"*MATERIAL_REF",	// MTRL_REF

	"*NODE_TM {",	// NODE_TM
	"*TM_ROW0",	// TM_ROW0
	"*TM_ROW1",	// TM_ROW1
	"*TM_ROW2",	// TM_ROW2
	"*TM_ROW3",	// TM_ROW3
	"*TM_POS",	// TM_POS
	"*TM_ROTAXIS",	// TM_ROT
	"*TM_ROTANGLE",	// TM_RTA
	"*TM_SCALE",	// TM_SCL

	"*MESH {",	// MESH_INFOS
	"*MESH_NUMVERTEX",	// MESH_NUMVTX
	"*MESH_NUMFACES",	// MESH_NUMFCE
	"*MESH_VERTEX_LIST {",	// MESH_VTXLST
	"*MESH_VERTEX",	// MESH_VTXREC
	"*MESH_FACE_LIST {",	// MESH_FCELST
	"*MESH_FACE",	// MESH_FCEREC

	"*MESH_NUMTVERTEX",	// MESH_NUMTVTX
	"*MESH_TVERTLIST {",	// MESH_TVTXLST
	"*MESH_TVERT",	// MESH_TVTXREC

	"*MESH_NUMTVFACES",	// MESH_NUMTFCE
	"*MESH_TFACELIST {",	// MESH_TFCELST
	"*MESH_TFACE",	// MESH_TFCEREC

	"*MESH_NORMALS {",	// MESH_NORMAL
	"*MESH_FACENORMAL",	// MESH_FCENRL

	"*TM_ANIMATION {",	// TM_ANIMATION
	"*CONTROL_ROT_TRACK {",	// ROT_TRACK
	"*CONTROL_ROT_SAMPLE",	// ROT_SAMPLE
	"*CONTROL_SCALE_TRACK {",	// SCALE_TRACK
	"*CONTROL_SCALE_SAMPLE",	// SCALE_SAMPLE
	"*CONTROL_POS_TRACK {",	// POS_TRACK
	"*CONTROL_POS_SAMPLE",	// POS_SAMPLE

	"*CONTROL_ROT_TCB {",	// ROT_TCB
	"*CONTROL_TCB_ROT_KEY",	// ROT_TCB_KEY
};



BOOL cAseParser::CompareAseKey(char* val, char* key)
{
	return (0 == _strnicmp(val, key, strlen(key))) ? 1 : 0;
}



INT cAseParser::Load()
{
	FILE*	fp;
	char	sLine[MAX_PARSE_LINE];

	fp = fopen(m_sFile, "rt");

	if (NULL == fp)
		return -1;


	// Material의 숫자를 센다.
	m_nMtl = 0;


	while (!feof(fp))
	{
		fgets(sLine, MAX_PARSE_LINE, fp);
		LcStr_Trim(sLine);

		if (CompareAseKey(sLine, Keywords[MTRL_LST]))
		{
			while (!feof(fp))
			{
				fgets(sLine, MAX_PARSE_LINE, fp);
				LcStr_Trim(sLine);

				if ('}' == sLine[0])
					break;

				if (CompareAseKey(sLine, Keywords[MTRL_CNT]))
				{
					INT		iNmtl;
					sscanf(sLine, "%*s %d", &iNmtl);
					m_nMtl = iNmtl;

					if (m_nMtl>0)
						m_pMtl = new cAseParser::AseMtl[m_nMtl];
				}

				if (CompareAseKey(sLine, Keywords[MTRL_INF]))
				{
					INT	nMtl = -1;
					sscanf(sLine, "%*s %d", &nMtl);

					while (!feof(fp))
					{
						fgets(sLine, MAX_PARSE_LINE, fp);
						LcStr_Trim(sLine);

						if ('}' == sLine[0])
							break;

						if (CompareAseKey(sLine, Keywords[MTRL_MAPDIF]))
						{
							while (!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LcStr_Trim(sLine);

								if ('}' == sLine[0])
									break;

								if (CompareAseKey(sLine, Keywords[MTRL_TEXDIF]))
								{
									char	sFile[512];
									LcStr_Quot(sFile, sLine);

									char sTx[_MAX_FNAME] = { 0 };
									char dir[_MAX_DIR] = { 0 };
									char ext[_MAX_EXT];

									_splitpath(sFile, NULL, dir, sTx, ext);

									sprintf(m_pMtl[nMtl].sTex, "%s%s", sTx, ext);
								}

							}// while
						}// if

					}// while
				}// if


			}// while
		}//if
	}// while



	// 파일 포인터를 처음으로 옮긴다.
	fseek(fp, 0, SEEK_SET);




	//Geometry의 숫자를 센다.
	m_nGeo = 0;

	while (!feof(fp))
	{
		fgets(sLine, MAX_PARSE_LINE, fp);
		LcStr_Trim(sLine);

		if (CompareAseKey(sLine, Keywords[GEOOBJECT]))
			++m_nGeo;
	}

	if (0 == m_nGeo)
	{
		fclose(fp);
		return -1;
	}

	// 파일 포인터를 처음으로 옮긴다.
	fseek(fp, 0, SEEK_SET);


	m_pGeo = new AseGeo[m_nGeo];
	INT	nGeoIdx = -1;

	while (!feof(fp))
	{
		fgets(sLine, MAX_PARSE_LINE, fp);
		LcStr_Trim(sLine);


		if (CompareAseKey(sLine, Keywords[GEOOBJECT]))
		{
			++nGeoIdx;
			AseGeo* pGeo = &m_pGeo[nGeoIdx];

			while (!feof(fp))
			{
				fgets(sLine, MAX_PARSE_LINE, fp);
				LcStr_Trim(sLine);

				if ('}' == sLine[0])
					break;


				if (CompareAseKey(sLine, Keywords[MTRL_REF]))
				{
					INT		nMtl;
					sscanf(sLine, "%*s %d", &nMtl);
					pGeo->nMtlRef = nMtl;
				}

				if (CompareAseKey(sLine, Keywords[NODE_NAME]))
				{
					char	sName[64];
					LcStr_Quot(sName, sLine);
					strcpy(pGeo->sNodeName, sName);
				}


				if (CompareAseKey(sLine, Keywords[NODE_TM]))
				{
					// Node TM
					while (!feof(fp))
					{
						fgets(sLine, MAX_PARSE_LINE, fp);
						LcStr_Trim(sLine);

						if ('}' == sLine[0])
							break;


						if (CompareAseKey(sLine, Keywords[TM_ROW0]))
						{
							FLOAT	x = 0.F, y = 0.F, z = 0.F, w = 0.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->tmInf.mtW[0][0] = x;
							pGeo->tmInf.mtW[0][1] = z;
							pGeo->tmInf.mtW[0][2] = y;
							pGeo->tmInf.mtW[0][3] = w;
						}

						if (CompareAseKey(sLine, Keywords[TM_ROW1]))
						{
							FLOAT	x = 0.F, y = 0.F, z = 0.F, w = 0.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->tmInf.mtW[2][0] = x;
							pGeo->tmInf.mtW[2][1] = z;
							pGeo->tmInf.mtW[2][2] = y;
							pGeo->tmInf.mtW[2][3] = w;
						}

						if (CompareAseKey(sLine, Keywords[TM_ROW2]))
						{
							FLOAT	x = 0.F, y = 0.F, z = 0.F, w = 0.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->tmInf.mtW[1][0] = x;
							pGeo->tmInf.mtW[1][1] = z;
							pGeo->tmInf.mtW[1][2] = y;
							pGeo->tmInf.mtW[1][3] = w;
						}

						if (CompareAseKey(sLine, Keywords[TM_ROW3]))
						{
							FLOAT	x = 0.F, y = 0.F, z = 0.F;
							FLOAT	w = 1.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->tmInf.mtW[3][0] = x;
							pGeo->tmInf.mtW[3][1] = z;
							pGeo->tmInf.mtW[3][2] = y;
							pGeo->tmInf.mtW[3][3] = w;
						}

						if (CompareAseKey(sLine, Keywords[TM_POS]))
						{
							FLOAT	x = 0.F, y = 0.F, z = 0.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->tmInf.Px = x;
							pGeo->tmInf.Py = z;
							pGeo->tmInf.Pz = y;
						}


						if (CompareAseKey(sLine, Keywords[TM_ROT]))
						{
							FLOAT	x = 0.F, y = 0.F, z = 0.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->tmInf.Rx = x;
							pGeo->tmInf.Ry = z;
							pGeo->tmInf.Rz = y;
						}

						if (CompareAseKey(sLine, Keywords[TM_RTA]))
						{
							FLOAT	w = 0.F;
							sscanf(sLine, "%*s %f", &w);

							pGeo->tmInf.Rw = w;
						}

						if (CompareAseKey(sLine, Keywords[TM_SCL]))
						{
							FLOAT	x = 0.F, y = 0.F, z = 0.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->tmInf.Sx = x;
							pGeo->tmInf.Sy = z;
							pGeo->tmInf.Sz = y;
						}

					}// while NODE_TM
				}


				if (CompareAseKey(sLine, Keywords[MESH_INFOS]))
				{
					while (!feof(fp))
					{
						fgets(sLine, MAX_PARSE_LINE, fp);
						LcStr_Trim(sLine);

						if ('}' == sLine[0])
							break;

						if (CompareAseKey(sLine, Keywords[MESH_NUMVTX]))
						{
							INT		iNVx;
							sscanf(sLine, "%*s %d", &iNVx);

							pGeo->iNumVtx = iNVx;
							pGeo->pLstVtx = new cAseParser::AseVtx[iNVx];
						}

						if (CompareAseKey(sLine, Keywords[MESH_NUMFCE]))
						{
							INT		iNIx;
							sscanf(sLine, "%*s %d", &iNIx);

							pGeo->iNumFce = iNIx;
							pGeo->pLstFce = new cAseParser::AseFce[iNIx];
						}


						if (CompareAseKey(sLine, Keywords[MESH_VTXLST]))
						{
							while (!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LcStr_Trim(sLine);

								if ('}' == sLine[0])
									break;

								if (CompareAseKey(sLine, Keywords[MESH_VTXREC]))
								{
									INT		nIdx = 0;
									FLOAT	x = 0.F, y = 0.F, z = 0.F;
									sscanf(sLine, "%*s %d %f %f %f", &nIdx, &x, &y, &z);

									pGeo->pLstVtx[nIdx].x = x;
									pGeo->pLstVtx[nIdx].y = z;
									pGeo->pLstVtx[nIdx].z = y;
								}

							}
						}

						if (CompareAseKey(sLine, Keywords[MESH_FCELST]))
						{
							while (!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LcStr_Trim(sLine);

								if ('}' == sLine[0])
									break;

								if (CompareAseKey(sLine, Keywords[MESH_FCEREC]))
								{
									INT	nIdx = 0, a = 0, b = 0, c = 0;

									//									           *MESH_FACE 0:   A:  0  B: 1  C:  2
									sscanf(sLine, "%*s    %d: %*s %d %*s %d %*s %d", &nIdx, &a, &b, &c);

									pGeo->pLstFce[nIdx].a = a;
									pGeo->pLstFce[nIdx].b = c;
									pGeo->pLstFce[nIdx].c = b;
								}

							}// while
						}// if == MESH_FACE_LIST


						if (CompareAseKey(sLine, Keywords[MESH_NUMTVTX]))
						{
							INT		iNtvtx;
							sscanf(sLine, "%*s %d", &iNtvtx);
							pGeo->iNumTvtx = iNtvtx;
							pGeo->pLstTvtx = new cAseParser::AseTvtx[iNtvtx];

						}// if == *MESH_NUMTVERTEX


						if (CompareAseKey(sLine, Keywords[MESH_TVTXLST]))
						{
							while (!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LcStr_Trim(sLine);

								if ('}' == sLine[0])
									break;

								if (CompareAseKey(sLine, Keywords[MESH_TVTXREC]))
								{
									INT		nIdx = 0;
									FLOAT	u = 0.F, v = 0.F, w = 0.F;
									sscanf(sLine, "%*s %d %f %f %f", &nIdx, &u, &v, &w);

									pGeo->pLstTvtx[nIdx].u = u;
									pGeo->pLstTvtx[nIdx].v = 1.f - v;
									pGeo->pLstTvtx[nIdx].w = w;
								}


							}// while
						}// if == *MESH_TVERTLIST {


						if (CompareAseKey(sLine, Keywords[MESH_NUMTFCE]))
						{
							INT		iNtfce;
							sscanf(sLine, "%*s %d", &iNtfce);
							pGeo->iNumTfce = iNtfce;
							pGeo->pLstTfce = new cAseParser::AseFce[iNtfce];

						}// if == *MESH_NUMTVFACES


						if (CompareAseKey(sLine, Keywords[MESH_TFCELST]))
						{
							while (!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LcStr_Trim(sLine);

								if ('}' == sLine[0])
									break;

								if (CompareAseKey(sLine, Keywords[MESH_TFCEREC]))
								{
									INT		nIdx = 0;
									INT		a = 0, b = 0, c = 0;

									sscanf(sLine, "%*s %d %d %d %d", &nIdx, &a, &b, &c);

									pGeo->pLstTfce[nIdx].a = a;
									pGeo->pLstTfce[nIdx].b = c;
									pGeo->pLstTfce[nIdx].c = b;
								}


							}// while
						}// if == *MESH_TFACELIST {


						if (CompareAseKey(sLine, Keywords[MESH_NORMAL]))
						{
							pGeo->pLstNor = new cAseParser::AseVtx[pGeo->iNumVtx];

							while (!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LcStr_Trim(sLine);

								if ('}' == sLine[0])
									break;

							}// while
						}// if == *MESH_NORMALS {



					}// while
				}// if


				if (CompareAseKey(sLine, Keywords[TM_ANIMATION]))
				{
					while (!feof(fp))
					{
						fgets(sLine, MAX_PARSE_LINE, fp);
						LcStr_Trim(sLine);

						if ('}' == sLine[0])
							break;

						if (CompareAseKey(sLine, Keywords[ROT_TRACK]))
						{
							while (!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LcStr_Trim(sLine);

								if ('}' == sLine[0])
									break;

							}// while
						}// if == *CONTROL_ROT_TRACK {


						if (CompareAseKey(sLine, Keywords[POS_TRACK]))
						{
							while (!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LcStr_Trim(sLine);

								if ('}' == sLine[0])
									break;

							}// while
						}// if == *CONTROL_SCALE_TRACK {

						if (CompareAseKey(sLine, Keywords[SCALE_TRACK]))
						{
							while (!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LcStr_Trim(sLine);

								if ('}' == sLine[0])
									break;

							}// while
						}// if == *CONTROL_POS_TRACK {


						if (CompareAseKey(sLine, Keywords[ROT_TCB]))
						{
							while (!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LcStr_Trim(sLine);

								if ('}' == sLine[0])
									break;

							}// while
						}// if == *CONTROL_ROT_TCB {


					}// while
				}// if == *TM_ANIMATION {



			}// while
		}// if


	}// while


	fclose(fp);



	// Tface Processing
	//

	INT i = 0;
	INT j = 0;

	for (i = 0; i<m_nGeo; ++i)
	{
		AseGeo*	pGeo = &m_pGeo[i];
		INT		iTfce = pGeo->iNumTfce;
		INT		nMtrl = pGeo->nMtlRef;

		if (pGeo->pLstVtx)
			pGeo->dFVF = D3DFVF_XYZ;

		if (pGeo->pLstNor)
			pGeo->dFVF |= D3DFVF_NORMAL;

		if (iTfce >0 && nMtrl >= 0)
		{
			pGeo->dFVF |= D3DFVF_TEX1;

			for (j = 0; j<iTfce; ++j)
			{
				INT Ta = pGeo->pLstTfce[j].a;
				INT Tb = pGeo->pLstTfce[j].b;
				INT Tc = pGeo->pLstTfce[j].c;

				INT Va = pGeo->pLstFce[j].a;
				INT Vb = pGeo->pLstFce[j].b;
				INT Vc = pGeo->pLstFce[j].c;

				pGeo->pLstTvtx[Ta].nVt = Va;
				pGeo->pLstTvtx[Tb].nVt = Vb;
				pGeo->pLstTvtx[Tc].nVt = Vc;
			}
		}
	}

	for (i = 0; i<m_nGeo; ++i)
	{
		AseGeo*	pGeo = &m_pGeo[i];

		INT		iVtx = pGeo->iNumVtx;
		INT		iTvtx = pGeo->iNumTvtx;
		INT		iTfce = pGeo->iNumTfce;
		INT		nMtrl = pGeo->nMtlRef;


		if ((D3DFVF_XYZ | D3DFVF_NORMAL) == pGeo->dFVF)
		{
			pGeo->pVtxN = new AseVtxN[iVtx];

			for (j = 0; j<iVtx; ++j)
			{
				pGeo->pVtxN[j].Px = pGeo->pLstVtx[j].x;
				pGeo->pVtxN[j].Py = pGeo->pLstVtx[j].y;
				pGeo->pVtxN[j].Pz = pGeo->pLstVtx[j].z;

				pGeo->pVtxN[j].Nx = pGeo->pLstNor[j].x;
				pGeo->pVtxN[j].Ny = pGeo->pLstNor[j].y;
				pGeo->pVtxN[j].Nz = pGeo->pLstNor[j].z;
			}
		}


		else if ((D3DFVF_XYZ | D3DFVF_TEX1) == pGeo->dFVF)
		{
			pGeo->pVtxUV = new AseVtxUV[iTvtx];

			for (j = 0; j<iTvtx; ++j)
			{
				INT nVt = pGeo->pLstTvtx[j].nVt;

				pGeo->pVtxUV[j].Px = pGeo->pLstVtx[nVt].x;
				pGeo->pVtxUV[j].Py = pGeo->pLstVtx[nVt].y;
				pGeo->pVtxUV[j].Pz = pGeo->pLstVtx[nVt].z;

				pGeo->pVtxUV[j].u = pGeo->pLstTvtx[j].u;
				pGeo->pVtxUV[j].v = pGeo->pLstTvtx[j].v;
			}
		}


		else if ((D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) == pGeo->dFVF)
		{
			pGeo->pVtxNUV = new AseVtxNUV[iTvtx];

			for (j = 0; j<iTvtx; ++j)
			{
				INT nVt = pGeo->pLstTvtx[j].nVt;

				pGeo->pVtxNUV[j].Px = pGeo->pLstVtx[nVt].x;
				pGeo->pVtxNUV[j].Py = pGeo->pLstVtx[nVt].y;
				pGeo->pVtxNUV[j].Pz = pGeo->pLstVtx[nVt].z;

				pGeo->pVtxNUV[j].Nx = pGeo->pLstNor[nVt].x;
				pGeo->pVtxNUV[j].Ny = pGeo->pLstNor[nVt].y;
				pGeo->pVtxNUV[j].Nz = pGeo->pLstNor[nVt].z;

				pGeo->pVtxNUV[j].u = pGeo->pLstTvtx[j].u;
				pGeo->pVtxNUV[j].v = pGeo->pLstTvtx[j].v;
			}
		}
	}

	//

	return 1;
}




void cAseParser::Confirm()
{
	FILE*	fp;
	INT		i = 0, j = 0;


	char	sDst[260] = { 0 };
	strcpy(sDst, m_sFile);
	char * p = strchr(sDst, '.');
	*p = '\0';
	strcat(p, ".txt");


	fp = fopen(sDst, "wt");
	if (NULL == fp)
		return;


	fprintf(fp, "%s\n", Keywords[MTRL_LST]);
	fprintf(fp, "	%s	%d\n", Keywords[MTRL_CNT], m_nMtl);

	for (i = 0; i<m_nMtl; ++i)
	{
		fprintf(fp, "	%s %d {\n", Keywords[MTRL_INF], i);
		fprintf(fp, "		%s\n", Keywords[MTRL_MAPDIF]);

		fprintf(fp, "			%s	\"%s\"\n", Keywords[MTRL_TEXDIF], m_pMtl[i].sTex);

		fprintf(fp, "		}\n");
		fprintf(fp, "	}\n\n");
	}
	fprintf(fp, "}\n\n");



	// Geometry
	for (i = 0; i<m_nGeo; ++i)
	{
		fprintf(fp, "%s\n", Keywords[GEOOBJECT]);
		fprintf(fp, "	%s	\"%s\"\n", Keywords[NODE_NAME], m_pGeo[i].sNodeName);
		fprintf(fp, "	%s\n", Keywords[MESH_INFOS]);

		fprintf(fp, "		%s	%d\n", Keywords[MESH_NUMVTX], m_pGeo[i].iNumVtx);
		fprintf(fp, "		%s	%d\n", Keywords[MESH_NUMFCE], m_pGeo[i].iNumFce);

		fprintf(fp, "		%s\n", Keywords[MESH_VTXLST]);


		INT iNumVtx = m_pGeo[i].iNumVtx;

		for (j = 0; j<iNumVtx; ++j)
			fprintf(fp, "			%s	%f	%f	%f\n", Keywords[MESH_VTXREC]
			, m_pGeo[i].pLstVtx[j].x
			, m_pGeo[i].pLstVtx[j].y
			, m_pGeo[i].pLstVtx[j].z);

		fprintf(fp, "		}\n\n");

		fprintf(fp, "		%s\n", Keywords[MESH_FCELST]);

		INT iNumFce = m_pGeo[i].iNumFce;

		for (j = 0; j<iNumFce; ++j)
			fprintf(fp, "			%s	%u	%u	%u\n", Keywords[MESH_FCEREC]
			, m_pGeo[i].pLstFce[j].a
			, m_pGeo[i].pLstFce[j].b
			, m_pGeo[i].pLstFce[j].c);

		fprintf(fp, "		}\n");

		fprintf(fp, "	}\n");

		fprintf(fp, "}\n\n");
	}


	fclose(fp);
}


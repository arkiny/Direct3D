#include "stdafx.h"
#include "cMyASELoader.h"
#include "../Common/Asciitok.h"
#include "cMtlTex.h"

using namespace std;
cMyASELoader::cMyASELoader()
	: m_fp(NULL)
{
}


cMyASELoader::~cMyASELoader()
{
	for (auto p : m_vecMeshs){
		SAFE_RELEASE(p);
	}
	for (auto p : m_vecMtl){
		SAFE_RELEASE(p);
	}
}

void cMyASELoader::LoadMesh(){
#ifdef _DEBUG
	_ASSERT(m_bLoaded && "Data Not Loaded");
#endif
	int check = 0;
	for (size_t i = 0; i < m_vecASENode.size(); i++){
		if (m_vecASENode[i].nRef != INT_MAX){
			m_vecsubSet.push_back(m_vecASENode[i].nRef);
			LPD3DXMESH pMesh = NULL;
			HRESULT hr = D3DXCreateMeshFVF(m_vecASENode[i].vecVertex.size() / 3,
				m_vecASENode[i].vecVertex.size(),
				D3DXMESH_MANAGED,
				ST_PNT_VERTEX::FVF,
				g_pD3DDevice,
				&pMesh);

			ST_PNT_VERTEX* pV = NULL;
			pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
			memcpy(pV, &m_vecASENode[i].vecVertex[0], m_vecASENode[i].vecVertex.size() * sizeof(ST_PNT_VERTEX));
			pMesh->UnlockVertexBuffer();

			WORD* pI = NULL;
			pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
			for (size_t j = 0; j < pMesh->GetNumVertices(); ++j)
			{
				pI[j] = j;
			}
			pMesh->UnlockIndexBuffer();

			DWORD* pA = NULL;
			pMesh->LockAttributeBuffer(0, &pA);
			for (size_t j = 0; j < pMesh->GetNumFaces(); j++){
				pA[j] = m_vecASENode[i].nRef;
			}
			pMesh->UnlockAttributeBuffer();

			std::vector<DWORD> vecAdjBuffer(m_vecASENode[i].vecVertex.size());
			pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

			pMesh->OptimizeInplace(
				D3DXMESHOPT_ATTRSORT |
				D3DXMESHOPT_COMPACT |
				D3DXMESHOPT_VERTEXCACHE,
				&vecAdjBuffer[0], 0, 0, 0);

			m_vecMeshs.push_back(pMesh);
		}
	}
	m_bMeshed = true;
}

void cMyASELoader::Load(std::string& folderName, std::string& fileName){
	fopen_s(&m_fp, (folderName + fileName).c_str(), "r");
	
	while (char* szToken = GetToken()){
		if (strcmp(szToken, ID_SCENE) == 0)
			ParseScene();
		else if (isEqual(szToken, ID_MATERIAL_LIST))
			ParseBlockMaterialList();
		else if (isEqual(szToken, ID_GEOMETRY)){
			stASENode stNode;
			ParseGeometry(stNode);
			m_vecASENode.push_back(stNode);
		}
	}

#ifdef _DEBUG
	int debug = 0;
	for (auto p : m_vecASENode){
		if (p.nRef != INT_MAX){
			debug++;
		}
	}
	_ASSERT(debug == 26 && "All Texutresed GeomObject Not loaded // Woman_all.ase");
#endif
	m_bLoaded = true;
	fclose(m_fp);
}

void cMyASELoader::ParseScene(){
	int nLevel = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_FIRSTFRAME)){
			m_stSceneInfo.uiFrameFirst = GetInteger();
		}
		else if (isEqual(szToken, ID_LASTFRAME)){
			m_stSceneInfo.uiFrameLast = GetInteger();
		}
		else if (isEqual(szToken, ID_FRAMESPEED)){
			m_stSceneInfo.uiFrameSpeed = GetInteger();
		}
		else if (isEqual(szToken, ID_TICKSPERFRAME)){
			m_stSceneInfo.uiFrameTick = GetInteger();
		}
	} while (nLevel > 0);
}

void cMyASELoader::ParseTMAnimation(stAseTrackAni& stAseT){
	int nLevel = 0;
	
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_NODE_NAME)){
			stAseT.sNodeCur = GetToken();
		}
		else if (isEqual(szToken, ID_POS_TRACK)){
			stAseTrack pos;
			ParsePosTrack(pos);
			stAseT.vTrs.push_back(pos);
		}
		else if (isEqual(szToken, ID_ROT_TRACK)){
			stAseTrack pos;
			ParseRotTrack(stAseT);
			stAseT.vTrs.push_back(pos);
		}
		else if (isEqual(szToken, ID_SCALE_TRACK)){
			stAseTrack pos;
			ParseSclTrack(pos);
			stAseT.vTrs.push_back(pos);
		}
	} while (nLevel > 0);
}

void cMyASELoader::ParsePosTrack(stAseTrack& stAseT){
	int nLevel = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_POS_SAMPLE)){
			stAseT.nf = GetInteger() / m_stSceneInfo.uiFrameTick;
			stAseT.x = GetFloat();
			stAseT.y = GetFloat();
			stAseT.z = GetFloat();
			stAseT.w = 0.0f;
		}		
	} while (nLevel > 0);
}

void cMyASELoader::ParseRotTrack(stAseTrackAni& stAseT){
	int nLevel = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_ROT_SAMPLE)){
			int nf = GetInteger() / m_stSceneInfo.uiFrameTick;
			float fx, fy, fz, fw;
			fx = GetFloat();
			fy = GetFloat();
			fz = GetFloat();
			fw = GetFloat();
			float x, y, z, w;
			x = sinf(fw / 2.0f) * fx; 
			y = sinf(fw / 2.0f) * fy;
			z = sinf(fw / 2.0f) * fz;
			w = cosf(fw / 2.0f);
			if (stAseT.vRot.empty()){
				stAseTrack v;
				v.nf = nf; 
				v.x = x;
				v.y = y;
				v.z = z;
				v.w = w;
				stAseT.vRot.push_back(v);
			}
			else {
				D3DXQUATERNION q1(x, y, z, w);
				D3DXQUATERNION* q2;
				D3DXQUATERNION q3;
				q2 = (D3DXQUATERNION*)&stAseT.vRot.back();
				D3DXQuaternionMultiply(&q3, q2, &q1);
				stAseTrack v;
				v.nf = nf;
				v.x = q3.x;
				v.y = q3.y;
				v.z = q3.z;
				v.w = q3.w;
				stAseT.vRot.push_back(v);
			}
		}
	} while (nLevel > 0);
}

void cMyASELoader::ParseSclTrack(stAseTrack& stAseT){
	int nLevel = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_SCALE_SAMPLE)){
			stAseT.nf = GetInteger() / m_stSceneInfo.uiFrameTick;
			stAseT.x = GetFloat();
			stAseT.y = GetFloat();
			stAseT.z = GetFloat();
			stAseT.w = 0.0f;
		}
	} while (nLevel > 0);
}

void cMyASELoader::ParseMesh(stASENode& node){
	int numVertex = 0, numFaces = 0;
	int numTvertex = 0;

	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;

	int nLevel = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_TIMEVALUE))
		{
			//do nothing
		}
		else if (isEqual(szToken, ID_MESH_NUMVERTEX)){
			numVertex = GetInteger();
		}
		else if (isEqual(szToken, ID_MESH_NUMFACES))
		{
			numFaces = GetInteger();
		}
		else if (isEqual(szToken, ID_MESH_VERTEX_LIST)){
			// @todo
			vecV.resize(numVertex);
			ParseVertexList(vecV);
		}
		else if (isEqual(szToken, ID_MESH_FACE_LIST)){
			// @todo
			//node.vecVertex.resize(vecV.size() * 3);
			ParseFaceList(vecV, node.vecVertex);
#ifdef _DEBUG
			_ASSERT(node.vecVertex.size() / 3 == numFaces);
#endif
			vecV.clear();
		}
		else if (isEqual(szToken, ID_MESH_NUMTVERTEX)){
			numTvertex = GetInteger();
		}
		else if (isEqual(szToken, ID_MESH_TVERTLIST)){
			vecVT.resize(numTvertex);
			ParseTVertList(vecVT);
#ifdef _DEBUG
			_ASSERT(vecVT.size() == numTvertex);
#endif
		}
		else if (isEqual(szToken, ID_MESH_TFACELIST)){
			ParseTFaceList(vecVT, node.vecVertex);
			vecVT.clear();
		}
		else if (isEqual(szToken, ID_MESH_NORMALS)){
			ParseNormals(node.vecVertex);
		}
	} while (nLevel > 0);
}

void cMyASELoader::ParseTVertList(std::vector<D3DXVECTOR2>& vec){
	int nLevel = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_MESH_TVERT))
		{
			int vectorid = GetInteger();
			float x = GetFloat();
			float y = GetFloat();
			vec[vectorid].x = x;
			vec[vectorid].y = 1.0f - y;
		}
	} while (nLevel > 0);
}


void cMyASELoader::ParseVertexList(vector<D3DXVECTOR3>& vec){
	int nLevel = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_MESH_VERTEX))
		{
			int vectorid = GetInteger();
			float x = GetFloat();
			float z = GetFloat();
			float y = GetFloat();
			vec[vectorid].x = x;
			vec[vectorid].y = y;
			vec[vectorid].z = z;
		}
	} while (nLevel > 0);
}

void cMyASELoader::ParseFaceList(std::vector<D3DXVECTOR3>& vec, std::vector<ST_PNT_VERTEX>& vecPNT){
	int nLevel = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_MESH_FACE))
		{
			ST_PNT_VERTEX v;
			// 0:
			// atoi -> only parse the first number
			szToken = GetToken();
			szToken = GetToken();
			int a = GetInteger();
			szToken = GetToken();
			int b = GetInteger();
			szToken = GetToken();
			int c = GetInteger();
			
			v.p = vec[a];
			vecPNT.push_back(v);
			v.p = vec[c];
			vecPNT.push_back(v);
			v.p = vec[b];
			vecPNT.push_back(v);
			//vecPNT[nFaceIndex*3 + 0 ] = vec[a]
		}
	} while (nLevel > 0);
}

void cMyASELoader::ParseTFaceList(std::vector<D3DXVECTOR2>& vec, std::vector<ST_PNT_VERTEX>& vecPNT){
	int nLevel = 0;
	int index = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_MESH_TFACE))
		{
			// 0:
			int buf = GetInteger();
			int a = GetInteger();
			int b = GetInteger();
			int c = GetInteger();

			vecPNT[index].t = vec[a]; 
			index++;
			vecPNT[index].t = vec[c];
			index++;
			vecPNT[index].t = vec[b];
			index++;
		}
	} while (nLevel > 0);
}

void cMyASELoader::ParseNormals(std::vector<ST_PNT_VERTEX>& vecPNT){
	int nLevel = 0;
	int index = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_MESH_VERTEXNORMAL))
		{
			D3DXVECTOR3 stNorA, stNorB, stNorC;
			int buf = GetInteger();
			float x = GetFloat();
			float z = GetFloat();
			float y = GetFloat();

			stNorA = D3DXVECTOR3(x, z, y);
			szToken = GetToken();
			if (isEqual(szToken, ID_MESH_VERTEXNORMAL)){
				int buf = GetInteger();
				float x = GetFloat();
				float z = GetFloat();
				float y = GetFloat();
				stNorB = D3DXVECTOR3(x, z, y);
			}
			szToken = GetToken();
			if (isEqual(szToken, ID_MESH_VERTEXNORMAL)){
				int buf = GetInteger();
				float x = GetFloat();
				float z = GetFloat();
				float y = GetFloat();
				stNorC = D3DXVECTOR3(x, z, y);
			}			

			vecPNT[index].n = stNorA;
			index++;
			vecPNT[index].n = stNorC;
			index++;
			vecPNT[index].n = stNorB;
			index++;			
		}
	} while (nLevel > 0);
#ifdef _DEBUG
	_ASSERT(index == vecPNT.size() && "Normal check");
#endif
}

void cMyASELoader::ParseGeometry(stASENode& node){
	
	char* szNodeName;
	char* szParentName; 
	int refMat;	

	int nLevel = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_NODE_NAME))
		{
			szNodeName = GetToken();
			node.NodeName = szNodeName;
		}
		else if (isEqual(szToken, ID_NODE_PARENT)){
			szParentName = GetToken();
			node.NodeParent = szParentName;
		}
		else if (isEqual(szToken, ID_NODE_TM))
		{
			D3DXMATRIXA16 _matLocal;
			D3DXMatrixIdentity(&_matLocal);
			ParseNodeTM(_matLocal);
			node.LocalMat = _matLocal;
		}
		else if (isEqual(szToken, ID_MESH)){
			ParseMesh(node);
		}
		else if (isEqual(szToken, ID_PROP_MOTIONBLUR)){
			//do nothing
		}
		else if (isEqual(szToken, ID_PROP_CASTSHADOW)){
			//do nothing
		}
		else if (isEqual(szToken, ID_PROP_RECVSHADOW)){
			//do nothing
		}
		else if (isEqual(szToken, ID_TM_ANIMATION)){
			ParseTMAnimation(node.AnimationInfo);
		}
		else if (isEqual(szToken, ID_WIRECOLOR)){
			//do nothing
		}
		else if (isEqual(szToken, ID_MATERIAL_REF)){
			node.nRef = GetInteger();
		}
	} while (nLevel > 0);

//#ifdef _DEBUG
//	_ASSERT(nMtlCount == vecMtlTex.size()
//		&& "Material Count != Matrial Vector Size");
//#endif
}

void cMyASELoader::ParseNodeTM(D3DXMATRIXA16& mat){
	char* szNodeName;
	char* szParentName;
	int refMat;
	D3DXMATRIXA16 _matTrans, _matRot, _matScale ;
	D3DXVECTOR3 _RotAxis, _ScaleAxis;
	float _angle, _scaleAngle;
	D3DXMatrixIdentity(&_matTrans);
	D3DXMatrixIdentity(&_matRot);
	D3DXMatrixIdentity(&_matScale);

	D3DXMatrixIdentity(&mat);

	int nLevel = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_NODE_NAME))
		{
			// do nothing
		}
		else if (isEqual(szToken, ID_TM_ROW0)){
			mat._11 = GetFloat();
			mat._13 = GetFloat();
			mat._12 = GetFloat();
		}
		else if (isEqual(szToken, ID_TM_ROW1)){
			mat._31 = GetFloat();
			mat._33 = GetFloat();
			mat._32 = GetFloat();
		}
		else if (isEqual(szToken, ID_TM_ROW2)){
			mat._21 = GetFloat();
			mat._23 = GetFloat();
			mat._22 = GetFloat();
		}
		else if (isEqual(szToken, ID_TM_ROW3)){
			mat._41 = GetFloat();
			mat._43 = GetFloat();
			mat._42 = GetFloat();
		}
		else if (isEqual(szToken, ID_TM_POS)){
			D3DXMatrixTranslation(&_matTrans,
				GetFloat(), GetFloat(), GetFloat());
		}

		else if (isEqual(szToken, ID_TM_ROTAXIS)){
			_RotAxis.x = GetFloat();
			_RotAxis.y = GetFloat();
			_RotAxis.z = GetFloat();
		}

		else if (isEqual(szToken, ID_TM_ROTANGLE)){
			_angle = GetFloat();
			D3DXMatrixRotationAxis(&_matRot, &_RotAxis, _angle);
		}
		else if (isEqual(szToken, ID_TM_SCALE)){
			D3DXMatrixScaling(&_matScale,
				GetFloat(), GetFloat(), GetFloat());
		}
		else if (isEqual(szToken, ID_TM_SCALEAXIS)){
			_ScaleAxis.x = GetFloat();
			_ScaleAxis.y = GetFloat();
			_ScaleAxis.z = GetFloat();
		}
		else if (isEqual(szToken, ID_TM_SCALEAXISANG)){
			_scaleAngle = GetFloat();
		}		
	} while (nLevel > 0);
}


void cMyASELoader::SkipBlock(){
	int nLevel = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
	} while (nLevel > 0);
}

char* cMyASELoader::GetToken(){
	int nCurrIndex = 0;
	bool isQuote = false;
	while (char c = fgetc(m_fp)){
		if (feof(m_fp))
			break;
		
		if (isWhite(c)) {
			if (nCurrIndex == 0 || isQuote)
				continue;
			else
				break;
		}

		if (c == '\"'){
			if (isQuote){
				isQuote = false;
				break;
			}
			else {
				isQuote = true;
				continue;
			}
		}
	
		m_szToken[nCurrIndex++] = c;
	}

	if (nCurrIndex == 0){
		return NULL;
	}

	m_szToken[nCurrIndex] = '\0';


	return m_szToken;
}

void cMyASELoader::ParseBlockMaterialList(){
	int nLevel = 0;

	//vector<cMtlTex*> vecMtlTex;
	int nMtlCount;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_MATERIAL_COUNT))
		{
			nMtlCount = atoi(GetToken());
			m_vecMtl.resize(nMtlCount);
		}
		else if (isEqual(szToken, ID_MATERIAL))
		{
			int nMtlRef = atoi(GetToken());
			cMtlTex* pMtlTex = new cMtlTex;
			m_vecMtl[nMtlRef] = pMtlTex;
			ParseBlockMaterial(pMtlTex);
		}
	} while (nLevel > 0);

#ifdef _DEBUG
	_ASSERT(nMtlCount == m_vecMtl.size()
		&& "Material Count != Matrial Vector Size");
#endif
}

void cMyASELoader::ParseBlockMaterial(cMtlTex* pMtlTex){
	int nLevel = 0;

	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_AMBIENT))
		{
			float x, y, z;
			x = GetFloat();
			y = GetFloat();
			z = GetFloat();
			pMtlTex->stMtl.Ambient.r = x;
			pMtlTex->stMtl.Ambient.g = y;
			pMtlTex->stMtl.Ambient.b = z;
			pMtlTex->stMtl.Ambient.a = 1.0f;
		}
		else if (isEqual(szToken, ID_DIFFUSE))
		{
			float x, y, z;
			x = GetFloat();
			y = GetFloat();
			z = GetFloat();
			pMtlTex->stMtl.Diffuse.r = x;
			pMtlTex->stMtl.Diffuse.g = y;
			pMtlTex->stMtl.Diffuse.b = z;
			pMtlTex->stMtl.Diffuse.a = 1.0f;
		}
		else if (isEqual(szToken, ID_SPECULAR))
		{
			float x, y, z;
			x = GetFloat();
			y = GetFloat();
			z = GetFloat();
			pMtlTex->stMtl.Specular.r = x;
			pMtlTex->stMtl.Specular.g = y;
			pMtlTex->stMtl.Specular.b = z;
			pMtlTex->stMtl.Specular.a = 1.0f;
		}
		else if (isEqual(szToken, ID_MAP_DIFFUSE)){
			ParseMapDiffuse(pMtlTex);
		}
	} while (nLevel > 0);
}

void cMyASELoader::Render(){
#ifdef _DEBUG
	_ASSERT(m_bMeshed && "Mesh Not Loaded");
#endif
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	for (size_t i = 0; i < m_vecMeshs.size(); i++){
		g_pD3DDevice->SetTexture(0, m_vecMtl[m_vecsubSet[i]]->pTex);
		g_pD3DDevice->SetMaterial(&m_vecMtl[m_vecsubSet[i]]->stMtl);
		m_vecMeshs[i]->DrawSubset(m_vecsubSet[i]);
	}
}

void cMyASELoader::ParseMapDiffuse(cMtlTex* pMtlTex){
	int nLevel = 0;
	do{
		char* szToken = GetToken();
		if (isEqual(szToken, "{")){
			++nLevel;
		}
		else if (isEqual(szToken, "}")){
			--nLevel;
		}
		else if (isEqual(szToken, ID_BITMAP))
		{
			char* szFileName = GetToken();
			std::string s = std::string("../Resource/");
			s += "ase/";
			s += szFileName;		
			pMtlTex->pTex = g_pTextureManager->GetTexture(s.c_str());
		}
	} while (nLevel > 0);
}
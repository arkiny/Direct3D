#include "stdafx.h"
#include "cObjectParser.h"

#include <sstream>

using namespace std;

//#include <fstream>
//#include <sstream>
//#include <queue>
//
//using namespace std;

cObjectParser::cObjectParser(const char* fileName)
{
	m_sFileName = fileName;
}

cObjectParser::~cObjectParser()
{
	std::map<std::string, LPDIRECT3DTEXTURE9>::iterator itr = m_mapTextureList.begin();
	while (itr != m_mapTextureList.end()) {
		std::map<std::string, LPDIRECT3DTEXTURE9>::iterator toErase = itr;
		++itr;
		SAFE_RELEASE(toErase->second);
		m_mapTextureList.erase(toErase);
	}
}

void cObjectParser::LoadAndParse(){
	// file ver (C)
	char buffer[1024];
	size_t szbuffer(sizeof(buffer));
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp, m_sFileName.c_str(), "r");

#ifdef _DEBUG
	_ASSERT(!err && "file read err");
#endif
	
	char* mtlPath = new char[1024];
	FiNalObjectInfo ret;
	
	ZeroMemory(&ret.fileName, sizeof(ret.fileName));
	ZeroMemory(&ret.stMTL, sizeof(ret.stMTL));
	ZeroMemory(&ret.m_vecVertex, sizeof(ret.m_vecVertex));

	bool firstflag = false;
	while (!feof(fp)){
		// 줄별로 로딩
		fgets(buffer, szbuffer, fp);
		if (buffer[0] == '#'){
			continue;
		}
		else if (buffer[0] == 'm'){
			sscanf_s(buffer, "%*s %s", mtlPath, szbuffer);
			std::string folder = "../Resource/obj/";
			folder.append(mtlPath);
			LoadMaterial(folder.c_str());
		}
		else if (buffer[0] == 'g'){
			std::string mtln(buffer);
			int i = mtln.size();
			if (firstflag){
				if (mtln.size() == 2 || mtln.size() == 1){
					ret.m_vecVertex = m_vecVertex;
					m_objectInfo.push_back(ret);
					m_vecVertex.clear();
				}
				else {
				}
			}
			firstflag = true;
		}
		else if (buffer[0] == 'v'){
			if (buffer[1] == ' '){
				D3DXVECTOR3 vp;
				sscanf_s(buffer, "%*s %f %f %f", &vp.x, &vp.y, &vp.z);
				m_stObjectInfo.m_vecPoint.push_back(vp);
			}
			else if (buffer[1] == 't'){
				D3DXVECTOR2 vt;
				float dump;
				sscanf_s(buffer, "%*s %f %f %f", &vt.x, &vt.y, &dump);
				m_stObjectInfo.m_vecTexture.push_back(vt);
			}
			else if (buffer[1] == 'n'){
				D3DXVECTOR3 vn;
				sscanf_s(buffer, "%*s %f %f %f", &vn.x, &vn.y, &vn.z);
				m_stObjectInfo.m_vecNormal.push_back(vn);
			}
		}
		else if (buffer[0] == 'u'){
			char* mtlName = new char[1024];
			sscanf_s(buffer, "%*s %s", mtlName, szbuffer);
			std::string mtln(mtlName);
			mtl_t info = m_mtlInfo.at(mtln);

			ret.stMTL = info.stMTL;
			ret.fileName = info.fileName;
			delete[] mtlName;
		}
		else if (buffer[0] == 'f'){
			ST_PNT_VERTEX vertex;
			int vp, vt, vn;
			char d1[10];
			char d2[10];
			char d3[10];
			char d4[10];
			char d5[10];
			char d6[10];
			char d7[10];
			char d8[10];
			char d9[10];

			sscanf(buffer, 
				"%*s %[^'/']/%[^'/']/%[^'/'' '] %[^'/']/%[^'/']/%[^'/'' '] %[^'/']/%[^'/']/%[^'/'' '] ", 
				d1, d2, d3, d4, d5, d6, d7, d8, d9);

			vp = atoi(d1) - 1;
			vt = atoi(d2) - 1;
			vn = atoi(d3) - 1;
			vertex.p = m_stObjectInfo.m_vecPoint[vp];
			vertex.t = m_stObjectInfo.m_vecTexture[vt];
			vertex.n = m_stObjectInfo.m_vecNormal[vn];
			m_vecVertex.push_back(vertex);
			vp = atoi(d4) - 1;
			vt = atoi(d5) - 1;
			vn = atoi(d6) - 1;
			vertex.p = m_stObjectInfo.m_vecPoint[vp];
			vertex.t = m_stObjectInfo.m_vecTexture[vt];
			vertex.n = m_stObjectInfo.m_vecNormal[vn];
			m_vecVertex.push_back(vertex);
			vp = atoi(d7) - 1;
			vt = atoi(d8) - 1;
			vn = atoi(d9) - 1;
			vertex.p = m_stObjectInfo.m_vecPoint[vp];
			vertex.t = m_stObjectInfo.m_vecTexture[vt];
			vertex.n = m_stObjectInfo.m_vecNormal[vn];
			m_vecVertex.push_back(vertex);
		}
		else if (buffer[0] == 's'){
			continue;
		}
	}
	
	fclose(fp);
	delete [] mtlPath;

	// fstream version (c++ fstream library.)
	//fstream read(m_sFileName);
	//// do this until file end
	//string header;
	//// header type for obj file
	//// mtllib : mtllib path
	//// v : vertex point
	//// vt : vertex texture
	//// vn : vertex normal
	//// g : group
	//// usemtl : mtl id
	//// s : ?
	//// f : face (vertexPoint/vertexTexture/VertexNormal)
	//
	//string line;
	//while (!read.eof()){
	//	// get a line
	//	getline(read, line);
	//	// move it to stringstream
	//	stringstream stream(line);
	//	// check header;
	//	stream >> header;

	//	if (header == "mtllib"){
	//		stream >> m_sFileName;
	//	}
	//	else if (header == "g"){
	//		// skip
	//	}
	//	else if (header == "v"){
	//		D3DXVECTOR3 vp;
	//		stream >> vp.x;
	//		stream >> vp.y;
	//		stream >> vp.z;
	//		m_stObjectInfo.m_vecPoint.push_back(vp);
	//	}
	//	else if (header == "vt"){
	//		D3DXVECTOR2 vt;
	//		float femptybuffer;
	//		stream >> vt.x;
	//		stream >> vt.y;
	//		stream >> femptybuffer;
	//		m_stObjectInfo.m_vecTexture.push_back(vt);
	//	}
	//	else if (header == "vn"){
	//		D3DXVECTOR3 vn;
	//		stream >> vn.x;
	//		stream >> vn.y;
	//		stream >> vn.z;
	//		m_stObjectInfo.m_vecNormal.push_back(vn);
	//	}
	//	else if (header == "#"){
	//		// its comment. skip
	//	}
	//	else if (header == "usemtl"){
	//		// @todo mtl info 
	//	}
	//	else if (header == "f"){
	//		ST_PNT_VERTEX vertex;
	//		while (!stream.eof()){
	//			string token, detail;
	//			stream >> token;
	//			stringstream parse(token);
	//			int indexinfo;
	//			getline(parse, detail, '/');
	//			indexinfo = atoi(detail.c_str())-1;
	//			vertex.p = m_stObjectInfo.m_vecPoint[indexinfo];
	//			getline(parse, detail, '/');
	//			indexinfo = atoi(detail.c_str())-1;
	//			vertex.t = m_stObjectInfo.m_vecTexture[indexinfo];
	//			getline(parse, detail, '/');
	//			indexinfo = atoi(detail.c_str())-1;
	//			vertex.n = m_stObjectInfo.m_vecNormal[indexinfo];
	//			m_vecVertex.push_back(vertex);
	//		}
	//	}
	//}
}

void cObjectParser::LoadMaterial(const char* fileName){
	char buffer[1024];
	size_t szbuffer(sizeof(buffer));
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp, fileName, "r");

#ifdef _DEBUG
	_ASSERT(!err && "file read err");
#endif
		
	//LPD3DXMATERIAL pMTL;
	
	mtl_t m;
	while (!feof(fp)){
		// 줄별로 로딩
		fgets(buffer, sizeof(buffer), fp);
		
		if (buffer[0] == '#'){
			continue;
		}
		else if (buffer[0] == 'K'){
			if (buffer[1] == 'a'){
				float r, g, b;
				sscanf_s(buffer, "%*s %f %f %f", &r, &g, &b);
				m.stMTL.Ambient = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if (buffer[1] == 'd'){
				float r, g, b;
				sscanf_s(buffer, "%*s %f %f %f", &r, &g, &b);
				m.stMTL.Diffuse = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if (buffer[1] == 's'){
				float r, g, b;
				sscanf_s(buffer, "%*s %f %f %f", &r, &g, &b);
				m.stMTL.Specular = D3DXCOLOR(r, g, b, 1.0f);
			}
		}
		else if (buffer[0] == 'd'){
			continue;
		}
		else if (buffer[0] == 'N'){
			continue;
		}
		else if (buffer[0] == 'i'){
			continue;
		}
		else if (buffer[0] == 'n'){
			char* mtlName = new char[1024];
			sscanf_s(buffer, "%*s %s", mtlName, szbuffer);
			std::string mtln(mtlName);
			
			m.mtlName = mtln;

			delete[] mtlName;
		}
		else if (buffer[0] == 'm'){
			char* filePath = new char[1024];
			sscanf_s(buffer, "%*s %s", filePath, szbuffer);
			std::string p(filePath);
			delete[] filePath;
			filePath = NULL;

			m.fileName = p;

			//stMTL2.pTextureFilename = filePath;
			//std::wstring fileName(filePath);
			//_tcscpy_s(szProxyAddr, CA2T(internetprotocol.c_str()));
			//#include <atlstr.h>
			//_tcscpy_s(wfilePath, CA2T(p.c_str()));
			//mbstowcs(wfilePath, p.c_str(), p.size());
			//TCHAR* wfilePath = new TCHAR[512];

			TCHAR *param = new TCHAR[p.size() + 1];
			param[p.size()] = 0;
			std::copy(p.begin(), p.end(), param);
			std::wstring wFolder(L"../Resource/obj/");
			std::wstring wPath(param);
			wPath = wFolder + wPath;
			delete[] param;
			param = NULL;
			
			if (m_mapTextureList.count(p) >= 1){
				// already loaded
				LPDIRECT3DTEXTURE9 point = m_mapTextureList.at(p);
				m_mtlInfo.insert(pair<string, mtl_t>(m.mtlName, m));
			}
			else {
				LPDIRECT3DTEXTURE9 pTexture;
				HRESULT hr = D3DXCreateTextureFromFile(
					g_pD3DDevice,
					wPath.c_str(),
					&pTexture);
#ifdef _DEBUG
				_ASSERT(hr == S_OK);
#endif
				m_mapTextureList.insert(
					pair<string, LPDIRECT3DTEXTURE9>(p, pTexture));
				m_mtlInfo.insert(pair<string, mtl_t>(m.mtlName, m));
			}
			
			
		}
	}
}

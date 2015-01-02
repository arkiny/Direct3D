#include "stdafx.h"
#include "cObjectParser.h"

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

	while (!feof(fp)){
		// 줄별로 로딩
		fgets(buffer, sizeof(buffer), fp);
		if (buffer[0] == '#'){
			continue;
		}
		else if (buffer[0] == 'm'){
			sscanf_s(buffer, "%*s %s", mtlPath, szbuffer);
		}
		else if (buffer[0] == 'g'){
			continue;
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
			continue;
			// @todo mtl info 
		}
		else if (buffer[0] == 'f'){
			ST_PNT_VERTEX vertex;
			int vp, vt, vn;
			char d1[sizeof(UINT)];
			char d2[sizeof(UINT)];
			char d3[sizeof(UINT)];
			char d4[sizeof(UINT)];
			char d5[sizeof(UINT)];
			char d6[sizeof(UINT)];
			char d7[sizeof(UINT)];
			char d8[sizeof(UINT)];
			char d9[sizeof(UINT)];

			sscanf(buffer, 
				"%*s %[^'/']/%[^'/']/%[^'/'' '] %[^'/']/%[^'/']/%[^'/'' '] %[^'/']/%[^'/']/%[^'/'' '] ", 
				d1, d2, d3, d4, d5, d6, d7, d8, d9, szbuffer);

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

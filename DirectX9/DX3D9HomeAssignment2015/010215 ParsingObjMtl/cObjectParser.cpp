#include "stdafx.h"
#include "cObjectParser.h"

#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

cObjectParser::cObjectParser(const char* fileName)
{
	m_sFileName = fileName;
}


cObjectParser::~cObjectParser()
{
}

void cObjectParser::LoadAndParse(){
	fstream read(m_sFileName);
	// do this until file end
	string header;
	// header type for obj file
	// mtllib : mtllib path
	// v : vertex point
	// vt : vertex texture
	// vn : vertex normal
	// g : group
	// usemtl : mtl id
	// s : ?
	// f : face (vertexPoint/vertexTexture/VertexNormal)
	
	string line;
	while (!read.eof()){
		// get a line
		getline(read, line);
		// move it to stringstream
		stringstream stream(line);
		// check header;
		stream >> header;

		if (header == "mtllib"){
			stream >> m_sFileName;
		}
		else if (header == "g"){
			// skip
		}
		else if (header == "v"){
			D3DXVECTOR3 vp;
			stream >> vp.x;
			stream >> vp.y;
			stream >> vp.z;
			m_stObjectInfo.m_vecPoint.push_back(vp);
		}
		else if (header == "vt"){
			D3DXVECTOR2 vt;
			float femptybuffer;
			stream >> vt.x;
			stream >> vt.y;
			stream >> femptybuffer;
			m_stObjectInfo.m_vecTexture.push_back(vt);
		}
		else if (header == "vn"){
			D3DXVECTOR3 vn;
			stream >> vn.x;
			stream >> vn.y;
			stream >> vn.z;
			m_stObjectInfo.m_vecNormal.push_back(vn);
		}
		else if (header == "#"){
			// its comment. skip
		}
		else if (header == "usemtl"){
			// @todo mtl info 
		}
		else if (header == "f"){
			ST_PNT_VERTEX vertex;
			while (!stream.eof()){
				string token, detail;
				stream >> token;
				stringstream parse(token);
				int indexinfo;
				getline(parse, detail, '/');
				indexinfo = atoi(detail.c_str())-1;
				vertex.p = m_stObjectInfo.m_vecPoint[indexinfo];
				getline(parse, detail, '/');
				indexinfo = atoi(detail.c_str())-1;
				vertex.t = m_stObjectInfo.m_vecTexture[indexinfo];
				getline(parse, detail, '/');
				indexinfo = atoi(detail.c_str())-1;
				vertex.n = m_stObjectInfo.m_vecNormal[indexinfo];
				m_vecVertex.push_back(vertex);
			}
		}
	}
}

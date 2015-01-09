#include "stdafx.h"
#include <fstream>

#include "cASEModelLoader.h"
#include "cMtlTex.h"

using namespace std;
cASEModelLoader::cASEModelLoader()
{
}


cASEModelLoader::~cASEModelLoader()
{
	for (auto p : vecMeshs){
		SAFE_RELEASE(p);
	}
	for (auto p : vecMeshInfo){
		delete p;
	}
}

void cASEModelLoader::LoadMesh(std::string& sFolder){
	m_vecMtlTex.clear();
	
	fstream file;
	file.open(sFolder.c_str());

	char buffer[1024];
	
	while (!file.eof()){
		file.getline(buffer, sizeof(buffer));
		stringstream aLine(buffer);
		string token;
		aLine >> token;
		if (token == "*3DSMAX_ASCIIEXPORT" 
			|| token == "*COMMENT"){
			//skip
		}
		else if (token == "*SCENE"){
			SkipUntilTokenEnd(file);
		}
		else if (token == "*MATERIAL_LIST"){
			ASE_MaterialList(file);
		}
		else if (token == "*GEOMOBJECT"){
			ASE_GEOMOBJECT(file);
		}
	}

	file.close();


	for (int j = 0; j < vecMeshInfo.size(); j++){
		LPD3DXMESH pMesh = NULL;

		HRESULT hr = D3DXCreateMeshFVF(vecMeshInfo[j]->vecVertex.size() / 3,
			vecMeshInfo[j]->vecVertex.size(),
			D3DXMESH_MANAGED,
			ST_PNT_VERTEX::FVF,
			g_pD3DDevice,
			&pMesh);

		ST_PNT_VERTEX* pV = NULL;
		pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
		memcpy(pV, &vecMeshInfo[j]->vecVertex[0], vecMeshInfo[j]->vecVertex.size() * sizeof(ST_PNT_VERTEX));
		pMesh->UnlockVertexBuffer();

		WORD* pI = NULL;
		pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
		for (size_t i = 0; i < pMesh->GetNumVertices()  ; ++i)
		{
			pI[i] = i;
		}
		pMesh->UnlockIndexBuffer();

		DWORD* pA = NULL;
		pMesh->LockAttributeBuffer(0, &pA);
		for (size_t i = 0; i < pMesh->GetNumFaces(); i++){
			pA[i] = vecMeshInfo[j]->ref;
		}	
		pMesh->UnlockAttributeBuffer();

		std::vector<DWORD> vecAdjBuffer(vecMeshInfo[j]->vecVertex.size());
		pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

		pMesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT |
			D3DXMESHOPT_COMPACT |
			D3DXMESHOPT_VERTEXCACHE,
			&vecAdjBuffer[0], 0, 0, 0);

		vecMeshs.push_back(pMesh);
	}
}

void cASEModelLoader::ASE_GEOMOBJECT(std::fstream& file){
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<D3DXVECTOR3>	vecVN;
	//std::vector<ST_PNT_VERTEX>	vecVertex;
	int nVer, nFace, nTVertex, nTFace;
	stMeshInfo* info = new stMeshInfo;
	info->ref = INT_MAX;
	string token = "";
	char buffer[1024];
	stringstream aLine;
	while (token != "}"){
		file.getline(buffer, sizeof(buffer));
		aLine = stringstream(buffer);
		aLine >> token;
		if (token == "*NODE_TM" || token == "*NODE_NAME" || token == "*WIREFRAME_COLOR"){
			SkipUntilTokenEnd(file);
		}
		else if (token == "*TM_ANIMATION"){
			while (buffer[1] != '}'){
				file.getline(buffer, sizeof(buffer));
				aLine = stringstream(buffer);
				aLine >> token;
			}
			file.getline(buffer, sizeof(buffer));
			aLine = stringstream(buffer);
			aLine >> token;
			if (token == "*MATERIAL_REF"){
				aLine >> token;
				if (info->ref == 0){
					int a = 0; // hit
				}
				info->ref = atoi(token.c_str());
				vecAttrID.push_back(info->ref);
				vecMeshInfo.push_back(info);
				info = new stMeshInfo;
			}

		}
		else if (token == "*MATERIAL_REF"){			
			aLine >> token;
			info->ref = atoi(token.c_str());
			if (info->ref == 0){
				int a = 0; // hit
			}
			vecAttrID.push_back(info->ref);			
			vecMeshInfo.push_back(info);
			
			info = new stMeshInfo;
		}
		else if (token == "*MESH")
		{
			file.getline(buffer, sizeof(buffer));
			aLine = stringstream(buffer);
			aLine >> token;
			while (token != "}")
			{				

				if (token == "*TIMEVALUE"){
					file.getline(buffer, sizeof(buffer));
					aLine = stringstream(buffer);
					aLine >> token;
				}				
				else if (token == "*MESH_NUMVERTEX"){
					aLine >> token;
					nVer = atoi(token.c_str());
				}
				else if (token == "*MESH_NUMFACES"){
					aLine >> token;
					nFace = atoi(token.c_str());
				}
				else if (token == "*MESH_NUMTVERTEX"){
					aLine >> token;
					nTVertex = atoi(token.c_str());
				}
				else if (token == "*MESH_VERTEX_LIST"){
					vecV.clear();
					while (token != "}"){
						file.getline(buffer, sizeof(buffer));
						aLine = stringstream(buffer);
						aLine >> token; //*MESH_VERTEX
						if (token == "}") break;
						aLine >> token; // num

						float x, y, z;
						D3DXVECTOR3 vertexP;
						aLine >> token;
						x = static_cast<float>(atof(token.c_str()));
						aLine >> token;
						z = static_cast<float>(atof(token.c_str()));
						aLine >> token;
						vertexP.z;
						y = static_cast<float>(atof(token.c_str()));

						vertexP.x = x;
						vertexP.y = y;
						vertexP.z = z;
						vecV.push_back(vertexP);						
					}
					assert(vecV.size() == nVer);
					file.getline(buffer, sizeof(buffer));
					aLine = stringstream(buffer);
					aLine >> token;
				}
				else if (token == "*MESH_FACE_LIST"){
					info->vecVertex.clear();
					while (token != "}"){
						file.getline(buffer, sizeof(buffer));
						aLine = stringstream(buffer);
						aLine >> token; //*MESH_FACE 
						if (token == "}") break;
						aLine >> token; // num
						aLine >> token; // A:
						aLine >> token; // 0
						
						ST_PNT_VERTEX vA, vB, vC;
						vA.p = vecV[atoi(token.c_str())];
						
						
						aLine >> token; // C:
						aLine >> token; // 0
						vC.p = vecV[atoi(token.c_str())];
												
						aLine >> token; // B:
						aLine >> token; // 0
						vB.p = vecV[atoi(token.c_str())];

						info->vecVertex.push_back(vA);
						info->vecVertex.push_back(vB);
						info->vecVertex.push_back(vC);
						
					}
					assert(info->vecVertex.size()/3 == nFace);
					vecV.clear();
					file.getline(buffer, sizeof(buffer));
					aLine = stringstream(buffer);
					aLine >> token;
				}
				else if (token == "*MESH_TVERTLIST"){
					vecVT.clear();
					while (token != "}"){
						file.getline(buffer, sizeof(buffer));
						aLine = stringstream(buffer);
						aLine >> token; //*MESH_VERTEX
						if (token == "}") break;
						aLine >> token; // num

						D3DXVECTOR2 vertexT;
						aLine >> token;
						vertexT.x = static_cast<float>(atof(token.c_str()));
						aLine >> token;
						vertexT.y = 1.0f - static_cast<float>(atof(token.c_str()));
						vecVT.push_back(vertexT);
					}
					assert(vecVT.size() == nTVertex);
				
					file.getline(buffer, sizeof(buffer));
					aLine = stringstream(buffer);
					aLine >> token;
				}
				else if (token == "*MESH_TFACELIST"){
					int index = 0;
					while (token != "}"){
						file.getline(buffer, sizeof(buffer));
						aLine = stringstream(buffer);
						aLine >> token; //*MESH_FACE 
						if (token == "}") break;
						aLine >> token; // num

						//int index = atoi(token.c_str());

						D3DXVECTOR2 a, b, c;
						

						aLine >> token; // A 0
						a = vecVT[atoi(token.c_str())];

						aLine >> token; // C 0
						c = vecVT[atoi(token.c_str())];

						aLine >> token; // B 0
						b = vecVT[atoi(token.c_str())];

						info->vecVertex[index].t = a;
						index++;
						info->vecVertex[index].t = b;
						index++;
						info->vecVertex[index].t = c;
						index++;
					}
					vecVT.clear();
					file.getline(buffer, sizeof(buffer));
					aLine = stringstream(buffer);
					aLine >> token;
				}
				else if (token == "*MESH_NORMALS"){
					while (token != "}"){
						file.getline(buffer, sizeof(buffer));
						aLine = stringstream(buffer);
						aLine >> token; //*MESH_FACE 
						if (token == "}") break;
						int index = 0;
						if (token == "*MESH_VERTEXNORMAL"){
							D3DXVECTOR3 normal;
							aLine >> token; // num
							aLine >> token;
							normal.x = static_cast<float>(atof(token.c_str()));
							
							aLine >> token;
							normal.z = static_cast<float>(atof(token.c_str()));
							
							aLine >> token;
							normal.y = static_cast<float>(atof(token.c_str()));
							
							info->vecVertex[index].n = normal;
							index++;
						}
					}	
					file.getline(buffer, sizeof(buffer));
					aLine = stringstream(buffer);
					aLine >> token;
				}
				else {
					file.getline(buffer, sizeof(buffer));
					aLine = stringstream(buffer);
					aLine >> token;
				}
			}
			file.getline(buffer, sizeof(buffer));
			aLine = stringstream(buffer);
			aLine >> token;
		}	
		else{
			file.getline(buffer, sizeof(buffer));
			if(buffer[0] == '}'){
				if (info->ref == INT_MAX){
					delete info;
					info = new stMeshInfo;
				}
			}			
			aLine = stringstream(buffer);
			aLine >> token;
		}		
	}

	
	// °ýÈ£ ´Ý±â
	file.getline(buffer, sizeof(buffer));
	while (buffer[0] != '}'){
		if (file.eof()) break;
		file.getline(buffer, sizeof(buffer));		
	}
}

void cASEModelLoader::ASE_MaterialList(std::fstream& file){
	string token = "";
	char buffer[1024];
	while (token != "}"){		
		file.getline(buffer, sizeof(buffer));
		stringstream aLine(buffer);
		aLine >> token;
		if (token == "*MATERIAL_COUNT"){
			aLine >> token;
			m_vecMtlTex.resize(atoi(token.c_str()));
		}
		else if (token == "*MATERIAL"){
			while (token != "}"){				
				int i = atoi(token.c_str());
				m_vecMtlTex[i] = (ASE_Material(file));
				file.getline(buffer, sizeof(buffer));
				stringstream aLine(buffer);
				aLine >> token;
				if (token != "*MATERIAL") break;
				aLine >> token;
			}
		}
	}
}

cMtlTex* cASEModelLoader::ASE_Material(std::fstream& file){
	string token = "";
	cMtlTex* ret = new cMtlTex;
	stringstream aLine;
	char buffer[1024];
	while (token != "}"){	
		file.getline(buffer, sizeof(buffer));
		aLine = stringstream(buffer);
		aLine >> token;
		if (token == "*MATERIAL_AMBIENT"){
			aLine >> token;
			float x = static_cast<float>(atof(token.c_str()));
			aLine >> token;
			float y = static_cast<float>(atof(token.c_str()));
			aLine >> token;
			float z = static_cast<float>(atof(token.c_str()));

			ret->stMtl.Ambient.r = x;
			ret->stMtl.Ambient.g = y;
			ret->stMtl.Ambient.b = z;
			ret->stMtl.Ambient.a = 1.0f;
		}
		else if (token == "*MATERIAL_DIFFUSE"){
			aLine >> token;
			float x = static_cast<float>(atof(token.c_str()));
			aLine >> token;
			float y = static_cast<float>(atof(token.c_str()));
			aLine >> token;
			float z = static_cast<float>(atof(token.c_str()));

			ret->stMtl.Diffuse.r = x;
			ret->stMtl.Diffuse.g = y;
			ret->stMtl.Diffuse.b = z;
			ret->stMtl.Diffuse.a = 1.0f;
		}
		else if (token == "*MATERIAL_SPECULAR"){
			aLine >> token;
			float x = static_cast<float>(atof(token.c_str()));
			aLine >> token;
			float y = static_cast<float>(atof(token.c_str()));
			aLine >> token;
			float z = static_cast<float>(atof(token.c_str()));

			ret->stMtl.Specular.r = x;
			ret->stMtl.Specular.g = y;
			ret->stMtl.Specular.b = z;
			ret->stMtl.Specular.a = 1.0f;
		}
		else if (token == "*MAP_DIFFUSE"){
			
			while (token != "*BITMAP"){
				file.getline(buffer, sizeof(buffer));
				aLine = stringstream(buffer);
				//aLine(buffer);
				aLine >> token;
			}

			aLine >> token;
			token.erase(0, 1);
			token.erase(token.size() - 1);
			string s = RESOURCE_FOLDER;
			s += "ase/";
			//s += "ase/woman/hair_woman_01.jpg";
			//token.erase(0, 2);
			s += token;
			ret->pTex = g_pTextureManager->GetTexture(s);
		}
	}
	file.getline(buffer, sizeof(buffer));
	aLine = stringstream(buffer);
	aLine >> token;
	return ret;
}

void cASEModelLoader::SkipUntilTokenEnd(fstream& file){
	string token = "";
	while (token != "}"){
		char buffer[1024];
		file.getline(buffer, sizeof(buffer));
		stringstream aLine(buffer);
		aLine >> token;
	}
}
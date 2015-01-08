#pragma once
//#include <functional>
#include <sstream>

class cMtlTex;
class cGroup;

typedef struct {
	int						vertexNum[3];
	int						tVertexNum[3];
	D3DXVECTOR3				faceNormal;
	D3DXVECTOR3				vertexNormals[3];
	D3DXCOLOR				vertexColors[3][4];
} aseFace_t;

typedef struct {
	int						timeValue;

	int						numVertexes;
	int						numTVertexes;
	int						numCVertexes;
	int						numFaces;
	int						numTVFaces;
	int						numCVFaces;

	D3DXVECTOR3				transform[4];			// applied to normals

	bool					colorsParsed;
	bool					normalsParsed;
	D3DXVECTOR3 *			vertexes;
	D3DXVECTOR2 *			tvertexes;
	D3DXVECTOR3 *			cvertexes;
	aseFace_t *				faces;
} aseMesh_t;

typedef struct {
	UINT					number;
	std::string				name;
	float					uOffset, vOffset;		// max lets you offset by material without changing texCoords
	float					uTiling, vTiling;		// multiply tex coords by this
	float					angle;					// in clockwise radians
	

} aseMaterial_t;

typedef struct {
	std::string				name;
	int						materialRef;

	aseMesh_t				mesh;

	// frames are only present with animations
	std::vector<aseMesh_t*>		frames;			// aseMesh_t
} aseObject_t;

typedef struct aseModel_s {
	time_t							timeStamp;
	std::vector<cMtlTex *>			materials;
	std::vector<aseObject_t *>		objects;
} aseModel_t;

typedef struct {
	const char	*buffer;
	const char	*curpos;
	int			len;
	std::string	token;

	bool	verbose;

	aseModel_t	*model;
	aseObject_t	*currentObject;
	aseMesh_t	*currentMesh;
	//aseMaterial_t	*currentMaterial;

	cMtlTex			*currentcMtlTex;

	int			currentFace;
	int			currentVertex;
} ase_t;

class cASELoader
{
private:
	std::map<std::string, cMtlTex*> m_mapMtlTex;
	ase_t ase;
	std::vector<cMtlTex*> m_vecMtlTex;


	std::stringstream m_ssBuf;

private:
	aseMesh_t* ASE_GetCurrentMesh(){
		return ase.currentMesh;
	}

	bool CharIsTokenDelimiter(int ch){
		if (ch <= 32)
			return 1;
		return 0;
	}

	int ASE_GetToken(bool restOfLine);
	void ASE_ParseBlock(cASELoader* pc, void(cASELoader::*callback)(const char* token));
	void ASE_SkipEnclosingBraces();
	void ASE_SkipRestOfLine(){
		ASE_GetToken(true);
	}
	void ASE_KeyMAP_DIFFUSE(const char *token);
	void ASE_KeyMATERIAL(const char *token);
	void ASE_KeyMATERIAL_LIST(const char *token);
	void ASE_KeyMESH_VERTEX_LIST(const char *token);
	void ASE_KeyMESH_FACE_LIST(const char *token);
	void ASE_KeyTFACE_LIST(const char *token);
	void ASE_KeyCFACE_LIST(const char *token);
	void ASE_KeyMESH_TVERTLIST(const char *token);
	void ASE_KeyMESH_CVERTLIST(const char *token);
	void ASE_KeyMESH_NORMALS(const char *token);
	void ASE_KeyMESH(const char *token);
	void ASE_KeyMESH_ANIMATION(const char *token);
	void ASE_KeyGEOMOBJECT(const char *token);
	void ASE_ParseGeomObject();
	void ASE_KeyGROUP(const char *token);

public:
	cASELoader();
	~cASELoader();



	LPD3DXMESH LoadMesh(std::vector<cMtlTex*>& vecMtlTex, std::string& sFolder, std::string& sFileName);
	aseModel_t* ASE_Parse(const char *buffer);
	aseModel_t* ASE_Load(const char *fileName);
	void destroy();
};
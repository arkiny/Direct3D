#include "stdafx.h"
#include <fstream>
#include <sstream>
#include "cASELoader.h"
#include "cMtlTex.h"
#include "Asciitok.h"

using namespace std;

cASELoader::cASELoader()
{
}


cASELoader::~cASELoader()
{
}


void cASELoader::destroy(){

}

int cASELoader::ASE_GetToken(bool restOfLine){
	if (m_ssBuf.eof()) return 0;
	if (ase.buffer == 0) return 0;

	if (restOfLine){
		string dump;
		m_ssBuf.ignore(256, '\n');
	}	
	else if (m_ssBuf.peek() == '"'){
		while (ase.token.c_str()[ase.token.size() - 1] == '"'){
			m_ssBuf >> ase.token;
		}
		ase.token.erase(0, 1); // erase the first character
		ase.token.erase(ase.token.size() - 1); // erase the last character
	}
	else{
		m_ssBuf >> ase.token;
	}

	return 1;
}

//void(cASELoader::*FunctionPointer)(const char* token)
void cASELoader::ASE_ParseBlock(cASELoader* pc, void(cASELoader::*callback)(const char* token))
{
	ASE_GetToken(false); // remove opener
	while (ase.token != "}")
	{
		ASE_GetToken(false);
		if (pc && callback)
			(pc->*callback)(ase.token.c_str());
	}
	//int a;
	//ASE_GetToken(false);
}

void cASELoader::ASE_SkipEnclosingBraces(){
	int indent = 0;
	string dump;
	while (ase.token != "}"){
		m_ssBuf >> ase.token;
	}
}

void cASELoader::ASE_KeyMAP_DIFFUSE(const char *token){
	aseMaterial_t	*material;

	if (!strcmp(token, "*BITMAP"))
	{
		string	path;
		string	matname;

		
		ASE_GetToken(false);
		matname = ase.token.c_str();

		// remove the quotes
		if (ase.token.c_str()[0] == '"') {
			ase.token.erase(0, 1); // erase the first character
			ase.token.erase(ase.token.size() - 1); // erase the last character
		}

		ase.currentcMtlTex->pTex = g_pTextureManager->GetTexture(ase.token);
	}	
	else
	{
	}
}

void cASELoader::ASE_KeyMATERIAL(const char *token){
	if (!strcmp(token, "*MAP_DIFFUSE"))
	{
		ASE_ParseBlock(this, &cASELoader::ASE_KeyMAP_DIFFUSE);
	}
	else if (!strcmp(token, "*MATERIAL_AMBIENT")){
		ASE_GetToken(false);
		float x = atof(ase.token.c_str());
		ASE_GetToken(false);
		float y = atof(ase.token.c_str());
		ASE_GetToken(false);
		float z = atof(ase.token.c_str());;

		ase.currentcMtlTex->stMtl.Ambient.r = x;
		ase.currentcMtlTex->stMtl.Ambient.g = y;
		ase.currentcMtlTex->stMtl.Ambient.b = z;
		ase.currentcMtlTex->stMtl.Ambient.a = 1.0f;
	}
	else if (!strcmp(token, "*MATERIAL_DIFFUSE")){
		ASE_GetToken(false);
		float x = atof(ase.token.c_str());
		ASE_GetToken(false);
		float y = atof(ase.token.c_str());
		ASE_GetToken(false);
		float z = atof(ase.token.c_str());;

		ase.currentcMtlTex->stMtl.Diffuse.r = x;
		ase.currentcMtlTex->stMtl.Diffuse.g = y;
		ase.currentcMtlTex->stMtl.Diffuse.b = z;
		ase.currentcMtlTex->stMtl.Diffuse.a = 1.0f;
	}
	else if (!strcmp(token, "*MATERIAL_SPECULAR")){
		ASE_GetToken(false);
		float x = atof(ase.token.c_str());
		ASE_GetToken(false);
		float y = atof(ase.token.c_str());
		ASE_GetToken(false);
		float z = atof(ase.token.c_str());;

		ase.currentcMtlTex->stMtl.Specular.r = x;
		ase.currentcMtlTex->stMtl.Specular.g = y;
		ase.currentcMtlTex->stMtl.Specular.b = z;
		ase.currentcMtlTex->stMtl.Specular.a = 1.0f;
	}
	else
	{
	}	
}

void cASELoader::ASE_KeyMATERIAL_LIST(const char *token){
	if (!strcmp(token, "*MATERIAL_COUNT"))
	{
		ASE_GetToken(false);
	}
	else if (!strcmp(token, "*MATERIAL"))
	{
		ase.currentcMtlTex = new cMtlTex;
		ASE_GetToken(false);
		ase.currentcMtlTex->m_nAttrId = atoi(ase.token.c_str());
		m_vecMtlTex.push_back(ase.currentcMtlTex);
		ase.model->materials.push_back(ase.currentcMtlTex);
		ASE_ParseBlock(this, &cASELoader::ASE_KeyMATERIAL);
	}
}

//void cASELoader::ASE_KeyNODE_TM(const char *token){
//
//}

void cASELoader::ASE_KeyMESH_VERTEX_LIST(const char *token){
	aseMesh_t *pMesh = ASE_GetCurrentMesh();

	if (!strcmp(token, "*MESH_VERTEX"))
	{
		ASE_GetToken(false);		// skip number

		ASE_GetToken(false);
		pMesh->vertexes[ase.currentVertex].x = static_cast<float>(atof(ase.token.c_str()));

		ASE_GetToken(false);
		pMesh->vertexes[ase.currentVertex].y = static_cast<float>(atof(ase.token.c_str()));

		ASE_GetToken(false);
		pMesh->vertexes[ase.currentVertex].z = static_cast<float>(atof(ase.token.c_str()));

		ase.currentVertex++;

		//ase.currentVertex > pMesh->numVertexes

		assert(ase.currentVertex <= pMesh->numVertexes 
			&& "ase.currentVertex >= pMesh->numVertexes");
		
	}
	else
	{
		string out = "Unknown token while parsing MESH_VERTEX_LIST : ";
		out += token;
		assert(false &&  out.c_str());	
	}
}

void cASELoader::ASE_KeyMESH_FACE_LIST(const char *token){
	aseMesh_t *pMesh = ASE_GetCurrentMesh();

	if (!strcmp(token, "*MESH_FACE"))
	{
		ASE_GetToken(false);	// skip face number

		// we are flipping the order here to change the front/back facing
		// from 3DS to our standard (clockwise facing out)
		ASE_GetToken(false);	// skip label
		ASE_GetToken(false);	// first vertex
		pMesh->faces[ase.currentFace].vertexNum[0] = atoi(ase.token.c_str());

		ASE_GetToken(false);	// skip label
		ASE_GetToken(false);	// second vertex
		pMesh->faces[ase.currentFace].vertexNum[2] = atoi(ase.token.c_str());

		ASE_GetToken(false);	// skip label
		ASE_GetToken(false);	// third vertex
		pMesh->faces[ase.currentFace].vertexNum[1] = atoi(ase.token.c_str());

		ASE_GetToken(true);

		// we could parse material id and smoothing groups here
		/*
		if ( ( p = strstr( ase.token.c_str(), "*MESH_MTLID" ) ) != 0 )
		{
		p += strlen( "*MESH_MTLID" ) + 1;
		mtlID = atoi( p );
		}
		else
		{
		common->Error( "No *MESH_MTLID found for face!" );
		}
		*/

		ase.currentFace++;
	}
	else
	{
		string out = "Unknown token while parsing MESH_FACE_LIST : ";
		out += token;
		assert(false && out.c_str());
	}
}

void cASELoader::ASE_KeyTFACE_LIST(const char *token){
	aseMesh_t *pMesh = ASE_GetCurrentMesh();

	if (!strcmp(token, "*MESH_TFACE"))
	{
		int a, b, c;

		ASE_GetToken(false);

		ASE_GetToken(false);
		a = atoi(ase.token.c_str());
		ASE_GetToken(false);
		c = atoi(ase.token.c_str());
		ASE_GetToken(false);
		b = atoi(ase.token.c_str());

		pMesh->faces[ase.currentFace].tVertexNum[0] = a;
		pMesh->faces[ase.currentFace].tVertexNum[1] = b;
		pMesh->faces[ase.currentFace].tVertexNum[2] = c;

		ase.currentFace++;
	}
	else
	{
		string out = "UnknoASE_KeyMESH_TVERTLISTwn token while parsing TFACE_LIST : ";
		out += token;
		assert(false && out.c_str());
	}
}

void cASELoader::ASE_KeyCFACE_LIST(const char *token){
	aseMesh_t *pMesh = ASE_GetCurrentMesh();

	if (!strcmp(token, "*MESH_CFACE"))
	{
		ASE_GetToken(false);

		for (int i = 0; i < 3; i++) {
			ASE_GetToken(false);
			int a = atoi(ase.token.c_str());

			// we flip the vertex order to change the face direction to our style
			static int remap[3] = { 0, 2, 1 };
			pMesh->faces[ase.currentFace].vertexColors[remap[i]][0] = pMesh->cvertexes[a][0] * 255;
			pMesh->faces[ase.currentFace].vertexColors[remap[i]][1] = pMesh->cvertexes[a][1] * 255;
			pMesh->faces[ase.currentFace].vertexColors[remap[i]][2] = pMesh->cvertexes[a][2] * 255;
		}

		ase.currentFace++;
	}
	else
	{
		string out = "Unknown token while parsing MESH_CFACE : ";
		out += token;
		assert(false && out.c_str());
	}
}

void cASELoader::ASE_KeyMESH_TVERTLIST(const char *token){
	aseMesh_t *pMesh = ASE_GetCurrentMesh();

	if (!strcmp(token, "*MESH_TVERT"))
	{
		char u[80], v[80], w[80];

		ASE_GetToken(false);

		ASE_GetToken(false);
		strcpy(u, ase.token.c_str());

		ASE_GetToken(false);
		strcpy(v, ase.token.c_str());

		ASE_GetToken(false);
		strcpy(w, ase.token.c_str());

		pMesh->tvertexes[ase.currentVertex].x = atof(u);
		// our OpenGL second texture axis is inverted from MAX's sense
		pMesh->tvertexes[ase.currentVertex].y = 1.0f - atof(v);

		ase.currentVertex++;

		assert(ase.currentVertex <= pMesh->numTVertexes 
			&& "ase.currentVertex > pMesh->numTVertexes");
		
	}
	else
	{
		assert(false && "unknown token");
	}
}

void cASELoader::ASE_KeyMESH_CVERTLIST(const char *token){
	aseMesh_t *pMesh = ASE_GetCurrentMesh();

	pMesh->colorsParsed = true;

	if (!strcmp(token, "*MESH_VERTCOL"))
	{
		ASE_GetToken(false);

		ASE_GetToken(false);
		pMesh->cvertexes[ase.currentVertex][0] = static_cast<float>(atof(token));

		ASE_GetToken(false);
		pMesh->cvertexes[ase.currentVertex][1] = static_cast<float>(atof(token));

		ASE_GetToken(false);
		pMesh->cvertexes[ase.currentVertex][2] = static_cast<float>(atof(token));

		ase.currentVertex++;

		assert(ase.currentVertex > pMesh->numVertexes
			&& "ase.currentVertex >= pMesh->numVertexes");
	}
	else {
		string out = "Unknown token while parsing MESH_CVERTLIST : ";
		out += token;
		assert(false && out.c_str());
	}
}

void cASELoader::ASE_KeyMESH_NORMALS(const char *token)
{
	aseMesh_t	*pMesh = ASE_GetCurrentMesh();
	aseFace_t	*f;
	D3DXVECTOR3	n;

	pMesh->normalsParsed = true;
	f = &pMesh->faces[ase.currentFace];

	if (!strcmp(token, "*MESH_FACENORMAL"))
	{
		int	num;

		ASE_GetToken(false);
		num = atoi(ase.token.c_str());

		assert((num < pMesh->numFaces || num >= 0) && "MESH_NORMALS face index out of range");
		assert(num == ase.currentFace && "MESH_NORMALS face index != currentFace");

		ASE_GetToken(false);
		n[0] = static_cast<float>(atof(ase.token.c_str()));
		ASE_GetToken(false);
		n[1] = static_cast<float>(atof(ase.token.c_str()));
		ASE_GetToken(false);
		n[2] = static_cast<float>(atof(ase.token.c_str()));

		f->faceNormal[0] = n[0] * pMesh->transform[0][0] + n[1] * pMesh->transform[1][0] + n[2] * pMesh->transform[2][0];
		f->faceNormal[1] = n[0] * pMesh->transform[0][1] + n[1] * pMesh->transform[1][1] + n[2] * pMesh->transform[2][1];
		f->faceNormal[2] = n[0] * pMesh->transform[0][2] + n[1] * pMesh->transform[1][2] + n[2] * pMesh->transform[2][2];
		
		D3DXVec3Normalize(&f->faceNormal, &f->faceNormal);
		ase.currentFace++;
	}
	else if (!strcmp(token, "*MESH_VERTEXNORMAL"))
	{
		int	num;
		int	v;

		ASE_GetToken(false);
		num = atoi(ase.token.c_str());
		assert((num < pMesh->numFaces || num >= 0) && "MESH_NORMALS face index out of range");


		f = &pMesh->faces[ase.currentFace - 1];

		for (v = 0; v < 3; v++) {
			if (num == f->vertexNum[v]) {
				break;
			}
		}

		assert(v != 3 && "MESH_NORMALS vertex index doesn't match face");

		ASE_GetToken(false);
		n[0] = static_cast<float>(atof(ase.token.c_str()));
		ASE_GetToken(false);
		n[1] = static_cast<float>(atof(ase.token.c_str()));
		ASE_GetToken(false);
		n[2] = static_cast<float>(atof(ase.token.c_str()));

		f->vertexNormals[v][0] = n[0] * pMesh->transform[0][0] + n[1] * pMesh->transform[1][0] + n[2] * pMesh->transform[2][0];
		f->vertexNormals[v][1] = n[0] * pMesh->transform[0][1] + n[1] * pMesh->transform[1][1] + n[2] * pMesh->transform[2][1];
		f->vertexNormals[v][2] = n[0] * pMesh->transform[0][2] + n[1] * pMesh->transform[1][2] + n[2] * pMesh->transform[2][2];

		D3DXVec3Normalize(&f->faceNormal, &f->faceNormal);
	}
}


void cASELoader::ASE_KeyMESH(const char *token)
{
	aseMesh_t *pMesh = ASE_GetCurrentMesh();

	if (!strcmp(token, "*TIMEVALUE"))
	{
		ASE_GetToken(false);

		pMesh->timeValue = atoi(ase.token.c_str());
	}
	else if (!strcmp(token, "*MESH_NUMVERTEX"))
	{
		ASE_GetToken(false);

		pMesh->numVertexes = atoi(ase.token.c_str());
	}
	else if (!strcmp(token, "*MESH_NUMTVERTEX"))
	{
		ASE_GetToken(false);

		pMesh->numTVertexes = atoi(ase.token.c_str());
	}
	else if (!strcmp(token, "*MESH_NUMCVERTEX"))
	{
		ASE_GetToken(false);

		pMesh->numCVertexes = atoi(ase.token.c_str());
	}
	else if (!strcmp(token, "*MESH_NUMFACES"))
	{
		ASE_GetToken(false);

		pMesh->numFaces = atoi(ase.token.c_str());
	}
	else if (!strcmp(token, "*MESH_NUMTVFACES"))
	{
		ASE_GetToken(false);

		pMesh->numTVFaces = atoi(ase.token.c_str());

		assert(pMesh->numTVFaces == pMesh->numFaces && "MESH_NUMTVFACES != MESH_NUMFACES");

	}
	else if (!strcmp(token, "*MESH_NUMCVFACES"))
	{
		ASE_GetToken(false);

		pMesh->numCVFaces = atoi(ase.token.c_str());

		assert(pMesh->numTVFaces == pMesh->numFaces && "MESH_NUMTVFACES != MESH_NUMFACES");
	}
	else if (!strcmp(token, "*MESH_VERTEX_LIST"))
	{
		pMesh->vertexes = new D3DXVECTOR3[pMesh->numVertexes];

		ase.currentVertex = 0;
		ASE_ParseBlock(this, &cASELoader::ASE_KeyMESH_VERTEX_LIST);
	}
	else if (!strcmp(token, "*MESH_TVERTLIST"))
	{
		ase.currentVertex = 0;
		pMesh->tvertexes = new D3DXVECTOR2[pMesh->numTVertexes];
		ASE_ParseBlock(this, &cASELoader::ASE_KeyMESH_TVERTLIST);
	}
	else if (!strcmp(token, "*MESH_CVERTLIST"))
	{
		ase.currentVertex = 0;
		pMesh->cvertexes = new D3DXVECTOR3[pMesh->numCVertexes];
		ASE_ParseBlock(this, &cASELoader::ASE_KeyMESH_CVERTLIST);
	}
	else if (!strcmp(token, "*MESH_FACE_LIST"))
	{
		pMesh->faces = new aseFace_t[pMesh->numFaces];
		ase.currentFace = 0;
		ASE_ParseBlock(this, &cASELoader::ASE_KeyMESH_FACE_LIST);
	}
	else if (!strcmp(token, "*MESH_TFACELIST"))
	{
		assert(pMesh->faces && "*MESH_TFACELIST before *MESH_FACE_LIST");

		ase.currentFace = 0;
		ASE_ParseBlock(this, &cASELoader::ASE_KeyTFACE_LIST);
	}
	else if (!strcmp(token, "*MESH_CFACELIST"))
	{
		assert(pMesh->faces && "*MESH_CFACELIST before *MESH_FACE_LIST");
		ase.currentFace = 0;
		ASE_ParseBlock(this, &cASELoader::ASE_KeyCFACE_LIST);
	}
	else if (!strcmp(token, "*MESH_NORMALS"))
	{
		assert(pMesh->faces && "*MESH_NORMALS before *MESH_FACE_LIST");
		ase.currentFace = 0;
		ASE_ParseBlock(this, &cASELoader::ASE_KeyMESH_NORMALS);
	}
}

void cASELoader::ASE_KeyMESH_ANIMATION(const char *token)
{
	aseMesh_t *mesh;

	// loads a single animation frame
	if (!strcmp(token, "*MESH"))
	{
		//VERBOSE(("...found MESH\n"));

		mesh = new aseMesh_t;
		memset(mesh, 0, sizeof(aseMesh_t));
		ase.currentMesh = mesh;

		ase.currentObject->frames.push_back(mesh);

		ASE_ParseBlock(this, &cASELoader::ASE_KeyMESH);
	}
	else
	{
		assert(false && "Unknown token while parsing MESH_ANIMATION");
	}
}

void cASELoader::ASE_KeyGEOMOBJECT(const char *token)
{
	aseObject_t	*object;

	object = ase.currentObject;

	if (!strcmp(token, "*NODE_NAME"))
	{
		ASE_GetToken(true);
		//VERBOSE((" %s\n", ase.token.c_str()));
		object->name = ase.token.c_str();
	}
	else if (!strcmp(token, "*NODE_PARENT"))
	{
		ASE_SkipRestOfLine();
	}
	// ignore unused data blocks
	else if (!strcmp(token, "*NODE_TM") ||
		!strcmp(token, "*TM_ANIMATION"))
	{
		//ASE_ParseBlock(this, &cASELoader::ASE_KeyNODE_TM);
	}
	// ignore regular meshes that aren't part of animation
	else if (!strcmp(token, "*MESH"))
	{
		ase.currentMesh = &ase.currentObject->mesh;
		memset(ase.currentMesh, 0, sizeof(ase.currentMesh));

		ASE_ParseBlock(this, &cASELoader::ASE_KeyMESH);
	}
	// according to spec these are obsolete
	else if (!strcmp(token, "*MATERIAL_REF"))
	{
		ASE_GetToken(false);

		object->materialRef = atoi(ase.token.c_str());
	}
	// loads a sequence of animation frames
	else if (!strcmp(token, "*MESH_ANIMATION"))
	{
		//VERBOSE(("..found MESH_ANIMATION\n"));

		ASE_ParseBlock(this, &cASELoader::ASE_KeyMESH_ANIMATION);
	}
	// skip unused info
	else if (!strcmp(token, "*PROP_MOTIONBLUR") ||
		!strcmp(token, "*PROP_CASTSHADOW") ||
		!strcmp(token, "*PROP_RECVSHADOW") )
	{
		ASE_SkipRestOfLine();
	}


}

void cASELoader::ASE_ParseGeomObject(void) {
	aseObject_t	*object;



	object = new aseObject_t;
	memset(object, 0, sizeof(aseObject_t));
	ase.model->objects.push_back(object);
	ase.currentObject = object;

	object->frames.resize(32);

	ASE_ParseBlock(this, &cASELoader::ASE_KeyGEOMOBJECT);
}

void cASELoader::ASE_KeyGROUP(const char *token)
{
	if (!strcmp(token, "*GEOMOBJECT")) {
		ASE_ParseGeomObject();
	}
}

aseModel_t* cASELoader::ASE_Parse(const char *buffer) {
	
	memset(&ase, 0, sizeof(ase));

	//ase.verbose = verbose;

	ase.buffer = buffer;
	ase.len = strlen(buffer);
	ase.curpos = ase.buffer;
	ase.currentObject = NULL;

	// NOTE: using new operator because aseModel_t contains idList class objects
	ase.model = new aseModel_t;
	memset(ase.model, 0, sizeof(aseModel_t));
	ase.model->objects.resize(32);
	ase.model->materials.resize(32);

	while (ASE_GetToken(false)) {
		if (!strcmp(ase.token.c_str(), "*3DSMAX_ASCIIEXPORT") ||
			!strcmp(ase.token.c_str(), "*COMMENT")) {
			ASE_SkipRestOfLine();
		}
		else if (!strcmp(ase.token.c_str(), "*SCENE")) {
			ASE_SkipEnclosingBraces();
		}
		else if (!strcmp(ase.token.c_str(), "*GROUP")) {
			ASE_GetToken(false);		// group name
			ASE_ParseBlock(this, &cASELoader::ASE_KeyGROUP);
		}
		else if (!strcmp(ase.token.c_str(), "*SHAPEOBJECT")) {
			ASE_SkipEnclosingBraces();
		}
		else if (!strcmp(ase.token.c_str(), "*CAMERAOBJECT")) {
			ASE_SkipEnclosingBraces();
		}
		else if (!strcmp(ase.token.c_str(), "*MATERIAL_LIST")) {
			ASE_ParseBlock(this, &cASELoader::ASE_KeyMATERIAL_LIST);
		}
		else if (!strcmp(ase.token.c_str(), "*GEOMOBJECT")) {
			ASE_ParseGeomObject();
		}
		else if (ase.token.c_str()[0]) {
			assert(false && "unknown Token");
		}
	}

	return ase.model;
}

aseModel_t* cASELoader::ASE_Load(const char *fileName) {
	
	aseModel_t *ase;
	FILE* pf;

	pf = fopen(fileName, "r");
	time_t timeStamp = GetCurrentTime();
	


	fseek(pf, 0L, SEEK_END);
	long lSize = ftell(pf);
	rewind(pf);

	char *charbuffer;
	charbuffer = (char*)malloc(sizeof(char)*lSize);
	if (!charbuffer) fclose(pf), fputs("memory alloc fails", stderr), exit(1);
	


	size_t result = fread(charbuffer, 1, lSize, pf);
	m_ssBuf = stringstream(charbuffer);
	
	/*if (result != lSize) {
		OutputDebugString(charbuffer);
	}*/
	//if (1 != )
	//	fclose(pf), free(charbuffer), fputs("entire read fails", stderr), exit(1);


	//fileSystem->ReadFile(fileName, (void **)&buf, &timeStamp);
	
	if (!pf) {
		return NULL;
	}
	
	ase = ASE_Parse(charbuffer);
	ase->timeStamp = timeStamp;

	fclose(pf);
	delete[] charbuffer;
	return ase;
}
#include "stdafx.h"
#include "cObjectFromParser.h"
#include "cObjectParser.h"
#include "cObject.h"

using namespace std;

cObjectFromParser::cObjectFromParser()
: m_pResource(NULL)
{
}


cObjectFromParser::~cObjectFromParser()
{
	SAFE_DELETE(m_pResource);
	cObject* p;
	while (!m_vecObjects.empty()){
		p = m_vecObjects.back();
		m_vecObjects.pop_back();
		SAFE_DELETE(p);
	}
}

void cObjectFromParser::setup(const char* fileName){
	m_pResource = new cObjectParser(fileName);
	m_pResource->LoadAndParse();
	cObject* pObject;
	for (UINT i = 0; i < m_pResource->getObjectsInfo().size(); i++){
		pObject = new cObject;
		pObject->setup(
			m_pResource->getTexture(m_pResource->getObjectsInfo()[i].fileName),
			m_pResource->getObjectsInfo()[i].stMTL,
			m_pResource->getObjectsInfo()[i].m_vecVertex
			);
		m_vecObjects.push_back(pObject);
	}	
	pObject = NULL;
}

void cObjectFromParser::update(float delta){

}

void cObjectFromParser::setMatrix(D3DXMATRIX& mat){
	for (auto object : m_vecObjects){
		object->setMatrix(mat);
	}
}

void cObjectFromParser::render(){
	for (auto object : m_vecObjects){
		object->render();
	}
}
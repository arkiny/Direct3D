#include "stdafx.h"
#include "cObjectGirl.h"
#include "cASEObject.h"
#include "cMyASELoader.h"

cObjectGirl::cObjectGirl()
	:
	m_vPosition(0,0,0),
	m_pRoot(NULL),
	m_pASEObj(NULL)
{
	D3DXMatrixIdentity(&m_matworldMat);	
}


cObjectGirl::~cObjectGirl()
{
	if (m_pRoot){
		m_pRoot->destroy();
	}
	SAFE_DELETE(m_pASEObj);
}


void cObjectGirl::setup(){
	
	//cMyASELoader loader;
	m_pASEObj = new cMyASELoader;
	std::string sFolder1 = std::string("../Resource/");
	sFolder1 += std::string("ase/woman/");
	m_pASEObj->Load(sFolder1, std::string("woman_01_all.ASE"));

	std::vector<stASENode> vecNodeList = m_pASEObj->getASENodeList();
	std::vector<cMtlTex*> vecMtlTexList = m_pASEObj->getMtlTex();
	std::map<std::string, cASEObject*> vecNodeTree;

	
	D3DXMatrixIdentity(&m_matworldMat);

	cASEObject* pPart;
	for (int i = 0; i < vecNodeList.size(); i++){
		if (m_pRoot){
			pPart = new cASEObject;
			pPart->setup(vecNodeList[i]);
			vecNodeTree.insert(std::pair<std::string, cASEObject*>(vecNodeList[i].NodeName, pPart));
			vecNodeTree.at(vecNodeList[i].NodeParent)->AddChild(pPart);
		}
		else {
			pPart = new cASEObject;
			pPart->setup(vecNodeList[i]);
			vecNodeTree.insert(std::pair<std::string, cASEObject*>(vecNodeList[i].NodeName, pPart));
			m_pRoot = pPart;
		}
	}
	 
	_ASSERT(vecNodeTree.size() == vecNodeList.size());
	
}

void cObjectGirl::update(float delta){
	m_pRoot->update(delta, &m_matworldMat);
}

void cObjectGirl::render(){
	m_pRoot->render(m_pASEObj->getMtlTex());
}
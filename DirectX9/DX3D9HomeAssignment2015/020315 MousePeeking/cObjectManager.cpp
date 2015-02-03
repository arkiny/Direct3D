#include "stdafx.h"
#include "cObjectManager.h"


cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
}

void cObjectManager::AddObject(cObject* pObject){
	m_setObject.insert(pObject);
}

void cObjectManager::RemoveObject(cObject* pObject){
	m_setObject.erase(pObject);	
}

void cObjectManager::Destroy(){
	if (!m_setObject.empty())
	{
		for each(cObject* p in m_setObject)
		{
			OutputDebugString(p->GetDesc().c_str());
		}
		_ASSERT(false && "There are cObject which are not deleted");
	}
}
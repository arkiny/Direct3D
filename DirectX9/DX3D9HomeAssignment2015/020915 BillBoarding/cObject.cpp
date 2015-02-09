#include "stdafx.h"
#include "cObject.h"


cObject::cObject(void)
	: m_nRefCount(1)
{
	g_pObjectManager->AddObject(this);
}

cObject::cObject(std::string sDesc) 
	: m_nRefCount(1)
{
	m_sDesc = sDesc;
	g_pObjectManager->AddObject(this);
}

cObject::~cObject(void)
{
	_ASSERT(m_nRefCount <= 0);
	g_pObjectManager->RemoveObject(this);
}

void cObject::Release(){
	_ASSERT(m_nRefCount > 0);
	m_nRefCount--;
	if (m_nRefCount <= 0)
	{
		delete this;
	}
}

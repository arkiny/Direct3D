#include "StdAfx.h"
#include "cObject.h"


cObject::cObject(void)
	: m_nRefCount(1)
{
}


cObject::~cObject(void)
{
	assert(m_nRefCount <= 0);
}

#include "stdafx.h"
#include "cObject.h"


cObject::cObject(void)
	: m_nRefCount(1)
{
}


cObject::~cObject(void)
{
	_ASSERT(m_nRefCount <= 0);
}

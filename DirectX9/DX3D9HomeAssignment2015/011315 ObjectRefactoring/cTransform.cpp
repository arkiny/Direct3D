#include "stdafx.h"
#include "cTransform.h"


cTransform::cTransform()
	: m_vPosition(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matTransform);
}

cTransform::~cTransform()
{
}

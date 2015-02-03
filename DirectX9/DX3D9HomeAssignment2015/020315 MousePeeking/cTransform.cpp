#include "stdafx.h"
#include "cTransform.h"


cTransform::cTransform()
	: m_vPosition(0, 0, 0),
	m_fYAxisAngle(0.0f),
	m_fZAxisAngle(0.0f),
	m_fXAxisAngle(0.0f)
{
	D3DXMatrixIdentity(&m_matTransform);
}

cTransform::~cTransform()
{
}

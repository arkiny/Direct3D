#include "stdafx.h"
#include "cGameObject.h"
#include "cTransform.h"

cGameObject::cGameObject()
{
	m_pTransform = new cTransform;
}

cGameObject::~cGameObject()
{
	SAFE_RELEASE(m_pTransform);
}

D3DXMATRIXA16* cGameObject::GetTransformMatrix()
{
	return m_pTransform->GetTransformMatrix();
}
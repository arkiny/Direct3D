#include "stdafx.h"
#include "cActionMove.h"
#include "cTransform.h"
#include "cNTeapot.h"
#define SPEED 1.0f

cActionMove::cActionMove()
{
	m_fActionTime = 1.0f;
}


cActionMove::~cActionMove()
{
}


void cActionMove::Start(){
	m_fPassedTime = 0.0f;
	if (m_pOwner)
	{
		cTransform* pTransform = m_pOwner->GetTransform();
		pTransform->SetPosition(m_vFrom);
	}
}

void cActionMove::Update(float delta){
	m_fPassedTime += delta;

	float t = m_fPassedTime / m_fActionTime;
	if (t < 1.0f)
	{
		D3DXVECTOR3 v;
		//p = (1 - t) * p0 + t * p1
		D3DXVec3Lerp(&v, &m_vFrom, &m_vTo, t);
		cTransform* pTransform = m_pOwner->GetTransform();
		pTransform->SetPosition(v);
	}
	else
	{
		cTransform* pTransform = m_pOwner->GetTransform();
		pTransform->SetPosition(m_vTo);
		if (m_pDelegate)
			m_pDelegate->OnActionFinish(this);
	}
}
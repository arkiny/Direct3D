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

void cActionMove::Update(float delta, cNTeapot* pNTeapot){
	m_fPassedTime = m_fPassedTime + (delta * 1.0f/SPEED);
	D3DXVECTOR3 curPos = m_vFrom + (m_vTo - m_vFrom) * m_fPassedTime;

	if (m_fActionTime > m_fPassedTime){
		pNTeapot->GetTransform()->SetPosition(curPos);
	}
	else {
		m_fPassedTime = 0.0f;
		pNTeapot->SetNextTarget();
	}	
}
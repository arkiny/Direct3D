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

void cGameObject::Update(float delta){
	if (m_pAction){
		m_vPrevPosition = m_pTransform->GetPosition();
		m_pAction->Update(delta);
		D3DXVECTOR3 vCurrPosition = m_pTransform->GetPosition();
		D3DXVECTOR3 vDeltaPosition = vCurrPosition - m_vPrevPosition;
		if (fabs(vDeltaPosition.x) > 0.0001f)
		{
			m_fAngle = -atan2(vDeltaPosition.z, vDeltaPosition.x);
		}
	}
}

void cGameObject::SetAction(cAction* pAction){
	if (m_pAction != pAction)
	{
		pAction->SetOwner(this);
		SAFE_ADD_REF(pAction);
		SAFE_RELEASE(m_pAction);
		m_pAction = pAction;
	}
}

cTransform*	cGameObject::GetTransform(){
	return m_pTransform;
}

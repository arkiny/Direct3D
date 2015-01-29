#include "stdafx.h"
#include "cActionIdle.h"


cActionIdle::cActionIdle()
{
	m_fActionTime = 1.0f;
}


cActionIdle::~cActionIdle()
{
}

void cActionIdle::Start(){
	m_fPassedTime = 0.0f;
	if (m_pOwner)
	{
		cTransform* pTransform = m_pOwner->GetTransform();
	}
}

void cActionIdle::Update(float delta){
	// if get key, change action;
	if (GetKeyState('0') & 0x8000)
	{
		if (m_pDelegate)
			m_pDelegate->OnActionMoveTargetUpdated(this, 0);
	}
	if (GetKeyState('1') & 0x8000)
	{
		if (m_pDelegate)
			m_pDelegate->OnActionMoveTargetUpdated(this, 1);
	}
	if (GetKeyState('2') & 0x8000)
	{
		if (m_pDelegate)
			m_pDelegate->OnActionMoveTargetUpdated(this, 2);
	}
	if (GetKeyState('3') & 0x8000)
	{
		if (m_pDelegate)
			m_pDelegate->OnActionMoveTargetUpdated(this, 3);
	}
	if (GetKeyState('4') & 0x8000)
	{
		if (m_pDelegate)
			m_pDelegate->OnActionMoveTargetUpdated(this, 4);
	}
	if (GetKeyState('5') & 0x8000)
	{
		if (m_pDelegate)
			m_pDelegate->OnActionMoveTargetUpdated(this, 5);
	}
	if (GetKeyState('6') & 0x8000)
	{
		if (m_pDelegate)
			m_pDelegate->OnActionMoveTargetUpdated(this, 6);
	}
	if (GetKeyState('7') & 0x8000)
	{
		if (m_pDelegate)
			m_pDelegate->OnActionMoveTargetUpdated(this, 7);
	}
}
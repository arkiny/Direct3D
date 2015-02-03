#include "StdAfx.h"
#include "cAnimationSet.h"


cAnimationSet::cAnimationSet(void)
	: m_pAnimationSet(NULL)
	, m_isLoop(false)
	, m_pPrevAnimation(NULL)
	, m_fPassedTime(0.0)
	, m_pDelegate(NULL)
	, m_nIndex(0)
{
}


cAnimationSet::~cAnimationSet(void)
{
}

void cAnimationSet::Start()
{
	m_fPassedTime = 0.0f;
}

void cAnimationSet::Update(float delta)
{
	m_fPassedTime += delta;
	if (m_fPassedTime >= m_pAnimationSet->GetPeriod())
	{
		if (m_pDelegate)
		{
			m_pDelegate->OnFinishAnimation(this);
		}
	}
}

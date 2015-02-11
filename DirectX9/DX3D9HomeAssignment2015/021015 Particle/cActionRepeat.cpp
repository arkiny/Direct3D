#include "stdafx.h"
#include "cActionRepeat.h"


cActionRepeat::cActionRepeat():
m_pAction(NULL)
{
}


cActionRepeat::~cActionRepeat()
{
	SAFE_RELEASE(m_pAction);
}


void cActionRepeat::SetAction(cAction* pAction){
	if (m_pAction != pAction)
	{
		pAction->SetDelegate(this);
		SAFE_ADD_REF(pAction);
		SAFE_RELEASE(m_pAction);
		m_pAction = pAction;
	}
}

// cAction override
void cActionRepeat::Start(){
	if (m_pAction)
		m_pAction->Start();
}

void cActionRepeat::Update(float delta){
	if (m_pAction)
		m_pAction->Update(delta);
}

// iActionDelegate override
void cActionRepeat::OnActionFinish(cAction* pSender){
	pSender->Start();
}
#include "stdafx.h"
#include "cActionSeq.h"


cActionSeq::cActionSeq()
{
}


cActionSeq::~cActionSeq()
{
	for (auto p : m_lstAction){
		SAFE_RELEASE(p);
	}
}


void cActionSeq::AddAction(cAction* pAction){
	pAction->AddRef();
	pAction->SetDelegate(this);
	m_lstAction.push_back(pAction);
}

void cActionSeq::Start(){
	m_itCurrAction = m_lstAction.begin();
	if (*m_itCurrAction)
		(*m_itCurrAction)->Start();
}

void cActionSeq::Update(float delta){
		(*m_itCurrAction)->Update(delta);
}

void cActionSeq::OnActionFinish(cAction* pSender){
	++m_itCurrAction;
	if (m_itCurrAction == m_lstAction.end())
	{
		if (m_pDelegate)
			m_pDelegate->OnActionFinish(this);
	}
	else
	{
		(*m_itCurrAction)->Start();
	}
}
void cActionSeq::OnActionMoveTargetUpdated(cAction* pSender, int TargetNode){
	if (m_pDelegate)
		m_pDelegate->OnActionMoveTargetUpdated(this, TargetNode);
}
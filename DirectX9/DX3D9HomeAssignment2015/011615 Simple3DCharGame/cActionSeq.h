#pragma once
#include "cAction.h"

class cActionSeq : public cAction, public iActionDelegate
{
protected:
	std::list<cAction*>				m_lstAction;
	std::list<cAction*>::iterator	m_itCurrAction;

public:
	cActionSeq();
	virtual ~cActionSeq();

	virtual void AddAction(cAction* pAction);

	//cAction override
	virtual void Start() override;
	virtual void Update(float delta) override;

	//iActionDelegate override
	virtual void OnActionFinish(cAction* pSender) override;
};


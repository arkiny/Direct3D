#pragma once
#include "cAction.h"

class cActionRepeat : public cAction, public iActionDelegate
{
protected:
	cAction* m_pAction;

public:
	cActionRepeat();
	virtual ~cActionRepeat();

	virtual void SetAction(cAction* pAction);
	// cAction override
	virtual void Start() override;
	virtual void Update(float delta) override;

	// iActionDelegate override
	virtual void OnActionFinish(cAction* pSender) override;
};


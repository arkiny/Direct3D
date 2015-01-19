#pragma once
class cAction;
__interface iActionDelegate
{
public:
	virtual void OnActionFinish(cAction* pSender) = 0;
};


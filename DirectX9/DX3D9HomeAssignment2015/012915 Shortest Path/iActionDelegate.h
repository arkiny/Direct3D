#pragma once
class cAction;
__interface iActionDelegate
{
public:
	virtual void OnActionMoveTargetUpdated(cAction* pSender, int TargetNode) = 0;
	virtual void OnActionFinish(cAction* pSender) = 0;
};


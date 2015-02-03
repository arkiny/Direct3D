#pragma once

class cGameObject;

class cAction : public cObject
{
protected:
	float m_fPassedTime;
	SYNTHESIZE(float, m_fActionTime, ActionTime);
	SYNTHESIZE(cGameObject*, m_pOwner, Owner);
	SYNTHESIZE(iActionDelegate*, m_pDelegate, Delegate);

public:
	cAction();
	virtual ~cAction();
	virtual void Start() {}
	virtual void Update(float delta) = 0;
};


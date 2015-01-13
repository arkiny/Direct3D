#pragma once

class cNTeapot;

class cAction
{
protected:
	float m_fPassedTime;
	SYNTHESIZE(float, m_fActionTime, ActionTime);

public:
	cAction();
	virtual ~cAction();
	virtual void Update(float delta, cNTeapot* pNTeapot) = 0;
};


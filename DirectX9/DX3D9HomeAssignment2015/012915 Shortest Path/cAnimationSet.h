#pragma once

class cAnimationSet;

class iAnimationSetDelegate
{
public:
	virtual void OnFinishAnimation(cAnimationSet* pSender) = 0;
};

class cAnimationSet
{
protected:
	SYNTHESIZE_ADD_REF(LPD3DXANIMATIONSET, m_pAnimationSet, AnimationSet);
	SYNTHESIZE(bool, m_isLoop, IsLoop);
	SYNTHESIZE(cAnimationSet*, m_pPrevAnimation, PrevAnimation);
	SYNTHESIZE(iAnimationSetDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE(int, m_nIndex, Index);

private:
	float m_fPassedTime;

public:
	cAnimationSet(void);
	~cAnimationSet(void);

	void Start();
	void Update(float delta);
};


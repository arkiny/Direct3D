#pragma once
#include "cAction.h"

class cActionMove : public cAction
{
protected:
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vFrom, From);
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vTo, To);

public:
	cActionMove();
	virtual ~cActionMove();
	virtual void Update(float delta, cNTeapot* pNTeapot) override;
};


#pragma once
#include "cButton.h"
class cMoveBar : public cButton
{
private:
	D3DXVECTOR2		m_vecPrev;
	D3DXVECTOR2		m_vecMove;
	bool			m_bIsMoving;
	
public:
	cMoveBar();
	~cMoveBar();

	virtual void Update(float delta) override;
	POINT* getCurPos(){ return m_pMouseLoc; }
};


#include "stdafx.h"
#include "cMoveBar.h"


cMoveBar::cMoveBar() :
m_bIsMoving(false)
{
}


cMoveBar::~cMoveBar()
{
}

void cMoveBar::Update(float delta){

	if (m_pMouseLoc->x >= m_stOriRect.left	&& m_pMouseLoc->x <= m_stOriRect.right &&
		m_pMouseLoc->y >= m_stOriRect.top && m_pMouseLoc->y <= m_stOriRect.bottom){
		m_bCursorOn = true;
	}
	else {
		m_bCursorOn = false;
	}

	if (*m_pClicked && m_bCursorOn){
		if (!m_bIsMoving){
			m_bIsMoving = true;
			m_vecPrev = { (float)m_pMouseLoc->x, (float)m_pMouseLoc->y };
		}
		else {
			float xMove = m_pMouseLoc->x - m_vecPrev.x;
			float yMove = m_pMouseLoc->y - m_vecPrev.y;
			m_vecPrev = { (float)m_pMouseLoc->x, (float)m_pMouseLoc->y };
			m_vecMove = { xMove, yMove };
			m_pDelegate->UserInterfaceMove(this, m_vecMove);
		}
	}
	else if (*m_pClicked && m_bIsMoving) {
		float xMove = m_pMouseLoc->x - m_vecPrev.x;
		float yMove = m_pMouseLoc->y - m_vecPrev.y;
		m_vecPrev = { (float)m_pMouseLoc->x, (float)m_pMouseLoc->y };
		m_vecMove = { xMove, yMove };
		m_pDelegate->UserInterfaceMove(this, m_vecMove);
	}
	else {
		m_bIsMoving = false;
	}	
}
#include "stdafx.h"
#include "cOKButton.h"


cOKButton::cOKButton()
{
	m_sContent = "";
}


cOKButton::~cOKButton()
{
}

void cOKButton::Update(float delta){
	cButton::Update(delta);
	if (m_bActivated){
		if (m_bCursorOn){
			if (m_pDelegate){
				m_bActivated = false;
				m_pDelegate->UserInterfaceActivation(this, m_sContent);
			}
			else{
				m_bActivated = false;
			}
		}
	}
}

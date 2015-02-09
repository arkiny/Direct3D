#include "stdafx.h"
#include "cExitButton.h"
#include "iUserInterfaceDelegate.h"

cExitButton::cExitButton()
{
}


cExitButton::~cExitButton()
{
}

void cExitButton::Update(float delta){
	cButton::Update(delta);

	if (m_bActivated){
		if (m_bCursorOn){
			if (m_pDelegate){
				m_bActivated = false;
				m_pDelegate->UserInterfaceFinished(this);
			}
			else{
				m_bActivated = false;
			}
		}
	}
}

//void cExitButton::Render(){
//	cButton::Render();
//}

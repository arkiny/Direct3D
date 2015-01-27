#pragma once
#include "cUserInterface.h"

class cExitButton : public cUserInterface
{
private:
	bool m_bClicked = false;

	SYNTHESIZE(iUserInterfaceDelegate*, m_pDelegate, Delegate);
	

public:
	cExitButton();
	virtual ~cExitButton();
	//virtual void Update(float);
};


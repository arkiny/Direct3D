#pragma once
#include "cButton.h"

class cExitButton : public cButton {
public:
	cExitButton();
	virtual ~cExitButton();
	virtual void Update(float delta) override;
};


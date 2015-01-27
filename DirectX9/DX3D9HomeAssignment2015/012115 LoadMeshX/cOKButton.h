#pragma once
#include "cButton.h"

class cOKButton : public cButton
{
protected:
	std::string m_sContent;

public:
	cOKButton();
	virtual ~cOKButton();
	virtual void Update(float delta) override;
	virtual void SetContent(std::string& in){
		m_sContent = in;
	}
};


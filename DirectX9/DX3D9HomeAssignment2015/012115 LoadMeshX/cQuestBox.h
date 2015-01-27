#pragma once
#include "cUserInterface.h"

class cQuestBox : public cUserInterface, public iUserInterfaceDelegate
{
private:
	cUserInterface*						m_pUserInterface;

public:
	cQuestBox();
	~cQuestBox();
	void Setup();
	void Update(float delta);
	void Render();
	virtual void UserInterfaceActivation(cUserInterface* pSender);
	virtual void UserInterfaceFinished(cUserInterface* pSender);
};


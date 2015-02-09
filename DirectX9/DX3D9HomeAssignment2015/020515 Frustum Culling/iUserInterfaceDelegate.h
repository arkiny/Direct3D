#pragma once
class cUserInterface;

__interface iUserInterfaceDelegate{
	// accept, cancel
	virtual void UserInterfaceActivation(cUserInterface* pSender, std::string& sContent) = 0;
	virtual void UserInterfaceFinished(cUserInterface* pSender) = 0;
	virtual void UserInterfaceMove(cUserInterface* pSender, D3DXVECTOR2& move) = 0;
};

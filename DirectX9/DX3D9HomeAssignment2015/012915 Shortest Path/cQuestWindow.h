#pragma once
#include "iUserInterfaceDelegate.h"

class cUserInterface;

class cQuestWindow : public cGameObject, public iUserInterfaceDelegate
{
private:
	cUserInterface*						m_pUserInterface;
	bool								m_bShow = true;
	std::string							m_sTextContent;
	RECT								m_stMoveBar;

public:
	cQuestWindow();
	~cQuestWindow();
	void Setup();
	void Update(float delta);
	void Render();
	
	void SetMousePosPointer(POINT* mousPos);
	void SetMouseClickInfo(bool* mousclick);
	void SetPosition(D3DXVECTOR3& pos);

	virtual void UserInterfaceActivation(cUserInterface* pSender, std::string& sContent);
	virtual void UserInterfaceFinished(cUserInterface* pSender);
	virtual void UserInterfaceMove(cUserInterface* pSender, D3DXVECTOR2& move);
};


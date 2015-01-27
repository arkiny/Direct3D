#include "stdafx.h"
#include "cQuestBox.h"
#include "cExitButton.h"


cQuestBox::cQuestBox() :
m_pUserInterface(NULL)
{
}

cQuestBox::~cQuestBox()
{
	SAFE_RELEASE(m_pUserInterface);
}

void cQuestBox::Setup(){
	m_pUserInterface = new cUserInterface;
	m_pUserInterface->Setup("../Resource/UI/", "menu_normalbox.png");
	m_pUserInterface->SetPosition(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	cExitButton* p = new cExitButton;
	p->Setup("../Resource/UI/", "ui_hookeditem.png");
	p->SetPosition(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	p->SetDelegate(this);
	m_pUserInterface->AddChild(p);

	cUserInterface* dp = new cUserInterface;
	dp->Setup("../Resource/UI/", "ui_hookeditem.png");
	dp->SetPosition(D3DXVECTOR3(150.0f, 10.0f, 0.0f));
	p->SetDelegate(this);
	m_pUserInterface->AddChild(dp);
}

void cQuestBox::Update(float delta){
	// clicked
	// m_pDelegate->UserInterfaceFinished(this);
}

void cQuestBox::Render(){	
	if (m_pUserInterface){
		m_pUserInterface->Render();
	}
}

void cQuestBox::UserInterfaceActivation(cUserInterface* pSender){
	int a = 0;
}

void cQuestBox::UserInterfaceFinished(cUserInterface* pSender){
	int a = 0;
}
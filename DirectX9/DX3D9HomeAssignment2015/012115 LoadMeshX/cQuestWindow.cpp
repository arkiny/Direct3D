#include "stdafx.h"
#include "cQuestWindow.h"
#include "cExitButton.h"
#include "cTextBox.h"
#include "cUserInterface.h"
#include "cOKButton.h"
#include "cMoveBar.h"


cQuestWindow::cQuestWindow() :
m_pUserInterface(NULL)
{
}

cQuestWindow::~cQuestWindow()
{
	SAFE_RELEASE(m_pUserInterface);
}

void cQuestWindow::Setup(){

	m_stMoveBar.left = m_pTransform->GetPosition().x + 9.0;
	m_stMoveBar.top = m_pTransform->GetPosition().y + 5.0;
	m_stMoveBar.right = m_pTransform->GetPosition().x + 287.0;
	m_stMoveBar.bottom = m_pTransform->GetPosition().y + 30.0;

	m_pUserInterface = new cUserInterface;
	m_pUserInterface->Setup("../Resource/UI/", "UI_basicBox", ".png");
	m_pUserInterface->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUserInterface->SetParentLeftTop(m_pTransform->getPosPointer());

	cExitButton* p = new cExitButton;
	p->Setup("../Resource/UI/", "UI_XButton", ".png");
	p->SetPosition(D3DXVECTOR3(289.0f, 8.0f, 0.0f));
	p->SetDelegate(this);
	m_pUserInterface->AddChild(p);

	m_sTextContent = "There's a Quest. \n Make a Inventory UI";

	cTextBox* tp = new cTextBox;
	tp->Setup("../Resource/UI/", "UI_TextBox", ".png");
	tp->SetPosition(D3DXVECTOR3(12.0f, 44.0f, 0.0f));
	tp->SetCaptionTarget(&m_sTextContent);
	m_pUserInterface->AddChild(tp);

	cOKButton* okp = new cOKButton;
	okp->Setup("../Resource/UI/", "UI_AcceptButton", ".png");
	okp->SetPosition(D3DXVECTOR3(21.0f, 271.0f, 0.0f));
	okp->SetDelegate(this);
	std::string content = "Challenge Accepted";
	okp->SetContent(content);
	m_pUserInterface->AddChild(okp);

	cOKButton* cp = new cOKButton;
	cp->Setup("../Resource/UI/", "UI_CancelButton", ".png");
	cp->SetPosition(D3DXVECTOR3(184.0f, 271.0f, 0.0f));
	cp->SetDelegate(this);
	content = "Challenge Denied";
	cp->SetContent(content);
	m_pUserInterface->AddChild(cp);


	//UI_MoveBar
	cMoveBar* mp = new cMoveBar;
	mp->Setup("../Resource/UI/", "UI_MoveBar", ".png");
	mp->SetPosition(D3DXVECTOR3(9.0f, 5.0f, 0.0f));
	mp->SetDelegate(this);
	m_pUserInterface->AddChild(mp);
}

void cQuestWindow::SetPosition(D3DXVECTOR3& pos){
	m_pTransform->SetPosition(pos);
}

void cQuestWindow::SetMousePosPointer(POINT* mousPos){
	if (m_pUserInterface){
		m_pUserInterface->SetMousePosPointer(mousPos);
	}
}

void cQuestWindow::SetMouseClickInfo(bool* mousclick){

	if (m_pUserInterface){
		m_pUserInterface->SetMouseClickInfo(mousclick);
	}
}

void cQuestWindow::Update(float delta){
	if (m_bShow){
		m_pUserInterface->Update(delta);
		m_pUserInterface->UpdateRectangle(m_pTransform->getPosPointer());
	}
	else {
		if (GetKeyState('Q') & 0x8000){
			m_bShow = true;
		}
	}
}

void cQuestWindow::Render(){	
	if (m_pUserInterface){
		if (m_bShow){
			m_pUserInterface->Render();
		}
	}
}

void cQuestWindow::UserInterfaceActivation(cUserInterface* pSender, std::string& sContent){
	m_sTextContent = sContent;
}

void cQuestWindow::UserInterfaceFinished(cUserInterface* pSender){
	m_bShow = false;
}

void cQuestWindow::UserInterfaceMove(cUserInterface* pSender, D3DXVECTOR2& move){
	D3DXVECTOR3 newpos = { m_pTransform->GetPosition().x + move.x, m_pTransform->GetPosition().y + move.y, 0.0f };
	m_pTransform->SetPosition(newpos);
}
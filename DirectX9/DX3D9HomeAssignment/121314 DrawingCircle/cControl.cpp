#include "stdafx.h"
#include "cControl.h"


cControl::cControl()
{
	memset(m_bKeyCodeArray, 0, sizeof(m_bKeyCodeArray));
	m_MousePos = { 0, 0 };
}


cControl::~cControl()
{
}


void cControl::OnKeyDown(WPARAM wParam){
	m_bKeyCodeArray[wParam] = true;
}

void cControl::OnKeyUP(WPARAM wParam){
	m_bKeyCodeArray[wParam] = false;
}

void cControl::OnMouseMove(LPARAM lParam){
	m_MousePos.x = LOWORD(lParam);
	m_MousePos.y = HIWORD(lParam);
}

void cControl::OnMouseClick(LPARAM lParam){
	m_ClickPos.x = LOWORD(lParam);
	m_ClickPos.y = HIWORD(lParam);
}


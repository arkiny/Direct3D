#pragma once
class cControl
{
	SINGLETONE(cControl);

public:
	void OnKeyDown(WPARAM wParam);
	void OnKeyUP(WPARAM wParam);
	void OnMouseMove(LPARAM lParam);
	void OnMouseClick(LPARAM lParam);

	bool cControl::getKeyControlInfo(WPARAM in){
		return m_bKeyCodeArray[in];
	}

	POINTFLOAT cControl::getMousePosition(){
		return m_MousePos;
	}

	POINTFLOAT cControl::getClickPosition(){
		return m_ClickPos;
	}

private:
	bool m_bKeyCodeArray[256];
	POINTFLOAT m_MousePos;
	POINTFLOAT m_ClickPos;
};


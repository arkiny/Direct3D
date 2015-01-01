#pragma once

#define g_pControl cControl::GetInstance()


class cControl
{
	SINGLETONE(cControl);

public:
	enum MOUSEWHEELTYPE{up, down, nomove};

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

	bool getMouseScrollInfo(MOUSEWHEELTYPE in){
		return m_bWheel[in];
	}

	void setMouseScrollInfo(MOUSEWHEELTYPE in){
		if (in < 2){
			m_bWheel[in] = true;
		}
		else{
			m_bWheel[up] = false;
			m_bWheel[down] = false;
		}
	}

private:
	bool m_bKeyCodeArray[256];
	bool m_bWheel[2];
	POINTFLOAT m_MousePos;
	POINTFLOAT m_ClickPos;
};


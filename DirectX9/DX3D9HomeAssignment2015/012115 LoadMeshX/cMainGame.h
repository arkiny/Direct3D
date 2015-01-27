#pragma once

#include "gIObject.h"
#include "cUserInterface.h"

class cAxis;
class cGrid;
class cCamera;
class cPyramid;
class cCharacter;
class cHeightMap;
class cSkinnedMesh;
class cQuestBox;

class cMainGame : public cObject, public iActionDelegate, public iUserInterfaceDelegate
{
private:
	POINT								m_mousePos;

	cAxis*								m_cAxis;
	cGrid*								m_cGrid;
	cCamera*							m_cCamera;
	cPyramid*							m_pPyramid;
	cCharacter*							m_pCharacter;
	cHeightMap*							m_pHeightMap;
	cSkinnedMesh*						m_pSkinnedMesh;
	cQuestBox*							m_pQuestBox;

	LPD3DXFONT							m_pFont;
	RECT								m_recFontRect;

	bool								m_bIntShow = true;
	int									m_nScore;
	float								m_fAccumTime = 0.0f;

public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update(float delta);
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void OnActionFinish(cAction* pSender);
	
	void UserInterfaceActivation(cUserInterface* pSender) override;
	void UserInterfaceFinished(cUserInterface* pSender) override;
};


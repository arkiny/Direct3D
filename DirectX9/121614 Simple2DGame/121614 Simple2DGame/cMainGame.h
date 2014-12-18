#pragma once
#include "IObject.h"
class cMainGame
{
private:
	// background
	std::vector<ST_RHW_VERTEX>			m_vecVertex;
	LPD3DXFONT							m_pFont;
	RECT								m_recFontRect;
	//bool								m_bPause = false;

	//ST_RHW_VERTEX v2[3];
	//LPDIRECT3DVERTEXBUFFER9 v_buffer;
	/*IObject_Circle* m_cCircle1;
	IObject_Circle* m_cCircle2;*/
	IObject* m_oPlayer;
	std::vector<IObject*> m_vecoShit;
	std::vector<IObject*> m_vecoRoadLine;

	int m_nDifficulty;
	float m_faccumTime = 0.0f;
	float m_fTotalTime = 0.0f;

	LPDIRECT3DTEXTURE9 m_pArrShitTexture[6];

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update(float delta);
	void Render();

	// control

};


#pragma once
class cObjectCircle;
class cMainGame
{
private:
	std::vector<ST_RHW_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9			m_pTexture;
	//ST_RHW_VERTEX v2[3];
	//LPDIRECT3DVERTEXBUFFER9 v_buffer;
	cObjectCircle* m_cCircle1;
	cObjectCircle* m_cCircle2;


public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();

	// control

};


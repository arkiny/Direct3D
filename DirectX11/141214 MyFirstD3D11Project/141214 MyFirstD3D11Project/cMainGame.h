#pragma once
class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	void init();
	void update(float);
	void render();
private:


	ID3D11VertexShader	*pVS;		    // the vertex shader
	ID3D11PixelShader	*pPS;			// the pixel shader
	ID3D11Buffer		*pVBuffer;		// buffer
	
	ID3D11InputLayout *pLayout; // layout

	
	std::vector<ST_VERTEX1> m_vecdata;
};


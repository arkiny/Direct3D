#pragma once
class cObject
{
public:
	cObject();
	~cObject();

	void setup(LPDIRECT3DTEXTURE9 texture, D3DMATERIAL9& mat, std::vector<ST_PNT_VERTEX>& vecVertex);
	void update(float delta);
	void render();

	void setTexture(LPDIRECT3DTEXTURE9 texture){
		m_pTexture = texture;
		m_pTexture->AddRef();
	}

	void setMaterial(D3DMATERIAL9& mat){
		m_stMaterial = mat;
	}

	void setVertices(std::vector<ST_PNT_VERTEX>& vecVertex){
		m_vecVertex = vecVertex;
	}

	void setMatrix(D3DXMATRIX& mat){ m_worldMat = mat; }

private:
	LPDIRECT3DTEXTURE9			m_pTexture;
	std::vector<ST_PNT_VERTEX>	m_vecVertex;
	D3DMATERIAL9				m_stMaterial;
	D3DXMATRIX					m_worldMat;
};


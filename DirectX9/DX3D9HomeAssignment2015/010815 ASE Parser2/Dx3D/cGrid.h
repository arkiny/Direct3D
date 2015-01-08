#pragma once
class cGrid
{
private:
	class cPyramid
	{
	private:
		LPDIRECT3DVERTEXBUFFER9		m_pVB;
		int							m_nNumTri;
		D3DXMATRIXA16				m_matWorld;

	public:
		cPyramid() : m_pVB(NULL), m_nNumTri(0) {}
		~cPyramid()
		{
			SAFE_RELEASE(m_pVB);
		}
		void Setup(D3DXMATRIXA16& mat, D3DCOLOR c);
		void Render();
	};

	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	int							m_nNumLine;
	std::vector<cPyramid*>		m_vecPyramid;

public:
	cGrid(void);
	~cGrid(void);

	void Setup(int nHalfTile, float fWidth);
	void Render();
};


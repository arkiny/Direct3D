#pragma once
class cAseParser 
{
public:
	struct AseFce
	{
		union	{ struct	{ WORD a;	WORD b;	WORD c; };	WORD m[3]; };

		AseFce() : a(0), b(1), c(2){}
		AseFce(WORD A, WORD B, WORD C) : a(A), b(B), c(C){}
		AseFce(WORD* r)					{ a = r[0]; b = r[1];	 c = r[2]; }
		operator WORD*()				{ return (WORD *)&a; }
		operator const WORD* () const	{ return (CONST WORD *) &a; }
	};

	typedef char AseKey[64];		// String Keword

	struct AseMtl
	{
		char				sTex[MAX_PATH];
		D3DXIMAGE_INFO		pImg;
		LPDIRECT3DTEXTURE9	pTex;

		AseMtl()
		{
			memset(sTex, 0, sizeof sTex);
			pTex = NULL;
		}

		~AseMtl()
		{
			if (pTex)
			{
				pTex->Release();
				pTex = NULL;
			}
		}
	};

	struct AseTvtx
	{
		INT		nVt;				// 배열에서 정점의 인덱스
		FLOAT	u, v, w;			// UVW좌표

		AseTvtx() :nVt(-1), u(0), v(0), w(0){}
	};

	struct AseVtx
	{
		FLOAT x, y, z;

		AseVtx() : x(0), y(0), z(0){}
		enum	{ FVF = (D3DFVF_XYZ), };
	};

	struct AseVtxN
	{
		FLOAT	Px, Py, Pz;
		FLOAT	Nx, Ny, Nz;

		AseVtxN() : Px(0), Py(0), Pz(0), Nx(0), Ny(0), Nz(0){}
		enum	{ FVF = (D3DFVF_XYZ | D3DFVF_NORMAL), };
	};

	struct AseVtxUV
	{
		FLOAT	Px, Py, Pz;
		FLOAT	u, v;

		AseVtxUV() : Px(0), Py(0), Pz(0), u(0), v(0){}
		enum	{ FVF = (D3DFVF_XYZ | D3DFVF_TEX1), };
	};

	struct AseVtxNUV
	{
		FLOAT	Px, Py, Pz;
		FLOAT	Nx, Ny, Nz;
		FLOAT	u, v;

		AseVtxNUV() : Px(0), Py(0), Pz(0), Nx(0), Ny(0), Nz(0), u(0), v(0){}
		enum	{ FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1), };
	};

	struct AseTM
	{
		FLOAT	mtW[4][4];							// World Matrix
		FLOAT	mtL[4][4];							// Local Matirx

		FLOAT	Px, Py, Pz;
		FLOAT	Rx, Ry, Rz, Rw;
		FLOAT	Sx, Sy, Sz;

		AseTM() : Px(0), Py(0), Pz(0)
			, Rx(0), Ry(0), Rz(0), Rw(0)
			, Sx(0), Sy(0), Sz(0){}
	};


	struct AseGeo
	{
		char		sNodeName[64];

		INT			nMtlRef;						// Material Index
		INT			iNumVtx;						// Number of Vertex
		INT			iNumFce;						// Number of Index

		INT			iNumTvtx;						// Number of Vertex
		INT			iNumTfce;						// Number of Index

		AseVtx*		pLstVtx;
		AseVtx*		pLstNor;
		AseFce*		pLstFce;

		AseTvtx*	pLstTvtx;
		AseFce*		pLstTfce;

		AseVtxN*	pVtxN;
		AseVtxUV*	pVtxUV;
		AseVtxNUV*	pVtxNUV;


		INT			iNix;						// Number of Index
		INT			iNvx;						// Number of Vertex
		AseFce*		pIdx;						// for indexed buffer
		void*		pVtx;						// for vertex buffer
		DWORD		dFVF;						// D3DX FVF
		DWORD		dStrid;						// Zero Stride

		AseTM		tmInf;

		AseGeo()
		{
			nMtlRef = -1;
			iNumVtx = 0;
			iNumFce = 0;
			iNumTvtx = 0;
			iNumTfce = 0;

			pLstVtx = NULL;
			pLstNor = NULL;
			pLstFce = NULL;

			pLstTvtx = NULL;
			pLstTfce = NULL;

			dFVF = 0;
			dStrid = 0;

			pVtxN = NULL;
			pVtxUV = NULL;
			pVtxNUV = NULL;

			memset(sNodeName, 0, sizeof sNodeName);


			iNix = 0;
			iNvx = 0;
			pIdx = NULL;
			pVtx = NULL;
			dFVF = 0;
			dStrid = 0;
		}

		~AseGeo()
		{
			if (pLstVtx)
			{
				delete[] pLstVtx;
				pLstVtx = NULL;
			}

			if (pLstNor)
			{
				delete[] pLstNor;
				pLstNor = NULL;
			}

			if (pLstFce)
			{
				delete[] pLstFce;
				pLstFce = NULL;
			}

			if (pLstTvtx)
			{
				delete[] pLstTvtx;
				pLstTvtx = NULL;
			}

			if (pLstTfce)
			{
				delete[] pLstTfce;
				pLstTfce = NULL;
			}

			if (pVtxN)
			{
				delete[] pVtxN;
				pVtxN = NULL;
			}

			if (pVtxUV)
			{
				delete[] pVtxUV;
				pVtxUV = NULL;
			}

			if (pVtxNUV)
			{
				delete[] pVtxNUV;
				pVtxNUV = NULL;
			}
		}
	};


protected:
	LPDIRECT3DDEVICE9	m_pDev;

	char		m_sFile[MAX_PATH];		// Model file

	INT			m_nMtl;
	AseMtl*		m_pMtl;

	INT			m_nGeo;
	AseGeo*		m_pGeo;

public:
	cAseParser();
	virtual ~cAseParser();

	virtual INT		Create(LPDIRECT3DDEVICE9 p1, const char* p2, void* p3 = NULL, void* p4 = NULL);
	virtual void	Destroy();

	virtual INT		FrameMove();
	virtual void	Render();

protected:
	void	Confirm();

	INT		GetNumMtl();
	INT		GetNumGeo();
	INT		GetNumVtx(INT nGeo);
	INT		GetNumIdx(INT nGeo);

	void*	GetPtVtx(INT nGeo);
	void*	GetPtIdx(INT nGeo);

protected:
	BOOL	CompareAseKey(char* val, char* key);
	INT		Load();
};
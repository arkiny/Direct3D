#pragma once
struct D3DXFRAME_DR : public D3DXFRAME{
	D3DXMATRIXA16 matWorld;
};

class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	cAllocateHierarchy();
	~cAllocateHierarchy();

	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name,
		LPD3DXFRAME *ppNewFrame) override;

	STDMETHOD(CreateMeshContainer)(THIS_
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer) override;

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) override;

	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) override;
};


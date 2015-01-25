#pragma once

class cMtlTex;

struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16 matWorldTM;
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	// CloneMeshFVF�Լ��� ����Ͽ� ���� �޽��� �������ּ���.

	DWORD					dwNumSubset;
	std::vector<cMtlTex*>	vecMtlTex;

	LPD3DXMESH				pOrigMesh;				// ���� �޽�
	D3DXMATRIX**			ppBoneMatrixPtrs;		// �� �޽��� ������ �ִ� ������'��'�� �����Ʈ���� ������ �迭
	D3DXMATRIX*				pBoneOffsetMatrices;	// ���� �޽��� ���ý����̽��� ������ ��Ʈ������.
	D3DXMATRIX*				pCurrentBoneMatrices;	// �� ���� ���� �����Ʈ����
};

class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
protected:
	SYNTHESIZE(std::string, m_sFolder, Folder);

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


#pragma once
class cSkinnedMesh
{
private:
	D3DXFRAME*					m_pRootFrame;
	LPD3DXANIMATIONCONTROLLER	m_pAnimControl;
public:
	cSkinnedMesh(void);
	~cSkinnedMesh(void);

	void Setup(std::string sFolder, std::string sFile);
	void Render();
	void Update(float delta);

private:
	void SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIXA16* pmatParent);
	void Render(D3DXFRAME* pFrame);
	void SetupBoneMatrixPtrs(D3DXFRAME* pFrame);
	void UpdateSkinnedMesh(D3DXFRAME* pFrame);
};


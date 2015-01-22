#pragma once

class cSkinnedMesh
{
private:
	LPD3DXFRAME m_pRootFrame;
public:
	cSkinnedMesh();
	~cSkinnedMesh();

	void Setup(std::string sFolder, std::string sFile);

private:

	void SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIXA16* pmatParent);

};


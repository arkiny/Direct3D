#pragma once

class cSkinnedMesh;
class cSphere;

class cSkinnedMeshObject : public cGameObject
{
private:
	cSkinnedMesh*						m_pSkinnedMesh;
		
	LPD3DXMESH							m_pFontMesh;
	D3DMATERIAL9						m_stFontMtl;

	cSphere*							m_pSphere;

public:
	cSkinnedMeshObject();
	~cSkinnedMeshObject();

	void Setup();
	void Update(float delta);
	void Render();
	void SetAnimationIndex(DWORD dwIndex);
	cSphere* GetSphere() { return m_pSphere; }
	void SetSelcted(bool in);
};


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
	volatile bool						m_bIsLoaded = false;

public:
	cSkinnedMeshObject();
	~cSkinnedMeshObject();

	bool isLoaded(){ return m_bIsLoaded; }
	void SetisLoaded(bool in) { m_bIsLoaded = in; }

	void Setup();
	void Update(float delta);
	void Render();
	void SetAnimationIndex(DWORD dwIndex);
	cSphere* GetSphere() { return m_pSphere; }
	void SetSelcted(bool in);
};


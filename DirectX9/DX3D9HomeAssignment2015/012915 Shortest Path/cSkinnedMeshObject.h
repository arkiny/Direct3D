#pragma once

class cSkinnedMesh;

class cSkinnedMeshObject : public cGameObject
{
private:
	cSkinnedMesh*						m_pSkinnedMesh;

public:
	cSkinnedMeshObject();
	~cSkinnedMeshObject();

	void Setup();
	void Update(float delta);
	void Render();
	void SetAnimationIndex(DWORD dwIndex);
};


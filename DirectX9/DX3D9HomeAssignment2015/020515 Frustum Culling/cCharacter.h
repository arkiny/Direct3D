#pragma once

class cFrame;
class cAction;

__declspec(align(16)) class cCharacter : public cGameObject
{
private:
	std::vector<cFrame*>			m_vecFrameRoots;
	std::vector<stSceneInfo>		m_vecSceneInfo;

	D3DXVECTOR3						m_vFront;

	cFrame*							m_pCurrentFrameRoot;
	float							m_fAccum = 0.0f;
		
public:
	enum							ECState{ECS_IDLE, ECS_ISWALK};
	
	// override keyword new
	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

		void operator delete(void* p)
	{
		_mm_free(p);
	}

	cCharacter();
	~cCharacter();
	void Setup();
	void Update(float delta);
	void Render();
	D3DXVECTOR3* GetPosition();
};


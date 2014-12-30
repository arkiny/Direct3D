#pragma once

class cCube;

__declspec(align(16)) class cCharacter
{
public:

	cCharacter();
	~cCharacter();

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

		void operator delete(void* p)
	{
		_mm_free(p);
	}

	void init();
	void update(float delta);
	void render();
	void setPosition(D3DXVECTOR3 pos) { m_vPosition = pos; }
	D3DXVECTOR3& getPosition() { return m_vPosition; }
	D3DXVECTOR3& getForward(){ return m_vForward; }

private:
	std::vector<cCube*>		m_vecCube;
	D3DXVECTOR3				m_vPosition;
	D3DXVECTOR3				m_vForward;
	float					m_fAngleDegree = 0.0f;
	float					m_fSpeed;
	D3DXMATRIXA16			m_matWorldT;
};


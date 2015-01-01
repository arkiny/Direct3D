#pragma once

__declspec(align(16)) class cCamera
{
public:
	cCamera();
	~cCamera();
	void init();
	void update(float delta);

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}

	void movefoward(float speed);

private:
	float m_fViewRangeX = -10.0f;
	float m_fViewRangeZ = 2.0f;
	float m_fAngleDegree = 0.0f;
	D3DVIEWPORT9 vp;
	D3DXVECTOR3 vEye;
	D3DXVECTOR3 vLookAt;
	D3DXVECTOR3 vUp;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProj;
};


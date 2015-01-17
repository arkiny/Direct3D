#pragma once

__declspec(align(16)) class cTransform : public cObject
{
protected:
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vPosition, Position);
	D3DXMATRIXA16 m_matTransform;
		
public:
	cTransform();
	virtual ~cTransform();

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

		void operator delete(void* p)
	{
		_mm_free(p);
	}

	D3DXMATRIXA16* GetTransformMatrix()
	{
		D3DXMatrixTranslation(&m_matTransform, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		return &m_matTransform;
	}
};


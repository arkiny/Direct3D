#pragma once

__declspec(align(16)) class cTransform : public cObject
{
protected:
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(float, m_fYAxisAngle, YAxisAngle);
	SYNTHESIZE(float, m_fXAxisAngle, XAxisAngle);
	SYNTHESIZE(float, m_fZAxisAngle, ZAxisAngle);
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

	D3DXVECTOR3* getPosPointer(){ return &m_vPosition; }

	D3DXMATRIXA16* GetTransformMatrix()
	{
		D3DXMATRIXA16 matT, matYR, matXR, matZR;
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		D3DXMatrixRotationX(&matXR, m_fXAxisAngle);
		D3DXMatrixRotationY(&matYR, m_fYAxisAngle);
		D3DXMatrixRotationZ(&matZR, m_fZAxisAngle);
		m_matTransform = matXR * matYR * matZR * matT;
		return &m_matTransform;
	}
};


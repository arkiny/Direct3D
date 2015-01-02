#pragma once
class cCircleRHW
{
	std::vector<ST_RHWC_VERTEX>	m_vecVertex;
	float						m_fRadius;
public:
	cCircleRHW(void);
	~cCircleRHW(void);

	void Setup(D3DXVECTOR2 vCenter, float fRadius);
	void SetCenter(D3DXVECTOR2 vCenter);
	void Render();
};


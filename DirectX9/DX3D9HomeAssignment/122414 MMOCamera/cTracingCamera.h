#pragma once
class cTracingCamera
{
public:
	cTracingCamera();
	~cTracingCamera();
	void init();
	void updatePosition(D3DXVECTOR3& objPos);

	void moveforward(float unit);

	void rotateX(float degree);
	void rotateY(float degree);

private:
	D3DXMATRIX m_matView;
	D3DXVECTOR3 m_vEye, m_vLookAt, m_vUp;
	D3DXVECTOR3 m_vlength;
	D3DXVECTOR3					m_vecForward;
	float						m_fAngleDegree;
	float						m_fSpeed;
};


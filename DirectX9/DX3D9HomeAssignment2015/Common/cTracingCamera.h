#pragma once
class cTracingCamera
{
public:
	cTracingCamera();
	~cTracingCamera();
	void init();
	void update(float delta);

	void setTarget(D3DXVECTOR3& objPos);
	void moveforward(float unit);
	void rotateX(float degree);
	void rotateY(float degree);

	void backlook(D3DXVECTOR3& objfoward);

private:
	D3DXMATRIX					m_matView;
	D3DXVECTOR3					m_vEye, m_vLookAt, m_vUp;
	D3DXVECTOR3					m_vlength;
	D3DXVECTOR3					m_vecForward;

	D3DXVECTOR3*				m_pvTarget;

	float						m_fAngleDegree;
	float						m_fSpeed;
};


#pragma once

class cCube;
class iMap;

class cCubeMan
{
	enum eAnimation
	{
		E_ANIM_WALK,
		E_ANIM_IDLE
	};

private:
	eAnimation				m_eCurrAnim;
	//std::vector<cCube*>		m_vecCube;
	cCube*					m_pRoot;
	D3DXVECTOR3				m_vPosition;
	D3DXVECTOR3				m_vForward;
	float					m_fAngle;
	float					m_fSpeed;
public:
	cCubeMan(void);
	~cCubeMan(void);
	void Setup();
	void Update(iMap* pMap = NULL);
	void Render();
	D3DXVECTOR3& GetPosition()
	{
		return m_vPosition;
	}
	void SetCurrentAnimation(eAnimation a)
	{
		m_eCurrAnim = a;
	}
};


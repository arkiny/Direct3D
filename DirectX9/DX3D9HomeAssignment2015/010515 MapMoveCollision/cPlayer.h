#pragma once

class cPart;
class cMainGame;

class cPlayer
{
	enum eAnimation
	{
		E_ANIM_WALK,
		E_ANIM_IDLE,
		E_ANIM_ATTACK,
		E_ANIM_JUMP
	};

private:
	bool					m_bJumped = false;
	eAnimation				m_eCurrAnim;
	//std::vector<cCube*>		m_vecCube;
	cPart*					m_pRoot;
	cPart*					m_pFist;

	cMainGame*				m_pGame;
	bool					m_bAttacked = false;

	D3DXVECTOR3				m_vPosition;
	D3DXVECTOR3				m_vForward;
	float					m_fAngle;
	float					m_fSpeed;
	float					m_fAttackAnimationTime = 0.0f;
	const float				m_fHeight = 4.5f;

	float jumpSpeed = 100.0f;
	float jumpAccum = 0.0f;
	const float jumpLimit = 10.0f;
	float unit = 1.0f;

	float GetParabolaY(float x, float VERT_X, float VERT_Y);
	float m_fJumpAccumTime = 0.0f;
	float jumpStartedPosY;

public:
	cPlayer(void);
	~cPlayer(void);
	void Setup(cMainGame* game);
	void Update(float delta);
	void Render();

	GRIDPOSITION getGridCoord();
	D3DXVECTOR3& GetPosition()
	{
		return m_vPosition;
	}
	void SetCurrentAnimation(eAnimation a)
	{
		m_eCurrAnim = a;
	}
	void setPos(D3DXVECTOR3& pos){
		m_vPosition = pos;
	}
	float getHeight(){
		return m_fHeight;
	}

	D3DXVECTOR3& getFistPosition();

	bool isJumping(){ return m_bJumped; }
};


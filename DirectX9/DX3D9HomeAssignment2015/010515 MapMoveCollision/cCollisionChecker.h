#pragma once
class cCollisionChecker
{
public:
	cCollisionChecker();
	~cCollisionChecker();

	bool isCollided(
		D3DXVECTOR3& triP1,
		D3DXVECTOR3& triP2,
		D3DXVECTOR3& triP3,
		D3DXVECTOR3& StartingPoint);



private:
	float m_fDistance = 1000.0f;
};


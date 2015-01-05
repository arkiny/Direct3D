#include "stdafx.h"
#include "cCollisionChecker.h"


cCollisionChecker::cCollisionChecker()
{
}


cCollisionChecker::~cCollisionChecker()
{
}


bool cCollisionChecker::isCollided(
	D3DXVECTOR3& triP1,
	D3DXVECTOR3& triP2,
	D3DXVECTOR3& triP3,
	D3DXVECTOR3& StartingPoint){
	
	return D3DXIntersectTri(&triP1, &triP2, &triP3, &StartingPoint, &D3DXVECTOR3(0, -1.0f, 0), triP1, triP3, &m_fDistance);;
}
#include "stdafx.h"
#include "cMousePeeking.h"
#include "cPlain.h"
#include "cSphere.h"


cMousePeeking::cMousePeeking()
{
}


cMousePeeking::~cMousePeeking()
{
}


Ray& cMousePeeking::CalcPickRay(int x, int y){
	float px(0.0f);
	float py(0.0f);
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	D3DXMATRIXA16 proj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &proj);

	px = (((2.0f * x) / vp.Width) - 1.0f) / proj(0, 0);
	py = (((-2.0f*y) / vp.Height) + 1.0f) / proj(1, 1);

	Ray ret;
	ret._origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ret._direction = D3DXVECTOR3(px, py, 1.0f);

	return ret;
}

void cMousePeeking::TransformRay(Ray* pRay, D3DXMATRIXA16& T){
	D3DXMATRIXA16 mat = T;
	D3DXVec3TransformCoord(
		&pRay->_origin,
		&pRay->_origin,
		&T
		);
	D3DXVec3TransformNormal(
		&pRay->_direction,
		&pRay->_direction,
		&T
		);
}

D3DXVECTOR3& cMousePeeking::GetCrossSectionWithPlain(Ray* pRay, std::vector<D3DXVECTOR3>& vecPlain, OUT bool& isCrossed /*= false*/){
	D3DXVECTOR3 x(0, 0, 0), y(0, 0, 0), z(0, 0, 0);

	for (size_t i = 0; i < vecPlain.size() ; i++){
		x = vecPlain[i];
		y = vecPlain[++i];
		z = vecPlain[++i];

		D3DXVECTOR3 target(0, 0, 0);
		float dist;

		if (D3DXIntersectTri(&x, &y, &z, &pRay->_origin, &pRay->_direction, NULL, NULL, &dist)){
			target = pRay->_origin + (pRay->_direction*dist);
			isCrossed = true;
			return target;
		}
	}
	

	isCrossed = false;
	return D3DXVECTOR3(0, 0, 0);
	
}


bool cMousePeeking::IsCrossWithSphere(Ray* pRay, cSphere* pSphere){
	D3DXVECTOR3 q = pRay->_origin - pSphere->GetTransform()->GetPosition();
	float b = D3DXVec3Dot(&pRay->_direction, &q);
	float c = D3DXVec3Dot(&pRay->_direction, &pRay->_direction) * 
		(D3DXVec3Dot(&q, &q) - (pSphere->GetRadius() * pSphere->GetRadius()));

	float disc = (b*b) - c;
	
	// not real
	if (disc < 0.0f){
		return false;
	}
	else {
		return true;
	}
	return false;
}
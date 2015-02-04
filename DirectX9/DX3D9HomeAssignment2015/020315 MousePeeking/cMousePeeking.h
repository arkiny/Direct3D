#pragma once

struct Ray
{
	D3DXVECTOR3 _origin;
	D3DXVECTOR3 _direction;
};

class cSphere;

class cMousePeeking
{
private:

public:
	cMousePeeking();
	~cMousePeeking();

	// get ray from mouse position
	Ray& CalcPickRay(int x, int y);

	// Transform to world space
	void TransformRay(Ray* pRay, D3DXMATRIXA16& T);
	
	// Get Intersection with Pliant
	D3DXVECTOR3& GetCrossSectionWithPlain(Ray* pRay, std::vector<D3DXVECTOR3>& pPlain, OUT bool& isCrossed);
	
	// Is the Ray cross with the Sphere?
	bool IsCrossWithSphere(Ray* pRay, cSphere* pSphere);

};


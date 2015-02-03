#pragma once

struct Ray
{
	D3DXVECTOR3 _origin;
	D3DXVECTOR3 _direction;
};

class cPlain;
class cSphere;

class cMousePeeking
{
private:

public:
	cMousePeeking();
	~cMousePeeking();

	Ray& CalcPickRay(int x, int y); // get ray from mouse position

	void TransformRay(Ray* pRay, D3DXMATRIXA16& T);
	
	D3DXVECTOR3& GetCrossSectionWithPlain(Ray* pRay, std::vector<D3DXVECTOR3>& pPlain, OUT bool& isCrossed);
	bool IsCrossWithSphere(Ray* pRay, cSphere* pSphere);

};


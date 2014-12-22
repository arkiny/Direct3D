#pragma once
class cCamera
{
public:
	cCamera();
	~cCamera();
	void init();
	void update(float delta);

private:
	D3DVIEWPORT9 vp;
	D3DXVECTOR3 vEye;
	D3DXVECTOR3 vLookAt;
	D3DXVECTOR3 vUp;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProj;
};


#pragma once

#include "IObject.h"

#define PI 3.14159265f

class cObjectCircle : public IObject_Circle
{
public:
	cObjectCircle();
	cObjectCircle(D3DXVECTOR4 origin, float Rad);
	~cObjectCircle();

	void init();
	void update(float delta);
	void render();

	void ChangeOrigin(float x, float y);
	void ChangeColor(D3DCOLOR color);

	bool isCollide(IObject_Circle*);

	D3DXVECTOR4 getOrigin(){ return m_vOrigin; }
	float getRad(){ return m_fRad; }

	virtual void setPos(float x, float y){
		ChangeOrigin(x, y);
	}

	virtual float getRad() const {
		return m_fRad;
	}
	virtual D3DXVECTOR4 getPos() const{
		return m_vOrigin;
	}

	virtual bool isCollided(const IObject* target){
		return false;
	}


private:
	std::vector<ST_RHW_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9			m_pTexture;

	D3DXVECTOR4 m_vOrigin;
	D3DCOLOR m_stColor;
	float m_fRad;
	int m_nNumOfPoints = 360;
	//int m_stuff = 0;
	//int m_neg = 1;
};


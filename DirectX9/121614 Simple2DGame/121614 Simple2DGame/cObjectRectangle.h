#pragma once
#include "IObject.h"

class cObjectRectangle : public IObject
{
public:
	cObjectRectangle();
	cObjectRectangle(D3DXVECTOR4 origin, POINTFLOAT size);
	~cObjectRectangle();
	virtual void init();
	virtual void update(float delta);
	virtual void render();
	virtual D3DXVECTOR4 getPos() const;
	virtual float getRad() const;
	virtual void setPos(float x, float y);
	virtual bool isCollided(const IObject* target);

private:
	void updateNewPos();
	std::vector<ST_RHW_VERTEX>	m_vecVertex;
	D3DXVECTOR4					m_vOrigin;
	D3DCOLOR					m_stColor;
	POINTFLOAT					m_stSize;
};


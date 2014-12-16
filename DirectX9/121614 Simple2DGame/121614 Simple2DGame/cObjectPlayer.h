#pragma once

#include "IObject.h"

class cObjectPlayer : public IObject_Player
{
public:
	cObjectPlayer();
	~cObjectPlayer();

	virtual void init();
	virtual void update(float delta);
	virtual void render();

	virtual void setPos(float x, float y){
		m_vPosition.x = x;
		m_vPosition.y = y;
	}

	virtual D3DXVECTOR4 getPos() const{
		return m_vPosition;
	}
	virtual float getRad() const{
		return m_fCollisionRad;
	}

	virtual bool isCollided(const IObject* target);

private:
	void ChangePosUptoOrigin();

	POINTFLOAT m_stPlayerSize;
	std::vector<ST_RHW_PT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9					m_pTexture;

	IObject_Circle* m_pColisionCircle;
	D3DXVECTOR4 m_vPosition;
	float m_fCollisionRad;
};


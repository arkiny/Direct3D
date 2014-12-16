#pragma once

__interface IObject
{
	virtual void init() = 0;
	virtual void update(float delta) = 0;
	virtual void render() = 0;
	virtual D3DXVECTOR4 getPos() const = 0;
	virtual float getRad() const = 0;
	virtual void setPos(float x, float y);
	virtual bool isCollided(const IObject* target);
};

__interface IObject_Player : public IObject
{
};

__interface IObject_Shit : public IObject
{
	
};

__interface IObject_Circle : public IObject
{
	virtual D3DXVECTOR4 getOrigin();
	virtual void ChangeOrigin(float x, float y);
	virtual void ChangeColor(D3DCOLOR color);
	virtual bool isCollide(IObject_Circle*);
	
};
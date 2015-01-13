#pragma once

class cTransform;

class cGameObject : public cObject
{
protected:
	SYNTHESIZE(cTransform*, m_pTransform, Transform);

public:
	cGameObject();
	virtual ~cGameObject();

	virtual D3DXMATRIXA16* GetTransformMatrix();
};


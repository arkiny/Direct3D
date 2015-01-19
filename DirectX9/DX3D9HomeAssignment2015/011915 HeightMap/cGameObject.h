#pragma once
#include "cAction.h"
#include "cTransform.h"

class cGameObject : public cObject
{
protected:
	//SYNTHESIZE(cTransform*, m_pTransform, Transform);
	cTransform* m_pTransform;
	D3DXVECTOR3 m_vPrevPosition;
	float m_fAngle;

	cAction* m_pAction;

public:
	cGameObject();
	virtual ~cGameObject();

	virtual void				Update(float delta);
	virtual cTransform*			GetTransform();
	virtual D3DXMATRIXA16*		GetTransformMatrix();
	virtual void				SetAction(cAction* pAction);
};


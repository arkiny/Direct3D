#pragma once
#include "cAction.h"
#include "cTransform.h"

class cGameObject : public cObject
{
protected:
	enum eGameObjectState{
		E_IDLE,
		E_WALK
	};

	//SYNTHESIZE(cTransform*, m_pTransform, Transform);
	eGameObjectState m_eState = E_IDLE;
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
	virtual float				GetAngle(){ return m_fAngle; }
	virtual void				SetAngle(float delta){ m_fAngle = delta; }
	virtual void				SetAction(cAction* pAction);
	virtual void				SetPosition(D3DXVECTOR3& pos);
	virtual void				SetPosition(float x, float y, float z);
};


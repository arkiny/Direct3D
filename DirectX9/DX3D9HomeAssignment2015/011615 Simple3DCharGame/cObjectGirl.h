#pragma once
class cASEObject;
class cMyASELoader;

class cObjectGirl
{
private:
	cASEObject*				m_pRoot;
	D3DXVECTOR3				m_vPosition;
	cMyASELoader*			m_pASEObj;
	D3DXMATRIXA16			m_matworldMat;

public:
	cObjectGirl();
	~cObjectGirl();

	void setup();
	void update(float delta);
	void render();
};


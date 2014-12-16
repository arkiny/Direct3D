#pragma once
#include "IObject.h"
class cObject : public IObject
{
public:
	cObject();
	~cObject();
	virtual bool isCollided(const IObject* target);
};


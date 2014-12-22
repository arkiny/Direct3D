#include "stdafx.h"
#include "cObject.h"


cObject::cObject()
{
}


cObject::~cObject()
{
}

bool cObject::isCollided(const IObject* target){
	float hRange = abs(this->getPos().x - target->getPos().x);
	float vRange = abs(this->getPos().y - target->getPos().y);
	float collidingRange = this->getRad() + target->getRad();
	float range = (hRange*hRange) + (vRange*vRange);
	return range <= collidingRange* collidingRange;
}
#pragma once

__interface gIObject{
	void init();
	void update(float);
	void render();

	bool collidewith(gIObject* obj);
	bool collidewithPoint(D3DXVECTOR3& pos);

	// return world space coord
	D3DXVECTOR3& getWorldPosition();
	// return grid space position
	GRIDPOSITION& getGridPosition();

	// set position using grid system
	void setPositionByGrid(GRIDPOSITION& gridpos);
	// set position using worldCoordSystem
	void setPositionByWorldCoord(D3DXVECTOR3& pos);
};

__interface gIOBJECT_BOX : public gIObject{
	// get dmg
	void getHit(int dmg);
	void setHP(int hp);
	int getHP();
};

__interface gIOBJECT_PLAYER : public gIObject{

};
#pragma once
class cActionIdle : public cAction
{
public:
	cActionIdle();
	virtual ~cActionIdle();

	virtual void Start();
	virtual void Update(float delta);
};


#pragma once
class cObject
{
protected:
	int m_nRefCount;
public:
	cObject();
	~cObject();

	void AddRef(){
		_ASSERT(m_nRefCount > 0);
		m_nRefCount++;
	}

	void Release(){
		_ASSERT(m_nRefCount > 0);
		m_nRefCount--;
		if (m_nRefCount <= 0)
		{
			delete this;
		}
	}
};


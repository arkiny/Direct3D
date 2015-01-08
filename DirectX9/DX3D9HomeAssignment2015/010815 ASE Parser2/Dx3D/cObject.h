#pragma once
class cObject
{
protected:
	int m_nRefCount;

public:
	cObject(void);
	~cObject(void);

	void AddRef()
	{
		assert(m_nRefCount > 0);
		m_nRefCount++;
	}

	void Release()
	{
		assert(m_nRefCount > 0);
		m_nRefCount--;
		if (m_nRefCount <= 0)
		{
			delete this;
		}
	}
};


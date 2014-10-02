#pragma once

class BaseObj
{
	static cMemoryMgr memMgr;

public:
	void* operator new (size_t sz)
	{
		return memMgr.allocate(sz);
	}

	void operator delete (void* space, size_t sz)
	{
		memMgr.deallocate(space, sz);
	}

	BaseObj(void) {};
	virtual ~BaseObj(void) {};
};

cMemoryMgr BaseObj::memMgr;

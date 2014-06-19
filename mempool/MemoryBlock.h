#ifndef __MEMORYBLOCK_H__
#define __MEMOEYBLOCK_H__

#include "Define.h"
#include <iostream>

struct MemoryBlock
{
	ULONG	nSize;
	USHORT	nFree;
	USHORT	nFirst;
	USHORT	nDummyAlign1;
	MemoryBlock*	pNext;
	char	aData[1];
	
	static void* operator new(size_t nBlockSize, USHORT nInitSize, ULONG nUnitSize)
	{
		return ::operator new(nBlockSize + nInitSize * nUnitSize);
	}
	static void  operator delete(void* p, size_t)
	{
		::operator delete (p);
	}

	MemoryBlock(USHORT nInitSize = 1, ULONG nUnitSize = 0);
	~MemoryBlock()
	{
	}
};

#endif


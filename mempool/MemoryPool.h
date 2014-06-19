#ifndef __MEMORYPOOL_H__
#define __MEMORYPOOL_H__
#include "MemoryBlock.h"

class MemoryPool
{
private:
	MemoryBlock*	pBlock;
	ULONG			nUnitSize;
	USHORT			nInitSize;
public:
	MemoryPool(ULONG nUnitSize, USHORT nInitSize = 1024);
	~MemoryPool();
	void* 	Alloc();
	void	Free(void *p);
};

#endif

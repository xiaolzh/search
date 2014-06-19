#include "MemoryPool.h"

MemoryPool::MemoryPool(ULONG _nUnitSize, USHORT _nInitSize)
{
	pBlock		=	NULL;
	nInitSize	=	_nInitSize;

	if (_nUnitSize > 4)
	{
		nUnitSize = (_nUnitSize + (MEMPOOL_ALIGNMENT - 1)) & ~(MEMPOOL_ALIGNMENT - 1);
	}
	else if (_nUnitSize <= 2)
	{
		nUnitSize = 2;
	}
	else
	{
		nUnitSize = 4;
	}
}

void* MemoryPool::Alloc()
{
	if (!pBlock)
	{
		pBlock = new(nInitSize, nUnitSize) MemoryBlock(nInitSize, nUnitSize);
	}
	MemoryBlock* pMyBlock = pBlock;
	while (pMyBlock && !pMyBlock->nFree)
	{
		pMyBlock = pMyBlock->pNext;
	}
	if (pMyBlock)
	{
		char* pFree = pMyBlock->aData + (pMyBlock->nFirst * nUnitSize);
		pMyBlock->nFirst = *((USHORT*)pFree);

		pMyBlock->nFree--;
		return (void*)pFree;
	}
	else
	{
		pMyBlock = new(nInitSize, nUnitSize) MemoryBlock(nInitSize, nUnitSize);
		if (!pMyBlock)
		{
			return NULL;
		}

		pMyBlock->pNext = pBlock;
		pBlock = pMyBlock;

		return (void*)(pMyBlock->aData);
	}
}

void MemoryPool::Free(void* pFree)
{
	MemoryBlock* pMyBlock = pBlock;
	while (((ULONG)pMyBlock->aData > (ULONG)pFree) || ((ULONG)pFree >= ((ULONG)pMyBlock->aData + pMyBlock->nSize)))
	{
		pMyBlock = pMyBlock->pNext;		
	}
	pMyBlock->nFree++;
	*((USHORT*)pFree) = pMyBlock->nFirst;
	pMyBlock->nFirst = (USHORT)(((ULONG)pFree - (ULONG)(pMyBlock->aData))/nUnitSize);
	if (pMyBlock->nFree * nUnitSize == pMyBlock->nSize)
	{
	
	}
	else
	{
	
	}
}
MemoryPool::~MemoryPool()
{
	MemoryBlock* pMyBlock = pBlock;
	while (pMyBlock)
	{
	
	}
}


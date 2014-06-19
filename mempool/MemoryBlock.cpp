#include "MemoryBlock.h"

MemoryBlock::MemoryBlock(USHORT nInitSize, ULONG nUnitSize)
: nSize (nInitSize * nUnitSize),
  nFree (nInitSize - 1),
  nFirst (1),
  pNext (0)
{
	char* pData = aData;
	for (USHORT i = 1; i < nInitSize; i++)
	{
		*reinterpret_cast<USHORT*>(pData) = i;
		pData += nUnitSize;
	}
}

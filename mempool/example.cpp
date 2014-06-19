#include "MemoryPool.h"
#include <cstring>
#include <queue>

int main(int argc, char* argv[])
{ 
	int alloc = 0, free = 0;
	char* buf = NULL;
	MemoryPool* pool = new MemoryPool(UNITSIZE, INITSIZE);
	std::queue<ULONG> queue_ulong;
	while (!queue_ulong.empty())
	{
		queue_ulong.pop();
	}
	while (++alloc < 300000000)
	{
		buf = (char*)pool->Alloc();
		strcpy(buf, "This is an  example code of memory pool\n ");
		queue_ulong.push((ULONG)buf);
		if (alloc % 1000 == 0)
		{
			std::cout <<"Now Alloc num: "<<alloc <<std::endl;

			for (free = 0; free < 1000; free++)
			{
				buf = (char*)queue_ulong.front();
				pool->Free((void*)buf);
				queue_ulong.pop();
			}
			std::cout <<"Now Free num: " <<free <<std::endl;
		}
	}
	return 0;
}

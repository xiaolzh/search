#include "utility.h"  

int main()
{
	int i, j;
	int a[n] ={0};
	init(a);

	for (i =0; i < n - 1;i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (a[j] > a[j+1])
				swap(a[j], a[j+1]);
		}
	}
	output(a);
	return 0;
}

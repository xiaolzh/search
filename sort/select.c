#include "utility.h"

int main()
{
	int i, j, r, max;
	int a[n] = {0};
	init(a);
	for (i =0; i < n-1; i++)
	{
		max = 0;
		for (j =1; j < n-i;j++)
		{
			if (a[j]>a[max])
			{
				max = j;
			}
		}
		swap(a[max], a[n-i-1]);
	}
	output(a);
	return 0;
}

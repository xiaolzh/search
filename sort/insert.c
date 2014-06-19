#include "utility.h" 

int main()
{
	int a[n] = {0};
	int i, j, key;
	init(a);
	for (i = 1; i < n; i++)
	{
		j = i - 1;
		key = a[i];
		while (j >= 0 && a[j] > key)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
    output(a);
	return 0;
}

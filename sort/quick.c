#include "utility.h"

void quick_sort(int []);
void recursive_quicksort(int [], int, int);
int partition(int [], int, int);

int main()
{
	int a[n] = {0};
	init(a);
	quick_sort(a);
	output(a);
	return 0;
}

void quick_sort(int a[])
{
	recursive_quicksort(a, 0, n -1);
}

void recursive_quicksort(int a[], int p, int q)
{
	if (p < q)
	{
		int r = partition(a, p, q);
		recursive_quicksort(a, p, r - 1);
		recursive_quicksort(a, r + 1, q);
	}
}

int partition(int a[], int p, int q)
{
	int j, i = p - 1;
	int pivot = a[q];
	for (j = p; j <= q-1;j++)
	{
		if (a[j] < pivot)
		{
			i++;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[q]);
	return i + 1;
}


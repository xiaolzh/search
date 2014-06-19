#include "utility.h"

void merge_sort(int []);
void recursive_mergesort(int [], int, int);
void merge(int [], int, int, int);

int main()
{
	int a[n] = {0};
	init(a);
	merge_sort(a);
	output(a);
	return 0;
}

void merge_sort(int a[])
{
	recursive_mergesort(a, 0, n -1);
}

void recursive_mergesort(int a[], int p, int q)
{
	if (p < q)
	{
		int m = (p + q) /2;
		recursive_mergesort(a, p, m);
		recursive_mergesort(a, m + 1, q);
		merge(a, p, m, q);
	}
}

void merge(int a[], int p, int m, int q)
{
	int l = m -p +1;
	int r = q - m;
	int L[n], R[n];
	int i, j, k;
	for (i = 0; i < l; i++)
	{
		L[i] = a[p + i];
	}
	for (i = 0; i < r; i++)
	{
		R[i] = a[m + i + 1];
	}
	i = 0, j = 0;
	L[l] = INF;
	R[r] = INF;
	for (k = p; k <= q; k++)
	{
		if (L[i] < R[j])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
			j++;
		}
	}
}


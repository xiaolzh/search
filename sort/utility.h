#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <stdio.h>
#include <stdlib.h>

#define		n	100
#define		INF	2147483647

void swap(int &a, int &b)
{
	int temp;
	temp =a;
	a=b;
	b=temp;
}

void init(int a[])
{
	FILE* fp = NULL;
	fp = fopen("unordered.txt", "r");
	if (fp == NULL)
		return;
	for (int i=0;i<n;i++)
	{
		fscanf(fp, "%d", &a[i]);
	}
}

void output(int a[])
{
	for (int i =0; i<n;i++)
	{
		printf("%d\n", a[i]);
	}
}

#endif


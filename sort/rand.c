#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i =0;
	FILE* fp = NULL;
	fp = fopen("unordered.txt","w");
	if (fp == NULL)
		return -1;
	for (i =0; i < 100; i++)
	{
		fprintf(fp, "%d\n", rand()%100);
	}
	return 0;
}

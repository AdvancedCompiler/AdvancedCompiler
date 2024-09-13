#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include<malloc.h>
int main()
{
	int n, i;
	n = 100000000;
	float* a,*b,*c,*d;
	double Total_time;
	clock_t start, end;
	a = (float*)malloc(n*sizeof(float));
	b = (float*)malloc(n*sizeof(float));
	c = (float*)malloc(n*sizeof(float));
	d = (float*)malloc(n*sizeof(float));
	for (i = 0; i < n; i++)
	{
		a[i] = rand() % 10;
		b[i] = rand() % 10;

	}
	//优化前
	start = clock();
	for (i = 0; i < n; i++) {
		c[i] = a[i] + b[i];
		d[i] = a[i] - b[i];
	}
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("标量替换优化前：%lf秒\n",Total_time);
	free(a);
	free(b);
	free(c);
	free(d);
}
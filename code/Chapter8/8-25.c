#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
int main()
{
	int n, i;
	n = 10000000;
	int* a, * b, * c, * sum;
	clock_t start, end;
	double Total_time;
	a = (int*)malloc(n*sizeof(int));
	b = (int*)malloc(n*sizeof(int));
	c = (int*)malloc(n*sizeof(int));
	sum = (int*)malloc(n*sizeof(int));
	for (i = 0; i < n; i++)
	{
		a[i] = rand() % 10;
		b[i] = rand() % 10;
		c[i] = rand() % 10;
	}
	//优化前
	start = clock();
	for (int i = 0; i < n; i++)
		sum[i] = a[i] + b[i] + c[i];
	end = clock();
    Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("数组重组优化前：%lf秒\n",Total_time);
	free(a);
	free(b);
	free(c);
	free(sum);
}
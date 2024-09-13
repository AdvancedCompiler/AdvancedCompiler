#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
int main()
{
	int n, i;
	n = 100000000;
	float* a, * b;
	clock_t start, end;
	double Total_time;
	a = (float*)malloc(n * sizeof(float));
	b = (float*)malloc(n * sizeof(float));
	for (i = 0; i < n; i++)
	{
		a[i] = rand() % 10;
		b[i] = rand() % 10;
	}
	//优化前
	start = clock();
	for (int i = 1; i < n; i++)//这段代码后一次循环需要使用前一次循环写入内存的结果
		a[i] += a[i - 1];
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("减少内存读写优化前：%lf秒\n",Total_time);
	free(a);
	free(b);
	return 0;
}
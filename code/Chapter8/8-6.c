#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include<malloc.h>
int main()
{
	int n, i, j;
	n = 10000;
	float* a, ** b;
	clock_t start, end;
	double Total_time;
	a = (float*)malloc(n * sizeof(float));
	b = (float**)malloc(n * sizeof(float*));
	for (i = 0; i < n; i++)
	{
		a[i] = 0;
		b[i] = (float*)malloc(n * sizeof(float));
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			b[i][j] = rand() % 10;
		}
	}
	//优化后
	int sum;//使用sum将数组a的数据保存在寄存器中
	start = clock();
	for (i = 0; i < n; i++) {
		sum = a[i];//这样就可以减少对内存的写操作
		for (j = 0; j < n; j++) {
			sum = sum + b[i][j];
		}
		a[i] = sum;
	}
	end = clock();
	Total_time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("标量替换优化前：%lf秒\n", Total_time);
	for (i = 0; i < n; i++) {
		free(b[i]);
	}
	free(a);
	free(b);
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
int main()
{
	int n, i;
	n = 100000000;
	float* a, * b,temp;
	clock_t start, end;
	double Total_time;
	a = (float*)malloc(n * sizeof(float));
	b = (float*)malloc(n * sizeof(float));
	for (i = 0; i < n; i++)
	{
		a[i] = rand() % 10;
		b[i] = rand() % 10;
	}
	//优化后
	start = clock();
	temp = a[0];
	for (int i = 1; i < n; i++) {//通过保存临时中间计算结果减少一些内存访问
		temp += a[i];
		a[i] = temp;
	}
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("减少内存读写优化后：%lf秒\n",Total_time);
	free(a);
	free(b);
	return 0;
}
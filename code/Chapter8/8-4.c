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
	//优化后
	int x, y;
	start = clock();
	for (i = 0; i < n; i++) {//标量替换--标量替换后x和y的数据存入寄存器中
		x = a[i];//将数组a[i]的读取结果替换为x
		y = b[i];//将数组b[i]的读取结果替换为y
		c[i] = x + y;//每次迭代可以减少一次a数组和b数组的内存访问
		d[i] = x - y;
	}
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("标量替换优化后：%lf秒\n",Total_time);
	free(a);
	free(b);
	free(c);
	free(d);
}
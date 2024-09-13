#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<malloc.h>
int main()
{
	int n, i,j,phi=354;
	n = 10000;
	float** x, ** y;
	clock_t start, end;
	double Total_time;
	x =  (float**)malloc(n*sizeof(float*));
	y =  (float**)malloc(n*sizeof(float*));
	for (i = 0; i < n; i++)
	{
		x[i] = (float*)malloc(n*sizeof(float));
		y[i] = (float*)malloc(n*sizeof(float));
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			x[i][j] = rand() % 10;
			y[i][j] = rand() % 10;
		}
	}
	//优化前
	start = clock();
	for (int i = 0; i<n; i++) {
		x[i][1] = x[i][1] + phi * y[i][1];
		x[i][2] = x[i][2] + phi * y[i][2];
	}
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("数组转置优化后：%lf秒\n",Total_time);
	//优化后-此处省略矩阵转置代码
	start = clock();
	for (int i = 0; i < n; i++) {
		x[1][i] = x[1][i] + phi * y[1][i];
		x[2][i] = x[2][i] + phi * y[2][i];
	}
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("数组转置优化后：%lf秒\n",Total_time);
	for(i=0;i<n;i++){
	    free(x[i]);
	    free(y[i]);
	}
	free(x);
	free(y);
}
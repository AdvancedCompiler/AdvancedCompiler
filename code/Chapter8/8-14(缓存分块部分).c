#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#define Cache_length 64
int main()
{
	int n = 251, i, j, k;
	clock_t start, end;
	double Total_time;
	int Cache_len = 256;
	float** a, ** b, ** c, ** a1, ** b1, ** c1;
	a = (float**)malloc(n*sizeof(float*));
	a1 = (float**)malloc(Cache_len*sizeof(float*));
	b = (float**)malloc(n*sizeof(float*));
	b1 = (float**)malloc(Cache_len*sizeof(float*));
	c = (float**)malloc(n*sizeof(float*));
	c1 = (float**)malloc(Cache_len*sizeof(float*));
	for (i = 0; i < n; i++)
	{
		a[i] = (float*)malloc(n * sizeof(float));
		b[i] = (float*)malloc(n * sizeof(float));
		c[i] = (float*)malloc(n * sizeof(float));
	}
	for (i = 0; i < Cache_len; i++)
	{
		a1[i] = (float*)malloc(Cache_len * sizeof(float));
		b1[i] = (float*)malloc(Cache_len * sizeof(float));
		c1[i] = (float*)malloc(Cache_len * sizeof(float));
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			a[i][j] = rand() % 10;
			b[i][j] = rand() % 10;
			c[i][j] = 0;
		}
	}
	for (i = 0; i < Cache_len; i++) {
		for (j = 0; j < Cache_len; j++) {
			a1[i][j] = rand() % 10;
			b1[i][j] = rand() % 10;
			c1[i][j] = 0;
		}
	}
	start = clock();
	for (i = 0; i < Cache_len; i++)
	{
		for (j = 0; j < Cache_len; j++)
		{
			c1[i][j] = 0;
			for (k = 0; k < Cache_len; k++)
				c1[i][j] += a1[i][k] * b1[k][j];
		}
	}
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("256*256普通矩阵乘耗时： %lf秒\n", Total_time);
	start = clock();
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			c[i][j] = 0;
			for (k = 0; k < n; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("251*251普通矩阵乘耗时： %lf秒\n",  Total_time);
	for (i = 0; i < n; i++) {
		a[i] = (float*)realloc(a[i], sizeof(float) * Cache_len);
		b[i] = (float*)realloc(b[i], sizeof(float) * Cache_len);
	}
	for (i = 0; i < n; i++) {
		for (j = n; j < Cache_len; j++) {
			a[i][j] = 0;
			b[i][j] = 0;
		}
	}
	start = clock();
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			c[i][j] = 0;
			for (k = 0; k < n; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("列扩展后的矩阵乘耗时： %lf秒",  Total_time);
	for(i=0;i<n;i++){
	    free(a[i]);
		free(b[i]);
		free(c[i]);
	}
	for(i=0;i<Cache_len;i++){
	    free(a1[i]);
		free(b1[i]);
		free(c1[i]);
	}
	free(a);
    free(b);
	free(c);
	free(a1);
    free(b1);
	free(c1);
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
typedef struct {//提高数组局部性
	int a, b, c;
	int sum;
}arr_struct;
int main()
{
	int n, i;
	n = 10000000;
	int * sum;
	clock_t start, end;
	double Total_time;
	sum = (int*)malloc(n*sizeof(int));
	arr_struct* arr;
	arr = (arr_struct*)malloc(n*sizeof(arr_struct));
	for (i = 0; i < n; i++)
	{
		arr[i].a = rand() % 10;
		arr[i].b = rand() % 10;
		arr[i].c = rand() % 10;
	}
	//优化后
	start = clock();
	for (int i = 0; i < n; i++)
		arr[i].sum = arr[i].a + arr[i].b + arr[i].c;
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("数组重组优化后：%lf秒\n",Total_time);
	free(sum);
	free(arr);
}
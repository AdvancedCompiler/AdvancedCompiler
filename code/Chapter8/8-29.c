#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct {
	float t_x, v_x, d_x;//对整个结构的属性域进行调整，改进数组在内存中存放的连续性
	float t_y, v_y, d_y;
	float t_z, v_z, d_z;
} motion_1;
int main()
{
	int N = 10000000;
	int i, j;
	clock_t start, end;
	double Total_time;
	motion_1* P_1;
	P_1 = (motion_1*)malloc(N*sizeof(motion_1));
	for (i = 0; i < N; i++)
	{
		P_1[i].t_x = rand() % 10;
		P_1[i].v_x = rand() % 10;
	}
	start = clock();
	for (int i = 1; i <= N; i++) {
		P_1[i].d_x = P_1[i].t_x * P_1[i].v_x;
	}
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("结构属性域优化后：%lf秒\n",Total_time);
	free(P_1);
return 0;
}

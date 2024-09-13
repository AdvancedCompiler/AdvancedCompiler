#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct {
	float t_x, t_y, t_z;
	float v_x, v_y, v_z;
	float d_x, d_y, d_z;
} motion;
typedef struct {//可以利用结构体拆分的方法进行改写
	float t_x, v_x, d_x;
} motion_x;
typedef struct {
	float t_y, v_y, d_x;
	float t_z, v_z, d_z;
} motion_yz;
int main()
{
	int N = 10000000;
	int i, j;
	clock_t start, end;
	double Total_time;
	motion *P;
	motion_x* P_1;
	P = (motion*)malloc(N*sizeof(motion));
	P_1 = (motion_x*)malloc(N*sizeof(motion_x));
	for (i = 0; i < N; i++)
	{
		P[i].t_x = rand() % 10;
		P[i].v_x = rand() % 10;
		P_1[i].t_x = rand() % 10;
		P_1[i].v_x = rand() % 10;
	}
	start = clock();
	for (int i = 1; i<=N; i++) {
		P[i].d_x = P[i].t_x * P[i].v_x;
	}
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("结构拆分优化前：%lf秒\n",Total_time);
	start = clock();
	for (int i = 1; i <= N; i++) {
		P_1[i].d_x = P_1[i].t_x * P_1[i].v_x;
	}
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("结构属性域优化后：%lf秒\n",Total_time);
	free(P);
	free(P_1);
}
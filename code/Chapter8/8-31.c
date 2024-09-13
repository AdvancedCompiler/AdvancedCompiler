#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<malloc.h>
#define N 100000
typedef struct {
	float t_x, t_y, t_z;
	float v_x, v_y, v_z;
	float d_x, d_y, d_z;
} motion;
typedef struct {
	float Pt_x[N];
	float Pv_x[N];
	float Pd_x[N];
} motion_x;
int main(){
	int i, j;
	clock_t start, end;
	double Total_time;
	motion *P;
	motion_x P_1;
	P = (motion*)malloc(N*sizeof(motion));
	for (i = 0; i < N; i++)
	{
		P[i].t_x = rand() % 10;
		P[i].v_x = rand() % 10;
		P_1.Pt_x[i] = rand() % 10;
		P_1.Pv_x[i] = rand() % 10;
		P_1.Pd_x[i] = rand() % 10;
	}
	start = clock();
	for (int i = 1; i<=N; i++) {
		P[i].d_x = P[i].t_x * P[i].v_x;
	}
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("结构体数组转为数组结构体优化前：%lf秒\n",Total_time);
	start = clock();
	for (int i = 1; i<=N; i++)
		P_1.Pd_x[i] = P_1.Pt_x[i] * P_1.Pv_x[i];
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("结构体数组转为数组结构体优化后：%lf秒\n",Total_time);
	free(P);
return 0;
}
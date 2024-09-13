#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct {
	float t_x, t_y, t_z;//x维的时间t_x、速度v_x和位移d_x在内存中并不是连续存放的
	float v_x, v_y, v_z;
	float d_x, d_y, d_z;
} motion;
int main()
{
	int N = 10000000;
	int i, j;
	clock_t start, end;
	double Total_time;
	motion *P;
	P = (motion*)malloc(N*sizeof(motion));
	for (i = 0; i < N; i++)
	{
		P[i].t_x = rand() % 10;
		P[i].v_x = rand() % 10;
	}
	start = clock();
	for (int i = 1; i<=N; i++) {
		P[i].d_x = P[i].t_x * P[i].v_x;
	}
	end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("结构属性域优化前：%lf秒\n",Total_time);
	free(P);
return 0;

}
#include <stdio.h>
#define N 8
int main() {
    int A1[N],A2[N];
	int A3[N][N];
    int i, j;
	//顺序访问
	for (i = 0; i < N; i++)
		A1[i] = i + 1;
	printf("顺序访问\n ");
	for (i = 0; i < N; i++)
		printf("%d  ",A1[i]);
	//逆序访问
	for (i = N-1; i >= 0; i--)
		A2[i] = i + 1;
	printf("\n逆序访问\n ");
	for (i = 0; i < N; i++)
		printf("%d  ", A2[i]);
	//固定步幅的跳步式访问
	for (i = 0 ;i < N;i++)
		for (j = 0 ; j < N;j++)
			A3[j][i] = i + j;
	printf("\n固定步幅的跳步式访问\n ");
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			printf("%d  ", A3[i][j]);
}
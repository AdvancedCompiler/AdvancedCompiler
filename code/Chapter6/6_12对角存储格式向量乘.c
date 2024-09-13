#include <stdio.h>
const static int SIZE = 4; // 矩阵的大小
const static int NNZ = 9; //非零元素的数量
const static int NUM_ROWS = 4;// 列长;
typedef int DTYPE;
#define X -1
void matrixvector(DTYPE A[SIZE][SIZE], DTYPE* y, DTYPE* x)//常规的矩阵向量乘
{
	for (int i = 0; i < SIZE; i++) {
		DTYPE y0 = 0;
		for (int j = 0; j < SIZE; j++)
			y0 += A[i][j] * x[j];
		y[i] = y0;
	}
}
void spmv(DTYPE data[12], int offsets[SIZE - 1], DTYPE y[SIZE], DTYPE x[SIZE]) {//CSR行压缩存储的矩阵向量乘
	int i, j, k, N;
	int Istart, Jstart, stride = 4;
	for (i = 0; i < SIZE - 1; i++) {
		k = offsets[i];
		Istart = max(0, -k);
		Jstart = max(0, k);
		N = min(SIZE - Istart, SIZE - Jstart);
		for (j = 0; j < N; j++) {
			if (data[Istart + i * stride + j] != X)////其中X对应源数组的*表示不存在该数
				y[Istart + j] += data[Istart + i * stride + j] * x[Jstart + j];
		}
	}
}
int main() {
	int fail = 0;
	DTYPE M[SIZE][SIZE] = { {1,5,0,0},{0,2,6,0},{8,0,3,7},{0,9,0,4} };
	DTYPE x[SIZE] = { 1,2,3,4 };
	DTYPE y_sw[SIZE];
	DTYPE data[12] = { X,X,8,9,1,2,3,4,5,6,7,X };
	int offsets[SIZE - 1] = { -2,0,1 };
	DTYPE y[SIZE] = { 0 };
	spmv(data, offsets, y, x);
	matrixvector(M, y_sw, x);
	for (int i = 0; i < SIZE; i++)//判断两次矩阵相量乘的结果是否一样
		if (y_sw[i] != y[i])
			fail = 1;
	if (fail == 1)
		printf("FAILED\n");
	else
		printf("PASS\n");
	printf("矩阵M为：\n");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf("%d  ", M[i][j]);
		}
		printf("\n");
	}
	printf("向量X为\n");
	for (int i = 0; i < SIZE; i++) {
		printf("%d\n", x[i]);
	}
	printf("矩阵向量乘的积为\n");
	for (int i = 0; i < SIZE; i++) {
		printf("%d\n", y[i]);
	}
	return fail;
}
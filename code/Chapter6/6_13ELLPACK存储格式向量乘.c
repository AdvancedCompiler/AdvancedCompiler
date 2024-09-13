#include <stdio.h>
#include<math.h>
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
void spmv(DTYPE data[12], int indices[12], DTYPE y[SIZE], DTYPE x[SIZE]) {//CSR行压缩存储的矩阵向量乘
	int n, i, k, N;
	int max_ncols = SIZE - 1, num_rows = SIZE;
	for (n = 0; n < max_ncols; n++)
		for (i = 0; i < num_rows; i++)
			if (data[n * num_rows + i] != X)
				y[i] += data[n * num_rows + i] * x[indices[n * num_rows + i]];
}
int main() {
	int fail = 0;
	DTYPE M[SIZE][SIZE] = { {1,5,0,0},{0,2,6,0},{8,0,3,7},{0,9,0,4} };
	DTYPE x[SIZE] = { 1,2,3,4 };
	DTYPE y_sw[SIZE];
	DTYPE data[12] = { 1,2,8,9,5,6,3,4,X,X,7,X };
	DTYPE indices[12] = { 0,1,0,1,1,2,2,3,X,X,3,X };
	DTYPE y[SIZE] = { 0 };
	spmv(data, indices, y, x);
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
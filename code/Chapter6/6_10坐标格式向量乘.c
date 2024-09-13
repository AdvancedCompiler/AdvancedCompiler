#include <stdio.h>
const static int SIZE = 4; // 矩阵的大小
const static int NNZ = 9; //非零元素的数量
const static int NUM_ROWS = 4;// 列长;
typedef int DTYPE;
void matrixvector(DTYPE A[SIZE][SIZE], DTYPE* y, DTYPE* x) {//常规的矩阵向量乘
	for (int i = 0; i < SIZE; i++) {
		DTYPE y0 = 0;
		for (int j = 0; j < SIZE; j++)
			y0 += A[i][j] * x[j];
		y[i] = y0;
	}
}
void spmv(int row[NNZ], int col[NNZ],DTYPE values[NNZ], DTYPE y[SIZE], DTYPE x[SIZE]) {//CSR行压缩存储的矩阵向量乘
	int i;
	for (i = 0; i < SIZE; i++) {
		y[i] = 0;
	}
	for ( i = 0; i < NNZ; i++)
		y[row[i]] += values[i] * x[col[i]];
}
int main() {
	int fail = 0;
	DTYPE M[SIZE][SIZE] = { {1,5,0,0},{0,2,6,0},{8,0,3,7},{0,9,0,4} };
	DTYPE x[SIZE] = { 1,2,3,4 };
	DTYPE y_sw[SIZE];
	DTYPE values[] = { 1,5,2,6,8,3,7,9,4 };
	int col[] = { 0,1,1,2,0,2,3,1,3 };
	int row[] = { 0,0,1,1,2,2,2,3,3};
	DTYPE y[SIZE];
	spmv(row, col, values, y, x);
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
#include<stdio.h>
#include<stdlib.h>
#define N 10
int main()
{
	int A[N] = { 1,2,3,4,5,6,7,8,9,10 };
	int B[N] = { 1,2,3,4,5,6,7,8,9,10 };
	int Y[N] = { 0 };
	int A1[N] = { 0 };
	int X = 1, Z = 1, C = 1;
	for (int i = 1; i < N; i++) {
		A1[i] = A[i - 1] + X; //S1语句
		Y[i] = A1[i] + Z;  //S2语句
		A[i] = B[i] + C;   //S3语句
	}
}
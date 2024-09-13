#include<stdlib.h>
#include<stdio.h>
int main() {
	int A[10] = { 1,23,4,26,3,2,6,7,8,5 };
	int N = sizeof(A) / sizeof(int);
	int T;
	int B[10] = { 0 };
	for (int i = 1; i < N; i++) {
		T = A[i];
		A[i] = B[i];
		B[i] = T;
	}
}
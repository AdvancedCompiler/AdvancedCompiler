#include <stdio.h>
#include<stdlib.h>
#define N 8
int main() {
	int A[20] = {0}, i, j, k;
	j = rand() % 10;
	k = 1;
	for (int i = 0; i < N; i++) {
		A[i + j] = A[i] + k;
	}
	for (int i = 0; i < 20; i++) {
		printf("%d  ", A[i]);
	}
}
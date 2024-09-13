#include <stdio.h>
#define N 256 
int main() {
	int i, j;
	int C = 5, D = 6;
float A[N], B[N];
	for (i = 0; i < N; i++)
		A[i] = i;
	for (i = 0; i < N; i++) {
		A[i + 1] = A[i] + C;//S1语句
		B[i] = B[i] + D;//S2语句
	}
}
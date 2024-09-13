#include<stdio.h>
#define N 100
int a[N], b[N], c[N];
int i;
int main() {
	for (i = 0; i < N; i++)
		a[i] = b[i] * c[i];
}
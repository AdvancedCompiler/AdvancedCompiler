#include<stdlib.h>
#include<stdio.h>
int main() {
	int a[10] = { 0,1,2,3,4,5,6,7,8,9 };
	int x = a[0];
	int N = sizeof(a) / sizeof(int);
	for (int i = 1; i < N; i++) {
		if (a[i] > x) //S1语句
			x = a[i];// S2语句
	}
	printf("x=%d", x);
}
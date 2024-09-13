#include<stdlib.h>
#include<stdio.h>
int main() {
	int a = 2, b = 3;
	a = (a + a) + (6 * a) / 2;
	b = (b + b) + (6 * b) / 2;
	printf("a=%d,b=%d", a, b);
}
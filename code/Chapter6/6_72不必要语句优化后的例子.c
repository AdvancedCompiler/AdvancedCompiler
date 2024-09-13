#include<stdio.h>
int main() {
	int a = 1, b = 2;
	int c;
	c = a + b;
	a = (b > 0 ? a : b);// S语句
	c = a - b;
}
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a = 1, b = 5;
	int tmp = a + b;//改进后只需计算一次a+b的值
	if (tmp > 3 && tmp < 10) {
		a = a + b;
	}
	printf("%d", a);
}
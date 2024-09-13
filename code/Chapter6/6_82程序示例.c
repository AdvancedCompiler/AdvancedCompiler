#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a = 1, b = 5;//改进前，重复计算两次a+b的值
	if ((a + b) > 3 && (a + b) < 10) {
		a = a + b;
	}
	printf("%d", a);
}
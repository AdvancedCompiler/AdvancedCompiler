#include<stdio.h>
int main(){
int a1 = 1, a2 = 2, a3 = 3;
	int a = 4, b = 5;
	//改进后
	int temp = (a1 && a2 && a3);
	printf("%d\n", temp);
	if (temp != 0) {//简化分支判断条件，提高流水线性能
		a = a + b;
	}
	printf("合并判断条件可以简化分支判断条件，提高流水线性能。\n");
    return 0;
}
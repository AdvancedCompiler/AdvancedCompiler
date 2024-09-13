#include<stdio.h>
int main(){
	int a1 = 1, a2 = 2, a3 = 3;
	int a = 4, b = 5;
	//改进前
	if ((a1 != 0) && (a2 != 0) && (a3 != 0)) {
		a = a + b;
	}
	printf("分支判断条件是复杂表达式,会对处理器流水线的运行产生一定的影响。\n");
return 0;
}
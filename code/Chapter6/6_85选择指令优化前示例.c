#include<stdio.h>
int main()
{
	int x;
	int a = 4, b = 5;
	//改进前
	if (a > 0) 
		x = a;
	else 
		x = b;
	//改进后--将分支判断移除其生成一条选择指令 
	x = (a > 0 ? a : b);
	printf( "生成选择指令，移除分支判断可以实现优化。\n");
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int score = 0;
	printf("请输入你的成绩：");
	scanf_s("%d", &score);
	if (score >= 90)  //score属于（0...100）    
		printf("A");
	else if (score >= 80)
		printf("B");
	else if (score >= 70)
		printf("C");
	else
		printf("D");
}
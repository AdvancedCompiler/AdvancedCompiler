#include<stdio.h>
#include<stdlib.h>
int main()
{
	int score = 0;
	printf("请输入你的成绩：");
	scanf_s("%d", &score);
	char s[] = { 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'C', 'B', 'A' };
	printf("%c", s[score / 10]);
}
#include<stdio.h>
void bubble_sort(int a[], int n)
{
	int i, j, temp;
	for ( j = 0; j < n - 1; j++)//总共需要冒泡多少次数
	{
		for ( i = 0; i < n - 1 - j; i++)
		{
			if (a[i] > a[i + 1])
			{
				temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;//交换操作

			}
		}
	}
}
int main() {
	int a[7] = { 3,6,4,2,11,10,5 };
	bubble_sort(a, 7);
	for (int k = 0; k < 7; k++)
	{
		printf("%d\t", a[k]);
	}
	return 0;
}
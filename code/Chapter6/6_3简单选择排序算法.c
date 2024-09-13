#include<stdio.h>
void selectSort(int a[], int len)
{
	int i, j, temp;
	int minIndex = 0;
	for (i = 0; i < len - 1; i++)
	{
		minIndex = i;
		for (j = i + 1; j < len; j++)
		{
			if (a[j] < a[minIndex])
			{
				minIndex = j;//min就是待排序中最小元素,找到每次最小的元素
			}
		}
		if (minIndex != i) {
			temp = a[i];
			a[i] = a[minIndex];
			a[minIndex] = temp;
		}
	}
}
int main()
{
	int a[]= { 3,6,4,2,11,10,5 };
	selectSort(a, 7);
	for (int k = 0; k < 7; k++)
	{
		printf("%d\t", a[k]);
	}
}
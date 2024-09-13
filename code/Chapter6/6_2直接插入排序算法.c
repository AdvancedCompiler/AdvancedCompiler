#include<stdio.h>
#include <assert.h>
void insertSort(int *arr, size_t size)
{
	assert(arr);
	for (int idx = 1; idx <= size - 1; idx++)//idx表示插入次数，共进行n-1次插入
	{
		int end = idx;
		int temp = arr[end];
		while (end > 0 && temp < arr[end - 1])//while循环的作用是将比当前元素大的元素都往后移动一个位置
		{
			arr[end] = arr[end - 1];
			end--;
		}
		arr[end] = temp; //元素后移后要插入的位置就空出了，找到该位置插入
	}
}
int main()
{
	int arr[]= { 3,6,4,2,11,10,5 };
	insertSort(arr, 7);
	for (int k = 0; k < 7; k++)
	{
		printf("%d\t", arr[k]);
	}
	return 0;
}
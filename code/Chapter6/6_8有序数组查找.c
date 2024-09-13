#include<stdio.h>
#include <malloc.h>
#include <sys/time.h>
int Bin_Search(int* num, int cnt, int target){
	int first = 0, last = cnt - 1, mid;
		int counter = 0;
		while (first <= last) {
			counter++;
			mid = (first + last) / 2;//确定中间元素	
				if (num[mid] > target) {
					last = mid - 1; //mid已经交换过了，last往前移一位
				}
				else if (num[mid] < target) {
					first = mid + 1;//mid已经交换过了，first往后移一位
				}
				else { //判断是否相等
					return 1;
				}
		}
		return 0;
}
int main(void) {
	struct timeval start,end;
	int flag = 0;
	int n = 10000000;
	int *num = malloc(n*sizeof(int));
	for (int i = 0; i < n; i++) {
		num[i] = i;
	}
	gettimeofday(&start,NULL);
	flag = Bin_Search(num, n, n-1);
	if (flag) printf("已经找到该数字!!\n");
	else printf("无该数字!!\n");
	gettimeofday(&end, NULL);
	double timeuse = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/ 1000000.0 ;
	printf("time=%f\n", timeuse);
    free(num);
	return 0;
}
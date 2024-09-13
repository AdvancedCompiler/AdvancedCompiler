#include<stdio.h>
int max(int a, int b){
	if (a > b)
		return a;
	else
		return b;
}
int main() {
	int x[] = { 8, -33, 16, 9, -12, 45, 67 };
	int maxsum =-0x3f3f3f3f;
    int n=sizeof(x)/sizeof(int);
	int sum;
	for (int i = 0; i < n; i++){
		sum = 0;
		for (int j = i; j < n; j++){
			sum += x[j];
			maxsum = max(maxsum, sum);
		}
	}
	printf("%d", maxsum);
}
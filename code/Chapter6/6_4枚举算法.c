#include<stdio.h>
int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}
int main(){
	int maxsum =  -0x3f3f3f3f;
	int x[] = { 8, -33, 16, 9, -12, 45, 67  };
	int n = sizeof(x) / sizeof(int);
	int ans = 0;
	int sum = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j <= i; j++){
			sum = 0;
			for (int k = j; k <= i; k++){
				sum += x[k];
			}
			ans = max(ans, sum);
		}
	}
	printf("%d", ans);
}
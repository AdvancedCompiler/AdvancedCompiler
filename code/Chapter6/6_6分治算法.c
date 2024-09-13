#include<stdio.h>
#include<stdlib.h>
int max1(int a, int b){
	if (a > b) return a;
	else return b;
}
int x[] = { 8, -33, 16, 9, -12, 45, 67 };
int maxsubsum(int l, int r){
	if (l == r) return x[0];
	int maxsum;
	int mid = (l + r) / 2;
	int leftmax = maxsubsum(l, mid);
	int rightmax = maxsubsum(mid + 1, r);
	maxsum = max1(leftmax, rightmax);
	int t = 0;
	int left = x[mid];
	for (int i = mid; i >= 0; i--){
		t += x[i];
		left = max1(left, t);
	}
	int right = x[mid + 1];
	t = 0;
	for (int i = mid + 1; i <= r; i++){
		t += x[i];
		right = max1(right, t);
	}
	maxsum = max1(maxsum, left + right);
	return maxsum;
}
int main(){
	printf("%d", maxsubsum(0, 6));
	return 0;
}
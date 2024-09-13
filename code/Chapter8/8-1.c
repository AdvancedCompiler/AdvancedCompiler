#include<stdio.h>
#include<malloc.h>
float x=5.5642;//一个随机的float值
void function(float *a,int N){
	int i;
	float phi=2.541, delta, alpha;
	delta = x * x;
	alpha = x / 2;
	for (i = 0; i < N; i++)
		a[i] = x * phi;
}
int main()
{
	float* a;
	int n=100;
	a = (float*)malloc(n * sizeof(float));
	function(a,n);
	free(a);
	return 0;
}
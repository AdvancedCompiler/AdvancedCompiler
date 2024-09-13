#include <stdio.h>
#include <emmintrin.h>
#include <time.h>
int main() {
	clock_t start, end;
	double Total_time;
	//int
	int op3[4] = { 11,22,33,44 };
	int op4[4] = { 22,33,44,55 };
	//short
	short op1[8] = { 11,22,33,44,55,77,66,88 };
	short op2[8] = { 22,33,44,55,11,44,22,77 };
	short result1[8];
	int result2[4];
	__m128i x, y, z;
	//用SSE指令进行一次int数据加法运算
	start = clock();
	x = _mm_loadu_si128((__m128i*)op3);
	y = _mm_loadu_si128((__m128i*)op4);
	z = _mm_add_epi32(x, y);
	_mm_store_si128((__m128i*)result2, z);
	end = clock();
	printf("int数据向量加结果:" );
	for (int i = 0; i < 4; i++) {
		printf("%d ", result2[i]);;
	}
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("\nint数据向量加耗费时间:%lfus\n",Total_time);
	//用SSE指令进行一次short数据加法运算
	__m128i x1, y1, z1;
	start = clock();
	x1 = _mm_loadu_si128((__m128i*)op1);
	y1 = _mm_loadu_si128((__m128i*)op2);
	z1 = _mm_add_epi16(x1, y1);
	_mm_store_si128((__m128i*)result1, z1);
	end = clock();
	printf("short数据向量加结果");
	for (int i = 0; i < 8; i++) {
		printf("%d ", result1[i]);;
	}
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("\nshort数据向量加耗费时间:%lfus\n", Total_time);
}
#include <stdio.h>
int a = 1;
void func(int *a) {
	int c = 14;
	*a = *a + c;
}
int main() {
	func(&a);
	printf("%d", a);
}
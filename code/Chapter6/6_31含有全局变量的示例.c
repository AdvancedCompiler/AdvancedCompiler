#include <stdio.h>
int a = 1;
void func() {
	int c = 14;
	a = a + c;
}
int main() {
	func();
	printf("%d", a);
}
#include <stdio.h>
#include <stdlib.h>
int main ()
{
	int a,b,c;
	a = rand();
	b = rand();
	c = a + b*3;
	b = a;
	return c;
}


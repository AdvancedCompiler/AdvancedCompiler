#include <stdio.h>
void func(int x,int y, int z, int a, int b,int c){
    x=a+b;
    y=b+c;
    z=a+c;
}
int main()
{
    int x,y,z,a,b,c;
a=1,b=2,c=3;
func(x,y,z,a,b,c);
    printf("参数过多会产生额外开销\n");
    return 0;
}
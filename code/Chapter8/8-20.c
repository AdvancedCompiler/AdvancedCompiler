#include<stdio.h>
struct BeforeAdjust{
   char a;
   int b;
   char c;
   short d;
};
int main() {
    printf("BeforeAdjust结构体所占大小为:%d\n",sizeof(struct BeforeAdjust));
    return 0;
}
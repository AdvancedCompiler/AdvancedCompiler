#include<stdio.h>
#define ON_ARM_处理器 1
#define ON_X86_处理器 2
void arm_f() {
    printf("ON_ARM_处理器\n");
}
void  x86_f(){
    printf("ON_X86_处理器\n");
}
int main()
{
    int mode = ON_ARM_处理器;
    printf("条件分支代码:");
    switch (mode) {
    case ON_ARM_处理器:   arm_f(); break;
    case ON_X86_处理器:    x86_f(); break;
    }
    return 0;
}
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
    printf("条件编译代码:");
    #ifdef ON_ARM_处理器      
        arm_f();
    #elif ON_X86_处理器       
        x86_f();
    #endif
    return 0;
}
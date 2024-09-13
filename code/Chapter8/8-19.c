#include<stdio.h>
struct AlignA {
    char a;
    long b;
    int c;
};
int main() {
    char a;
    long b;
    int c;
    printf("AlignA中各成员所占空间大小和为:%d\n",sizeof(a) + sizeof(b) + sizeof(c));
    printf("整个AlignA结构体所占大小为:%d\n",sizeof(struct AlignA));
    return 0;
}
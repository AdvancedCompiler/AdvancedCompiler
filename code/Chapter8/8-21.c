#include<stdio.h>
struct AfterAdjust {
    char a;
    char c;
    short d;
    int b;
};
int main() {
    printf("AfterAdjust结构体所占大小为: %d\n",sizeof(struct AfterAdjust));
    return 0;
}
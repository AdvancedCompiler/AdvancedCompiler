#include <stdio.h>
struct Param {
    int x;
    int y;
    int z;
    int a;
    int b;
    int c;
};
void func(struct Param* p) {
    p->x = p->a + p->b;
    p->y = p->b + p->c;
    p->z = p->a + p->c;
}
int main()
{
    struct Param p;
    p.a = 1;
    p.b = 2;
    p.c = 3;
    func(&p);
    printf("传递一个指针可以大大减少函数调用时传递参数的开销\n");
    return 0;
}
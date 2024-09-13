#include<stdio.h>
#include<unistd.h>
#define n 100
#define m 10
int x,i,j;
unsigned long rpcc(){
        unsigned long result;
        unsigned hi,lo;
        asm volatile("rdtsc":"=a"(lo),"=d"(hi));
        result = ((unsigned long long)lo)|(((unsigned long long)hi)<<32);
        return result;
}
void fun(int a){
        for(i=0;i<n;i++)
                x=(a/4)+i;
}
int main()
{
        unsigned long b[m],start ,end,k;
        for(j=0;j<10;j++){
                start = rpcc();
                fun(16);
                end = rpcc();
                b[j]=end -start;
                k+=b[j];
        }
        printf("time = %ld\n",k/m);
}                      
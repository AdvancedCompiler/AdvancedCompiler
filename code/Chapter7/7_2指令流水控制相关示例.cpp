//����7.2 �����в��������Կ��Բ��ý�if��֧����ᵽѭ����
#include <stdio.h>
#include <stdlib.h>

#define N 10
int main(){
        int a[N];
        int d[N];
        int c[N];
        int m[N];
        int n[N];
        int an = rand()%100;
        printf("an=%d\n",an);
        for(int i = 0; i < N; i++)
        {
                a[i] = 0;
                m[i]=0;
                c[i]=i;
                d[i]=i+1;
                n[i]=i+2;
        }
    if(an>10)
        {
                for(int i = 0; i < N; i++)
                {
                        a[i]=c[i];
                        m[i]=n[i];
                }
        }
        else
        {
                for(int i = 0; i < N; i++)
                {
                        a[i]=d[i];
                        m[i]=n[i];
                }
        }
        for(int i=0; i<N; i++)
        {
                printf("a[%d]=%d m[%d]=%d\n",i,a[i],i,m[i]);
        }
 
return 0;
}


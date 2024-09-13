#include <stdio.h>
#define N 10240
int main(){
        int a[N],b[N],c[N];
        int i;
        for (i = 0; i < 10240;i++){
                b[i] = i;
                c[i] = i+1;
        }
        for (i = 0; i < 10240;i+=4){
                a[i] = b[i] + c[i];
                a[i+1] = b[i+1] + c[i+1];
                a[i+2] = b[i+2] + c[i+2];
                a[i+3] = b[i+3] + c[i+3];
        }        
return a[100];
}


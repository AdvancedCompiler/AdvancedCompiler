extern int shared;
int main(void){
  int a=100;
 add(&a,&shared);
 printf("%d",a);
}


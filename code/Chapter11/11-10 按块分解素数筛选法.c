#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<mpi.h>
#define MAX_PRIME 100000001
int main(int argc,char **argv){
    //shift、volume为每个进程的偏移量、任务量
    //left为将任务划分后，剩余的不够平均分配的任务量
    int shift,volume,left;
    double start,end;
    char *prime;
    int my_rank,world_size,index,i;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    //计算偏移量及任务量
    left=MAX_PRIME%world_size;
    if(my_rank<left){
        volume=MAX_PRIME/world_size+1;
        shift=my_rank*volume;
    }else{
        volume=MAX_PRIME/world_size;
        shift=left*(volume+1)+(my_rank-left)*volume;
    }
    //当0进程的范围不能产生所有的未被标记数时，程序终止。
    if(my_rank==0){
        if(volume<sqrt(MAX_PRIME)){
            printf("进程数太多，素数上限太小\n");
            //终止MPI_COMM_WORLD下所有进程运行
            MPI_Abort(MPI_COMM_WORLD,0);
        }
    }
    //分配存储空间
    prime=malloc(sizeof(char)*volume);
    //标记2的倍数
    for(i=shift;i<shift+volume;i++){
        if(i%2==0){
            prime[i-shift]='n';
        }else{
            prime[i-shift]='y';
        }
    }
    if(my_rank==0){
        prime[0]=prime[1]='n';
        prime[2]='y';
    }
    //初始index设为3，之后由root进程产生index并广播
    start=MPI_Wtime();
    index=3;

    while(index*index<=MAX_PRIME){
        //定位到开始执行筛选的位置
        if(my_rank==0){
            i=index*2;
        }else{
            i=0;
            if(shift%index!=0){
                i+=index-shift%index;
            }
        }
        //将index的倍数标记为非素数
        for(;i+shift<volume+shift;i+=index){
            prime[i]='n';
        }
        //在0进程选择新的未标记数，之后广播到其他进程
        if(my_rank==0){
            for(i=index+1;i<volume;i++){
                if(prime[i]=='y'){
                    index=i;
                    break;
                }
            }
        }
        MPI_Bcast(&index,1,MPI_INT,0,MPI_COMM_WORLD);
    }
    end=MPI_Wtime();
    printf("进程%d的运行时间为:%lf\n",my_rank,(end-start));
    free(prime);
    MPI_Finalize();
    return 0;
}
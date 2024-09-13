#include<stdio.h>
#include<mpi.h>
int main(int argc,char *argv[]) 
{ 
     int world_rank,world_size,send,recv;
     MPI_Status status;
     MPI_Init(&argc,&argv); 
     MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
     MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    if(world_rank==0){
        send=666; 
        MPI_Send(&send,1,MPI_INT,1,0,MPI_COMM_WORLD);
        printf("共%d个进程，其中进程%d成功发送数据%d\n",world_size,world_rank,send);
    } 
    if(world_rank==1){
        MPI_Recv(&recv,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
       printf("共%d个进程，其中进程%d成功接收数据%d\n ", world_size , world_rank,recv);
    } 
    MPI_Finalize();
    return 0;
}
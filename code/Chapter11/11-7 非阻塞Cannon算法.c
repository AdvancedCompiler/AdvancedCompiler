#include<stdio.h>
#include<math.h>
#include<string.h>
#include"mympi.h"
#define DIMS 1000
int main(int argc, char *argv[]){
    int id,p,part,num,i,
    upRank,downRank,leftRank,rightRank;
    data_t *a, *b, *c, *a1, *b1;//a1,b1为非阻塞通信时a,b的缓冲
    data_t *A,*B,*C;//C即为最终结果
    int coord[2],x,y;//本进程坐标
    int position[2] = {0, 0};//确定（0，0）位置上的进程id
    double start_time, end_time;
    MPI_Comm MPI_COMM_CART;
    MPI_Request request1,request2,request3,request4;
    MPI_Status status,status1,status2;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    int periodic[2];
    int size[2];
    part = sqrt(p);
    //如果进程数不是平方数
    if(part*part!=p){
        printf("总进程数必须是一个平方数!\n");
        MPI_Finalize();
        return 0;
    }
    //如果行数不是进程数的整数倍
    if(DIMS%p!=0){
        printf("总进程数开方之后必须能整除矩阵总行数!\n");
        MPI_Finalize();
        return 0;
    }
    num = DIMS/part;
    //建立笛卡尔通信域
    size[0] = size[1] = part;//虚拟拓扑维数
    periodic[0] = periodic[1] = 1;//虚拟拓扑中进程下标是否循环
    MPI_Cart_create(MPI_COMM_WORLD, 2, size, periodic, 1, &MPI_COMM_CART);
    MPI_Comm_rank(MPI_COMM_CART,&id);
    MPI_Cart_coords(MPI_COMM_CART,id,2,coord);
    x = coord[0];
    y = coord[1];
    //为各个进程分配对应部分块矩阵的空间
    a = (data_t*)malloc(sizeof(data_t)*num*num);
    b = (data_t*)malloc(sizeof(data_t)*num*num);
    c = (data_t*)malloc(sizeof(data_t*)*num*num);
    a1 = (data_t*)malloc(sizeof(data_t)*num*num);
    b1 = (data_t*)malloc(sizeof(data_t)*num*num);
    if (id==0){
        A = (data_t*)malloc(sizeof(data_t)*DIMS*DIMS);
        B = (data_t*)malloc(sizeof(data_t)*DIMS*DIMS);
        C = (data_t*)malloc(sizeof(data_t)*DIMS*DIMS);
        Init_Matrix(A,DIMS*DIMS,2);
        Init_Matrix(B,DIMS*DIMS,2);
    }
    //分发矩阵
    start_time = MPI_Wtime();
    Init_Matrix(c,num*num,1);
    Matrix_cannon_scatter(DIMS,id,num,part,A,a1,MPI_COMM_CART);
    Matrix_cannon_scatter(DIMS,id,num,part,B,b1,MPI_COMM_CART);
    //进行第一次循环位移
    //获得当前矩阵块横坐标方向相聚x的左右方向的邻居进程号
    //分块a循环左移x位
    MPI_Cart_shift(MPI_COMM_CART, 1, x, &leftRank, &rightRank);
    MPI_Isend(a1,num*num,MPI_FLOAT,leftRank,i,MPI_COMM_CART,&request1);
    MPI_Irecv(a,num*num,MPI_FLOAT,rightRank,i,MPI_COMM_CART,&request2);
    //获得当前矩阵块纵坐标方向相聚y的上下邻居进程号
    //分块b循环上移y位
    MPI_Cart_shift(MPI_COMM_CART, 0, y, &upRank, &downRank);
    MPI_Isend(b1,num*num,MPI_FLOAT,upRank,i,MPI_COMM_CART,&request3);
    MPI_Irecv(b,num*num,MPI_FLOAT,downRank,i,MPI_COMM_CART,&request4);
    //获取本进程上下左右的进程号
    MPI_Cart_shift(MPI_COMM_CART, 0, 1, &upRank, &downRank);
    MPI_Cart_shift(MPI_COMM_CART, 1, 1, &leftRank, &rightRank);
    MPI_Wait(&request2,&status1);
    MPI_Wait(&request4,&status2);
    //进行余下part次循环位移，并计算分块c
    for (i = 0; i < part; ++i){
        //交替使用a、b及其缓冲a1、b1
        if(i%2==0){
            //非阻塞完成循环位移，将下一次计算需要的数据存于a1、b1
MPI_Isend(a,num*num,MPI_FLOAT,leftRank,i,MPI_COMM_CART,&request1);
MPI_Irecv(a1,num*num,MPI_FLOAT,rightRank,i,MPI_COMM_CART,&request2);
MPI_Isend(b,num*num,MPI_FLOAT,upRank,i,MPI_COMM_CART,&request3);
MPI_Irecv(b1,num*num,MPI_FLOAT,downRank,i,MPI_COMM_CART,&request4);            
//通信时计算
Mul_Matrix(a,b,c,num,num,num);
            //等待非阻塞通信完成后进入下一个循环
            MPI_Wait(&request2,&status1);
            MPI_Wait(&request4,&status2);
        }else{
            //非阻塞完成循环位移，将下一次计算需要的数据存于a、b
MPI_Isend(a1,num*num,MPI_FLOAT,leftRank,i,MPI_COMM_CART,&request1);
MPI_Irecv(a,num*num,MPI_FLOAT,rightRank,i,MPI_COMM_CART,&request2);
MPI_Isend(b1,num*num,MPI_FLOAT,upRank,i,MPI_COMM_CART,&request3);
MPI_Irecv(b,num*num,MPI_FLOAT,downRank,i,MPI_COMM_CART,&request4);
            //通信时计算
            Mul_Matrix(a1,b1,c,num,num,num);
            //等待非阻塞通信完成后进入下一个循环
            MPI_Wait(&request2,&status1);
            MPI_Wait(&request4,&status2);
        }
    }
    //收集矩阵C
    Matrix_cannon_gather(DIMS,id,num,part,c,C,MPI_COMM_CART);
    end_time = MPI_Wtime();
    printf("进程%d的运行时间为:%lf\n",id,(end_time-start_time));
    MPI_Comm_free(&MPI_COMM_CART);
	if (id==0){
        free(A);
        free(B);
        free(C);
    }
    free(a);
    free(b);
    free(c);
    free(a1);
    free(b1);
    MPI_Finalize();
    return 0;
}
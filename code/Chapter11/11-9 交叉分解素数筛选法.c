#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <mpi.h>

#define MAX_PRIME 100000001
int main(int argc, char **argv)
{
    // volume为每个进程的任务量
    // left为将任务划分后，剩余的不够平均分配的任务量
    int volume, left;
    double start, end;
    char *prime;
    int my_rank, world_size, index, i, new_index, last_index;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    //计算偏移量及任务量
    left = MAX_PRIME % world_size;
    if (my_rank < left)
    {
        volume = MAX_PRIME / world_size + 1;
    }
    else
    {
        volume = MAX_PRIME / world_size;
    }
    //当0进程的范围不能产生所有的未被标记数时，程序终止。
    if (my_rank == 0)
    {
        if (volume < sqrt(MAX_PRIME))
        {
            printf("进程数太多，素数上限太小\n");
            //终止MPI_COMM_WORLD下所有进程运行
            MPI_Abort(MPI_COMM_WORLD, 0);
        }
    }
    //分配存储空间
    prime = malloc(sizeof(char) * volume);
    memset(prime, 'y', volume);
    if (my_rank == 0)
    {
        prime[0] = 'n';
    }
    if (my_rank == 1)
    {
        prime[0] = 'n';
    }
    //初始index设为2，之后由root进程产生index并广播
    start = MPI_Wtime();
    index = 2;
    last_index=0;
    while (index * index <= MAX_PRIME)
    {
        //筛选index的倍数
        for (i = last_index; i < volume; i++)
        {
            if ((my_rank + i * world_size) % index == 0 && (my_rank + i * world_size) != index)
            {
                prime[i] = 'n';
            }
            // 标记2的倍数为非素数
            if(i != 2 && i % 2 == 0)
            {
                prime[i] = 'n'
            }
        }
        //寻找本进程的第一个未被标记数
        for (i = last_index; i < volume; i++)
        {
            if ((my_rank + i * world_size) > index && prime[i] == 'y')
            {
                index = i * world_size + my_rank;
                last_index=i;
                break;
            }
        }
        if (i == volume)
        {
            index = sqrt(MAX_PRIME) + 1;
        }
        // 每个进程产生的index的最小值
        MPI_Reduce(&index, &new_index, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
        if (my_rank == 0)
        {
            if (new_index == index)
            {
                index = new_index + 1;
            }
            else
            {
                index = new_index;
            }
        }
        MPI_Bcast(&index, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    end = MPI_Wtime();
    printf("进程%d的运行时间为:%lf\n", my_rank, (end - start));
    free(prime);
    MPI_Finalize();
    return 0;
}
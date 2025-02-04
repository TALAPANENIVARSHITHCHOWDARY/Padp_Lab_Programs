#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int process(int iter_num)
	{  	
	float x=0, y=0; 
	int N = 0; 
	for(int i=0; i < iter_num; i++)
		{
		x = (float)rand()/RAND_MAX;
		y = (float)rand()/RAND_MAX;
		if(x*x + y*y <= 1)
			N++;
		}
	return N;
	}
int main(int argc, char *argv[] )
    {
    if(argc != 2)
        {
        printf("Usage: %s <iterations>\n", argv[0]);
        return 1;
        }

    float t;
    int rank, numprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);


    int iter_num = atoi(argv[1]);
    srand(time(NULL)+rank);
    t=MPI_Wtime();
    int res=process(iter_num);
    t=MPI_Wtime()-t;
    printf("Time taken to compute for process %d: %.4f\n",rank,t);
    if(rank==0)
        {
        int temp =0;
        t=MPI_WgetTime();
        for(int i=1; i<numprocs; i++)
            {
            MPI_Recv(&temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            res += temp;
            }
            t=MPI_WgetTime()-t;
            printf("Time taken to gather messages: %.4f\n",t);
            float PI = 4*(float)res/(numprocs*iter_num);
            printf("Value of PI: %.4f\n",PI);
        }
    else
        MPI_Send(&res, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
    }
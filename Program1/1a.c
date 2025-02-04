#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
void process(int iterations,int tnum ){
    int x=0,y=0;
    int N=0;
    double t=omp_get_wtime();
    #pragma omp parallel for num_threads(tnum) private(x,y) reduction(+:N)
    for(int i=0;i<iterations;i++){
        x=rand()%100-50;
        y=rand()%100-50;
        if(x*x+y*y <= 2500)
            N++;
    }
    t=omp_get_wtime()-t;
    printf("%.4f\t",t);
}
int main(int argc,char *argv[]){
    if(argc!=3){
        printf("Usage: %s <iterations> <threads>\n",argv[0]);
        return 1;
    }
    int iterations=atoi(argv[1]);
    int tnum=atoi(argv[2]);
    process(iterations,tnum);
    return 0;
}
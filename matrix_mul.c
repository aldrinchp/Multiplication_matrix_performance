#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline double now_s(void){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);\
    return ts.tv_sec + ts.tv_nsec*1e-9;
}

static void run_case(int n, double *gt_s, double *ct_s){
    size_t N = (size_t)n*(size_t)n;
    double *A = (double*)malloc(N*sizeof(double));
    double *B = (double*)malloc(N*sizeof(double));
    double *C = (double*)calloc(N,sizeof(double));
    if(!A || !B || !C){ fprintf(stderr, "Memoria insuficiente\n"); exit(1); }

    srand(12345);
    double t0 = now_s();
    for(size_t i=0;i<N;i++) A[i] = (double)rand()/(double)RAND_MAX;
    double t1 = now_s();
    *gt_s = (t1 - t0);

    for(size_t i=0;i<N;i++) B[i] = (double)rand()/(double)RAND_MAX;

    t0 = now_s();
    for(int i=0;i<n;i++){
        for(int k=0;k<n;k++){
            double aik = A[(size_t)i*n + k];
            for(int j=0;j<n;j++){
                C[(size_t)i*n + j] += aik * B[(size_t)k*n + j];
            }
        }
    }
    t1 = now_s();
    *ct_s = (t1 - t0);

    free(A); free(B); free(C);
}

int main(int argc, char** argv){
    if(argc < 2){
        fprintf(stderr,"Uso: %s n1 [n2 n3 ...]\n", argv[0]);
        return 1;
    }
    printf("| n | GT(s) | CT(s) |\n");
    printf("|---:|------:|------:|\n");
    for(int a=1;a<argc;a++){
        int n = atoi(argv[a]);
        double gt, ct;
        run_case(n, &gt, &ct);
        printf("| %d | %.6f | %.6f |\n", n, gt, ct);
    }
    return 0;
}
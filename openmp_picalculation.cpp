#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
    #include <omp.h>
#endif

using namespace std;

double Local_Pi();

int main(int argc, char* argv[]){
    double global_result = 0.0;
    int thread_count;
    printf("el valor de _OPENMP: %d\n", _OPENMP);
    thread_count = strtol(argv[1], NULL, 10);
    #pragma omp parallel num_threads(thread_count)
    global_result = Local_Pi();

    printf("Pi = %f\n", global_result);
    return 0;
}
/* main */

double Local_Pi(){
    double factor;
    double sum = 0.0;
    double pi_approx = 0.0;
    int k;
    int thread_count = omp_get_num_threads();
    # pragma omp parallel for num_threads(thread_count) \
        reduction(+:sum) private(factor)
    for (k = 0; k < thread_count; k++) {
        if (k%2 == 0)
            factor = 1.0;
        else
            factor = -1.0;
        sum += factor/(2*k+1);
    }
    pi_approx = 4.0*sum;

    return pi_approx;
}

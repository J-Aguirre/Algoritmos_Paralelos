#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]){
    /* 6.
    int omp_get_thread_num();
    # pragma omp parallel for
    for(int i=0; i<10; i++){
        printf("Thread: %d. Iteration: %d\n", omp_get_thread_num(), i);
    }
    */
    int acum = 0;
    # pragma omp parallel for
    for(int i=1; i<5; i++){
        acum += i;
        printf("Valor: %d, Suma: %d\n", i, acum);
    }
    printf("%d\n", acum);
    return 0;


}
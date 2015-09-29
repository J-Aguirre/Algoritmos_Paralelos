#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <vector>

using namespace std;
 
int r=10, c=10, num_threads=5;
int parte=r/num_threads;
vector< vector<int> > matriz;
vector<int> vec, res;

void create_mat_vec(vector< vector<int> > &matriz, vector<int> &vec){
    srand(time(NULL));
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            vec.push_back(rand()%20);
        }
        matriz.push_back(vec);
        vec.clear();
    }
    for(int i=0; i<r; i++){
        vec.push_back(rand()%20);
    }
}

void *matrix_mult( void *ptr );

main(){
    create_mat_vec(matriz, vec);
    pthread_t thread1, thread2, thread3, thread4, thread5;
    /* Create independent threads each of which will execute function */
    for(int i=0; i<r; i++){
        pthread_t thread;
        pthread_create(&thread, NULL, matrix_mult, (void*) parte);
    }

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */

    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);

exit(EXIT_SUCCESS);
}
 
void *matrix_mult( void *ptr )
{
    int parte = (int) ptr;
    int val = 0;
    for(int i=0; i<parte; i++){
        for(int j=0; j<c; j++){
            val += matriz[i][j]*vec[j];
        }
        res.push_back(val);
        val = 0;
    }
}
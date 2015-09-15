#include <mpi.h>
#include <stdio.h>

int rank, size;
int data = 1;
int vec_data[5] = {1,2,3,4,5}; int vec_rec[5];

void first_exercise(){
  MPI_Recv(&data, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  if(rank < size-1){
    MPI_Send(&data, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
  }
  printf("Recibido %d, soy el proceso %d\n", data, rank);

}

void second_exercise(){
    MPI_Send(&vec_data, 5, MPI_INT, rank, 0, MPI_COMM_WORLD);

    MPI_Recv(&vec_rec, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Recibido %d, soy el proceso %d\n", vec_data[0], rank);
}

void third_exercise(){

}

int main (int argc, char* argv[]){
  MPI_Init (&argc, &argv);      /* starts MPI */

  MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */

  second_exercise();

  MPI_Finalize();
  return 0;
}
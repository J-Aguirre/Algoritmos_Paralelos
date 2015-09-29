#include <mpi.h>
#include <stdio.h>

int main (int argc, char* argv[]){
  MPI_Init (&argc, &argv);      /* starts MPI */

  MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */

  if(rank%2 == 0){
    MPI_Send(msg, /**/, MPI_INT, (rank+1) % size, 0, MPI_COMM_WORLD);
    MPI_Recv(new_msg, /**/, MPI_INT, (rank+size−1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }else{
    MPI_Recv(new_msg, /**/, MPI_INT, (rank+size−1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE).
    MPI_Send(msg, /**/, MPI_INT, (rank+1) % size, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}
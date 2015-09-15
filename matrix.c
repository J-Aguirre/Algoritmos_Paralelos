#include <mpi.h>
#include <stdio.h>

int rank, size;

int main (int argc, char* argv[]){
  MPI_Init (&argc, &argv);      /* starts MPI */

  MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */

	first_exercise();
	//second_exercise();

  MPI_Finalize();
  return 0;
}

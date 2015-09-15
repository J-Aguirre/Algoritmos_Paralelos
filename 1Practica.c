#include <mpi.h>
#include <stdio.h>

int rank, size;
int data_send = 1, data_rec;
int vec_data[5] = {1,2,3,4,5}; int vec_rec[5];

void first_exercise(){
	if(rank == 0){
	  MPI_Recv(&data_rec, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("proceso recivido de %d y enviado de %d", size-1, rank+1);
		MPI_Send(&data_send, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
	}
	else{
		if(rank < size-1){
			MPI_Send(&data_send, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
		}
		else{
			MPI_Recv(&data_rec, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}

  printf("Recibido %d, soy el proceso %d\n", data_send, rank);

}

void second_exercise(){
	if(rank == 0){
		int i=1;
		while(i<size){
			MPI_Send(&vec_data, 5, MPI_INT, i, 0, MPI_COMM_WORLD);
			i+=1;
		}
	}
	else{
	  MPI_Recv(&vec_rec, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  	printf("Recibido %d,%d,%d,%d,%d, soy el proceso %d\n", vec_data[0],vec_data[1],vec_data[2],vec_data[3],vec_data[4], rank);
	}
}

void third_exercise(){
//	string text = "";
	//for(int i=0; i<tex.size)

}

int main (int argc, char* argv[]){
  MPI_Init (&argc, &argv);      /* starts MPI */

  MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */

	first_exercise();
	//second_exercise();

  MPI_Finalize();
  return 0;
}

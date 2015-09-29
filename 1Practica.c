#include <mpi.h>
#include <stdio.h>
#include <string.h>

int rank, size;
int data_send = 1, data_rec;
int vec_data[5] = {1,2,3,4,5}; int vec_rec[5];

void first_exercise(){
    if(rank == size-1){
        MPI_Send(&data_send, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    }
    else{
        MPI_Send(&data_send, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
    }
    if(rank == 0){
        MPI_Recv(&data_rec, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else{
        MPI_Recv(&data_rec, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
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
    FILE* fp;
    char str[] = "El Perú (en quechua y en aimara: Piruw), oficialmente la República del Perú, es un país soberano del oeste de América del Sur. El océano Pacífico bordea su costa y limita con Ecuador y Colombia al norte, Brasil al este, y Bolivia y Chile al sureste. Su territorio se compone de diversos paisajes: los valles, las mesetas y las altas cumbres de los Andes se despliegan al oeste hacia la costa desértica y a el este hacia la Amazonia. Es uno de los países de mayor diversidad biológica del mundo y de mayores recursos minerales.",str_rec[strlen(str)], str_buffer[strlen(str)/(size-2)];
    // fp = fopen("text.txt", "r");


    // while(fgets(str, 5000, fp)!=NULL){
    //     puts(str);
    // }
    // fclose(fp);
    int fraction = strlen(str)/(size-2), number = strlen(str);
    if(rank == 0){
        int i=1, len_f=0, len_s = fraction;
        while(i<size){
            int j=len_f, k=0;
            while(j<len_s){
                str_buffer[k] = str[j];
                j+=1; k+=1;
            }
            printf("tamaños: %d, %d de %d procesos: %d, %d\n", len_f, len_s, number, size, fraction);
            len_f = len_s; len_s = len_f+number;
            MPI_Send(&str_buffer, fraction, MPI_CHAR, i,0, MPI_COMM_WORLD);
            i+=1;
        }
    }
    else{
        MPI_Recv(&str_rec, strlen(str), MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

}

int main (int argc, char* argv[]){
  MPI_Init (&argc, &argv);      /* starts MPI */

  MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */

	// first_exercise();
	// second_exercise();
    third_exercise();

  MPI_Finalize();
  return 0;
}

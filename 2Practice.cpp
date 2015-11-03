#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int rank, size, part, section;
int r=15, c=15, i=0, j=0, final_value=0;


int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    int matrix[r][c];
    int matrix_rec[r][c]; //= new int*[r/(size-1)];
    /*for(i=0; i<r; i++)
        matrix[i] = new int[c];*/
    int vector[c];
    int vector_rec[c]; //final = new int[c];


    part = r/(size-1);
    section = part;
    if(rank == 0){

    	for(i=0; i<r; i++) {
        	for(j=0; j<c; j++){
            	srand(time(NULL));
		    	matrix[i][j] = rand()%100;
            	vector[j] = rand()%100;
		    }
		}

        for(i=1; i<size; i++){
            MPI_Send(&matrix[section], part*c, MPI_INT, i, 10, MPI_COMM_WORLD);
<<<<<<< HEAD
            MPI_Send(&vector, c, MPI_INT, i, 10, MPI_COMM_WORLD);
            for(int l=0; l<section; l++){
                for(int m=0; m<c; m++)
                    printf("%d ",matrix[l][m]);
                printf("\n");
            }
=======
            MPI_Send(&vector, c, MPI_INT, i, 11, MPI_COMM_WORLD);
>>>>>>> 3aca5c429f968f90d66eb5bea47bde7a1f5b3ab5
            section += part;
        }
    }
    else{
        MPI_Recv(&matrix_rec, part*c, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&vector_rec, c, MPI_INT, 0, 11, MPI_COMM_WORLD, &status);
        for(i=0; i<part; i++){
            for(j=0; j<c; j++){
<<<<<<< HEAD
                final_value += matrix_rec[i][j]*vector_rec[j];
=======
                final_value += matrix_rec[i][j] * vector_rec[j];
>>>>>>> 3aca5c429f968f90d66eb5bea47bde7a1f5b3ab5
                printf("%d ", final_value);
            }
        }

    }

    MPI_Finalize();
    return 0;
}

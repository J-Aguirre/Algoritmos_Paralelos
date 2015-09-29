#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int rank, size, part, section;
int r=100, c=100, i=0, j=0, final_value=0;


int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    int** matrix = new int*[r], matrix_rec; //= new int*[r/(size-1)];
    for(i=0; i<r; i++)
        matrix[i] = new int[c];
    int* vector = new int[c], vector_rec; //final = new int[c];

    for(i=0; i<r; i++)
        for(j=0; j<c; j++){
            srand(time(NULL));
            matrix[i][j] = rand()%100;
            vector[j] = rand()%100;
        }


    part = r/(size-1);
    section = part;
    if(rank == 0){
        for(i=1; i<size; i++){
            MPI_Send(&matrix[section], part*c, MPI_INT, i, 10, MPI_COMM_WORLD);
            MPI_Send(&vector, c, MPI_INT, i, 10, MPI_COMM_WORLD);
            section += part;
        }
    }
    else{
        MPI_Recv(&matrix_rec, part*c, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&vector_rec, c, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        for(i=0; i<part; i++){
            for(j=0; j<c; j++){
                final_value += matrix_rec[part][j]*vector_rec[j];
                printf("%d ", final_value);
            }
        }

    }

    MPI_Finalize();
    return 0;
}
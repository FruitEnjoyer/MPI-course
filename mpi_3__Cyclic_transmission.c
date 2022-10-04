#include <stdio.h>
#include <stdint.h>
#include "mpi.h"

#define MES_SIZE    14

int main(int argc, char **argv)
{
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	char msg[MES_SIZE] = {'H','e','l','l','o',',',' ','w','o','r','l','d','!','\0'};
	char buffer[MES_SIZE];
	
	// transmission
	MPI_Send(msg, MES_SIZE, MPI_CHAR, (rank+1)%size, 0, MPI_COMM_WORLD);

	// reception
	MPI_Recv(buffer, MES_SIZE, MPI_CHAR, (rank-1+size)%size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	
	printf("from %i to %i received %i bytes: ", (rank-1+size)%size, rank, MES_SIZE);
	for(int i = 0; i < MES_SIZE; ++i){
		printf("%c", buffer[i]);
	}
	printf("\n");

	MPI_Finalize();
  
	return 0;
}

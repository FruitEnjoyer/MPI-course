#include <stdio.h>
#include <stdint.h>
#include "mpi.h"

#define MES_SIZE    14
#define TRANSMITTER 0
#define RECEIVER    1

int main(int argc, char **argv)
{
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	
	if(rank == TRANSMITTER){ // transmitter
		char msg[MES_SIZE] = {'H','e','l','l','o',',',' ','w','o','r','l','d','!','\0'};
		MPI_Send(msg, MES_SIZE, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
	}
	
	if(rank == RECEIVER){ // receiver
		char buffer[MES_SIZE];
		MPI_Recv(buffer, MES_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("from %i to %i received %i bytes: ", TRANSMITTER, RECEIVER, MES_SIZE);
		for(int i = 0; i < MES_SIZE; ++i){
			printf("%i ", buffer[i]);
		}
		printf("\n");
	}

	MPI_Finalize();
  
	return 0;
}

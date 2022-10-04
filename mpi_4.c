#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//#include <string>
//#include <cstring>
#include <mpi.h>

#define MES_SIZE    1048576
#define TRANSMITTER 0
#define RECEIVER    1



int main(int argc, char **argv)
{
	int size, rank;
	double Tstart, Tend;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// we need to create data buffer for transmission and reception,
	// so we allocate MES_SIZE bytes in heap for both kernels:
	uint8_t *buffer = (uint8_t*)malloc(sizeof(uint8_t) * MES_SIZE);
	
	//***OPTIONAL***
	//then, in transmitter kernel I fill buffer with integer numbers [0-255]:
	if(rank == TRANSMITTER){
		for(uint32_t i = 0; i < MES_SIZE; ++i){
			buffer[i] = i % 255;
		}
	}
	
	// transmission
	if(rank == TRANSMITTER){
		Tstart = MPI_Wtime();
		MPI_Send(buffer, MES_SIZE+1, MPI_UINT8_T, RECEIVER, 0, MPI_COMM_WORLD);
		
		MPI_Recv(buffer, MES_SIZE+1, MPI_UINT8_T, RECEIVER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		Tend = MPI_Wtime();
	}
	
	
	// reception
	if(rank == RECEIVER){
		MPI_Recv(buffer, MES_SIZE+1, MPI_UINT8_T, TRANSMITTER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
		MPI_Send(buffer, MES_SIZE+1, MPI_UINT8_T, TRANSMITTER, 0, MPI_COMM_WORLD);
	}
	
	// transmitter saves time data to the .txt file
	
	/*
	if(rank == TRANSMITTER){
		FILE *fp = fopen("/home/ruslan/Desktop/file1.txt", "a+");	
		for(uint32_t i = 0; i < MES_SIZE; ++i){
			fprintf("%d ",buffer[i]);
		}
		fprintf("\n");
		fclose(fp);
	}
	*/
	
	if(rank == TRANSMITTER){
		printf("Transmitted %i bytes in %f us", MES_SIZE, 1000000*(Tend-Tstart)/2);
	}
	
	// free allocated memory for each kernel
	free(buffer);
	
	MPI_Finalize();
  
	return 0;
}








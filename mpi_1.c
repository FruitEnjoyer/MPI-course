#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	int process_size, process_id;
	printf("Before MPI_INIT\n");
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

	printf("process: %i   size: %i\n", process_id, process_size);

	MPI_Finalize();
	printf("After MPI_FINALIZE\n");
  
	return 0;
}

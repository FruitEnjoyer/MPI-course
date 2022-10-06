#!/bin/bash

echo "compiling mpi_4.c ..."
mpic++ -o mpi_4 mpi_4.c 
#gcc -o kostyl kostyl.c

echo "mpi_4.c compiled succesfully"

for i in {1..750}
do 
	mpiexec -n 2 ./mpi_4
done



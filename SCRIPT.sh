#!/bin/bash

############################################################
#                                                          #
#    Bourne shell script for submitting a parallel MPI     #
#    job to the PBS queue using the qsub command.          #
#                                                          #
############################################################

#     Remarks: A line beginning with # is a comment.
#	       A line beginning with #PBS is a PBS directive.
#              PBS directives must come first; any directives
#                 after the first executable statement are ignored.
#
   
##########################
#                        #
#   The PBS directives   #
#                        #
##########################

#          Set the name of the job (up to 15 characters, 
#          no blank spaces, start with alphanumeric character)

#PBS -N JobName

#          Specify the number of nodes requested and the
#          number of processors per node. 

#PBS -l nodes=3:ppn=1

#          The directive below directs that the standard output and
#          error streams are to be merged, intermixed, as standard
#          output. 

#PBS -j oe

#          Specify the maximum cpu time. 
#          Format:   hhhh:mm:ss   hours:minutes:seconds
#          Be sure to specify a reasonable value here.
#          If the job does not finish by the time reached,
#          the job is terminated.

#PBS -l     cput=6:00:00


##########################################
#                                        #
#   Output some useful job information.  #
#                                        #
##########################################

NCPU=`wc -l < $PBS_NODEFILE`
echo ------------------------------------------------------
echo ' This job is allocated on '${NCPU}' cpu(s)'
echo 'Job is running on node(s): '
cat $PBS_NODEFILE
echo ------------------------------------------------------
echo PBS: qsub is running on $PBS_O_HOST
echo PBS: originating queue is $PBS_O_QUEUE
echo PBS: executing queue is $PBS_QUEUE
echo PBS: working directory is $PBS_O_WORKDIR
echo PBS: execution mode is $PBS_ENVIRONMENT
echo PBS: job identifier is $PBS_JOBID
echo PBS: job name is $PBS_JOBNAME
echo PBS: node file is $PBS_NODEFILE
echo PBS: current home directory is $PBS_O_HOME
echo PBS: PATH = $PBS_O_PATH
echo ------------------------------------------------------

##############################################################
#                                                            #
#   The prologue script automatically makes a directory      #
#   on the local disks for you.  The name of this directory  #
#   depends on the job id, but you need only refer to it     #
#   using ${WORKDIR}.                                        #
#                                                            #
##############################################################

SERVER=$PBS_O_HOST
WORKDIR=/data/$PBS_JOBID
LAUNCH="/opt/mpi/mpich-p4/bin/mpirun -np $NCPU -machinefile $PBS_NODEFILE"

echo server is $SERVER
echo workdir is $WORKDIR
echo ------------------------------------------------------
echo 'Job is running on node(s): '
cat $PBS_NODEFILE
echo ------------------------------------------------------
echo ' '
echo ' '


############################################################
#                                                          #
#    Execute the run.  Do not run in the background.       #
#                                                          #
############################################################


 cd ${WORKDIR}
 ${LAUNCH} program_executable input_file


###############################################################
#                                                             #
#   The epilogue script automatically deletes the directory   #
#   created on the local disk (including all files contained  #
#   therein.                                                  #
#                                                             #
###############################################################

exit

	



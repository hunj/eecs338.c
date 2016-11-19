#!/bin/bash
#SBATCH --output=q2.output
#SBATCH --nodes=1
#SBATCH --cpus-per-task=5

nproc=$(expr $SLURM_JOB_CPUS_PER_NODE \* $SLURM_NNODES)
echo $nproc cores available

cp q2.c $PFSDIR/.
cd $PFSDIR
module load gcc
gcc q2.c -o q2 -fopenmp
./q2
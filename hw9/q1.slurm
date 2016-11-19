#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=5
#SBATCH --output=q1.output
nproc=$(expr $SLURM_JOB_CPUS_PER_NODE \* $SLURM_NNODES)
echo $nproc cores available.

cp q1.c $PFSDIR/.
cd $PFSDIR
module load gcc
gcc q1.c -o q1
./q1
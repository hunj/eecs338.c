#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=5
#SBATCH --output=hw91.txt 
nproc=$(expr $SLURM_JOB_CPUS_PER_NODE \* $SLURM_NNODES)
echo $nproc cores available
cp hw91.c $PFSDIR/.
cd $PFSDIR
gcc hw91.c -o hw91
./hw91

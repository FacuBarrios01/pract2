#!/bin/bash
#SBATCH --nodes=1
#SBATCH --time=5:00
#SBATCH --partition=cpa
OMP_NUM_THREADS=16 

./restore1 -i peque.ppm -o ref1k.ppm -b 8
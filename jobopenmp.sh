#!/bin/bash
#SBATCH --nodes=1
#SBATCH --time=5:00
#SBATCH --partition=cpa

OMP_NUM_THREADS=2 OMP_SCHEDULE=static,1 ./restore2 -i peque.ppm -o ref1k.ppm -b 8

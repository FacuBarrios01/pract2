#!/bin/bash
#SBATCH --nodes=1
#SBATCH --time=5:00
#SBATCH --partition=cpa
echo "----------------------------------------------"
echo "EJECUCION RESTORE1 "
echo " "
echo "SCHEDULE= static , chunk por defecto"
OMP_NUM_THREADS=2 OMP_SCHEDULE=static ./restore1 -i grande.ppm -o ref1g.ppm -b 2
echo " "
echo "SCHEDULE= static , chunk por defecto"
OMP_NUM_THREADS=4 OMP_SCHEDULE=static ./restore1 -i grande.ppm -o ref1g.ppm -b 2
echo " "
echo "SCHEDULE= static , chunk por defecto"
OMP_NUM_THREADS=8 OMP_SCHEDULE=static ./restore1 -i grande.ppm -o ref1g.ppm -b 2
echo " "
echo "SCHEDULE= static , chunk por defecto"
OMP_NUM_THREADS=16 OMP_SCHEDULE=static ./restore1 -i grande.ppm -o ref1g.ppm -b 2
echo " "
echo "SCHEDULE= static , chunk por defecto"
OMP_NUM_THREADS=32 OMP_SCHEDULE=static ./restore1 -i grande.ppm -o ref1g.ppm -b 2
echo " "
echo "----------------------------------------------"
echo "EJECUCION RESTORE2 "
echo " "
echo "SCHEDULE= static , chunk por defecto"
OMP_NUM_THREADS=2 OMP_SCHEDULE=static ./restore2 -i grande.ppm -o ref1g2.ppm -b 2
echo " "
echo "SCHEDULE= static , chunk por defecto"
OMP_NUM_THREADS=4 OMP_SCHEDULE=static ./restore2 -i grande.ppm -o ref1g2.ppm -b 2
echo " "
echo "SCHEDULE= static , chunk por defecto"
OMP_NUM_THREADS=8 OMP_SCHEDULE=static ./restore2 -i grande.ppm -o ref1g2.ppm -b 2
echo " "
echo "SCHEDULE= static , chunk por defecto"
OMP_NUM_THREADS=16 OMP_SCHEDULE=static ./restore2 -i grande.ppm -o ref1g2.ppm -b 2
echo " "
echo "SCHEDULE= static , chunk por defecto"
OMP_NUM_THREADS=32 OMP_SCHEDULE=static ./restore2 -i grande.ppm -o ref1g2.ppm -b 2
echo " "
echo "SCHEDULE= static , chunk por defecto"
OMP_NUM_THREADS=64 OMP_SCHEDULE=static ./restore2 -i grande.ppm -o ref1g2.ppm -b 2
echo "SCHEDULE= static , chunk por defecto"
OMP_NUM_THREADS=128 OMP_SCHEDULE=static ./restore2 -i grande.ppm -o ref1g2.ppm -b 2
echo "----------------------------------------------"
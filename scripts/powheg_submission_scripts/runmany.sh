#!/bin/bash

#$1 number of jobs

njobs=$1

#dir="Out_"`date +"%F_%T"`
#mkdir $dir

for i in `seq 150 $njobs`; do

  jobname=powheg_Job_${i}
  seed=1000${i}

  export LS_JOBNAME=${jobname}
  export LS_SEED=${seed}
  echo $LS_SEED
  
#  bsub -q 1nd -o /dev/null -J powheg < powheg.sub
  bsub -q 1nd -J powheg < powheg.sub

done  


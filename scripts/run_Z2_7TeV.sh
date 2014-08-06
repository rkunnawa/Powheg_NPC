#!/bin/bash 
#o
#e
set echo

export JOBNAME=${LS_JOBNAME}
echo $JOBNAME

cd /afs/cern.ch/work/s/sdooling/NP_CORRECTION/CMSSW_5_0_0/src
eval `scram runtime -sh`

export MAXEVENTS=${LS_MAXEVENTS}
export RIVETXS=${LS_RIVETXS}
export SEED=${LS_SEED}
export JOBINDEX=${LS_JOBINDEX}
#export LHESET=${LS_LHESET}
export FILESPERJOB=${LS_FILESPERJOB}
export LHESET=${LS_DATASET}
export OUTPUT=${LS_OUTPUT}
export OUTPUTDIR=${LS_OUTPUTDIR}

cmsRun TuneZ2_7TeV.py
mv ${OUTPUT} ${OUTPUTDIR}


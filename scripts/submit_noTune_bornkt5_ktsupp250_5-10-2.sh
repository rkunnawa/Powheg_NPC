#!/bin/bash 
set echo

cd /afs/cern.ch/work/s/sdooling/NP_CORRECTION/CMSSW_5_0_0/src

for i in `seq 0 14`; do

	jobname=powheg_with_no_Tune_$i

	genseed=1000$i
	maxevents=-1
	rivetxs=30270000000
	filesperjob=10
	#filename=rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_$i.lhe
	dataset=CT10_bornkt5_bornsupp250_5-10-2.lhefiles	
	outputname=NOTUNEbornkt5ktsupp250_$i.aida
	outputdir=out_aida_CT10_bornkt5_bornsupp250_5-10-2_try

	export LS_JOBNAME=${jobname}
	echo ${jobname}
	export LS_JOBINDEX=$i
	echo jobindex: $i
	
	export LS_FILESPERJOB=${filesperjob}
	export LS_MAXEVENTS=${maxevents}
	export LS_RIVETXS=${rivetxs}
	export LS_SEED=${genseed}
	#export LS_LHESET=${filename}
	export LS_DATASET=${dataset}
	export LS_OUTPUT=${outputname}
	export LS_OUTPUTDIR=${outputdir}

	bsub -q 1nd run_noTune.sh
done


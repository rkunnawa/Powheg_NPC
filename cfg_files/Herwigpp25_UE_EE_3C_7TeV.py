# Auto generated configuration file
# using: 
# Revision: 1.341 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/MinBias_HerwigppUE_900GeV_pythia6_cff.py -s GEN --datatier=GEN-SIM-RAW --conditions auto:mc --eventcontent RAWSIM --no_exec -n 100000 --python_filename=HerwigppUE_900GeV_cfg.py --customise=Configuration/GenProduction/rivet_customize_herwigppUE_900GeV.py
import FWCore.ParameterSet.Config as cms
import os
import random
import time

process = cms.Process('GEN')

process.source = cms.Source("LHESource",
                   # fileNames = cms.untracked.vstring(os.getenv('LHESET')),
                    fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_0.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_1.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_2.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_4.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_5.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_6.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_7.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_8.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_9.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_10.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_11.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_12.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_13.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_14.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_15.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_16.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_17.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_18.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_19.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_20.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_21.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_22.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_23.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_24.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_25.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_26.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_27.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_28.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_29.lhe','rfio:/castor/cern.ch/user/s/sdooling/lhefiles_CT10_bornkt5_bornsupp250_5-10-2/powheg_Job_30.lhe'),
                    skipBadFiles = cms.untracked.bool(True)
                    )


# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic7TeV2011Collision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.RandomNumberGeneratorService.generator.initialSeed = int(os.getenv('SEED'))

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(int(os.getenv('MAXEVENTS')))
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('PYTHIA6-MinBias HerwigppUE at 7TeV'),
    name = cms.untracked.string('$Source: /local/reps/CMSSW/UserCode/sdooling/NP_CORRECTIONS/cfg_files/Herwigpp25_UE_EE_3C_7TeV.py,v $')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('MinBias_HerwigppUE_900GeV_pythia6_cff_py_GEN.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-RAW')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'MC_50_V8::All'

process.generator = cms.EDFilter("LHEProducer",
	eventsToPrint = cms.untracked.uint32(1),
    	hadronisation = cms.PSet(
		
		run = cms.string('LHC'),
		repository = cms.string('HerwigDefaults.rpo'),
		dataLocation = cms.string('${HERWIGPATH}'),
		
		configFiles = cms.vstring(),
		generatorModule = cms.string('/Herwig/Generators/LHCGenerator'),
		eventHandlers = cms.string('/Herwig/EventHandlers'),
	# from Panos
				 pdfCTEQ6L1 = cms.vstring(
		# the pdf set for the hard process
		'cd /Herwig/Partons',
		'create ThePEG::LHAPDF CTEQ6L1 ThePEGLHAPDF.so',
		'set CTEQ6L1:PDFName cteq6ll.LHpdf',
		'set CTEQ6L1:RemnantHandler HadronRemnants',
		'cp CTEQ6L1 cmsPDFSet',
		'cd /',
		'mkdir /LHAPDF',
		'cd /LHAPDF',
		'create ThePEG::LHAPDF CTEQ6L1',
		'set CTEQ6L1:PDFName cteq6ll.LHpdf',
		'set CTEQ6L1:RemnantHandler /Herwig/Partons/HadronRemnants',
		'cp CTEQ6L1 /cmsPDFSet',
		'cd /'
		),
	
	
	#from cvs file test...
        			lheDefaults = cms.vstring('cd /Herwig/Cuts', 
          	  'create ThePEG::Cuts NoCuts', 
		  # create a LesHouches reader object 
          	  'cd /Herwig/EventHandlers', 
          	  'create ThePEG::LesHouchesInterface LHEReader', 
          	  'set LHEReader:Cuts /Herwig/Cuts/NoCuts',
		  # create a LesHouchesEventHandler object 
          	  'create ThePEG::LesHouchesEventHandler LHEHandler', 
		  'set LHEHandler:WeightOption 1',
          	  'set LHEHandler:PartonExtractor /Herwig/Partons/QCDExtractor', 
          	  'set LHEHandler:CascadeHandler /Herwig/Shower/ShowerHandler', 
          	  'set LHEHandler:HadronizationHandler /Herwig/Hadronization/ClusterHadHandler', 
          	  'set LHEHandler:DecayHandler /Herwig/Decays/DecayHandler', 
          	  'insert LHEHandler:LesHouchesReaders 0 LHEReader', 
          	  'cd /Herwig/Generators', 
          	  'set LHCGenerator:EventHandler /Herwig/EventHandlers/LHEHandler', 
		  # set up the POWHEG shower
          	  'cd /Herwig/Shower', 
		  'set Evolver:HardEmissionMode POWHEG',  #Whether to use ME corrections or POWHEG for the hardest emission
		  'set Evolver:HardOnly No',		# Only generate the emission supplied by the hardest emission generator, for testing only.0(No) Generate full shower 1(Yes) Only the hardest emission 
          	  'set Evolver:HardVetoScaleSource Read', 
          	  'set Evolver:MECorrMode No', 	#Choice of the ME Correction Mode: 0(No) MECorrections off 
										#1(Yes) hard+soft on 
										#2(Hard) only hard on 
										#3(Soft) only soft on 
          	  'cd /'),
	#from cvs file test...
		  	      lheDefaultPDFs = cms.vstring('cd /Herwig/EventHandlers', 
	          'set LHEReader:PDFA /cmsPDFSet', 
         	  'set LHEReader:PDFB /cmsPDFSet', 
             	  'cd /'),
	#from Panos
			basicSetup = cms.vstring(
		'cd /Herwig/Generators',
		'create ThePEG::RandomEngineGlue /Herwig/RandomGlue',
		'set LHCGenerator:RandomNumberGenerator /Herwig/RandomGlue',
		'set LHCGenerator:NumberOfEvents 10000000',
		'set LHCGenerator:DebugLevel 1',
		'set LHCGenerator:PrintEvent 0',
		'set LHCGenerator:MaxErrors 10000',
		'cd /Herwig/Particles',
		'set p+:PDF /Herwig/Partons/cmsPDFSet',
		'set pbar-:PDF /Herwig/Partons/cmsPDFSet',
		'set K0:Width 1e300*GeV',
		'set Kbar0:Width 1e300*GeV',
		'cd /',
		),
	#from Panos	
			herwigppUE_EE_3C_Base = cms.vstring(
		'+pdfCTEQ6L1',
		'cd /Herwig',
		'create Herwig::O2AlphaS O2AlphaS',
		'set Model:QCD/RunningAlphaS O2AlphaS',
		# Energy-independent MPI parameters
		#   Colour reconnection settings
		'set /Herwig/Hadronization/ColourReconnector:ColourReconnection Yes',
		'set /Herwig/Hadronization/ColourReconnector:ReconnectionProbability 0.61',
		#   Colour Disrupt settings
		'set /Herwig/Partons/RemnantDecayer:colourDisrupt 0.75',
		#   inverse hadron radius
		'set /Herwig/UnderlyingEvent/MPIHandler:InvRadius 1.35',
		#   MPI model settings
		'set /Herwig/UnderlyingEvent/MPIHandler:IdenticalToUE 0',
		'set /Herwig/UnderlyingEvent/MPIHandler:softInt Yes',
		'set /Herwig/UnderlyingEvent/MPIHandler:twoComp Yes',
		'set /Herwig/UnderlyingEvent/MPIHandler:DLmode 2',
		'cd /',
		),
	#from Panos	
				 herwigppUE_EE_3C_7000GeV = cms.vstring(
		'+herwigppUE_EE_3C_Base',
		'set /Herwig/Generators/LHCGenerator:EventHandler:LuminosityFunction:Energy 7000.0',
		'set /Herwig/UnderlyingEvent/KtCut:MinKT 2.752',
		'set /Herwig/UnderlyingEvent/UECuts:MHatMin 5.504',
		'set /Herwig/Shower/Evolver:IntrinsicPtGaussian 2.34*GeV',
		),
				MPICut = cms.vstring(
		'cd /Herwig',
		'set /Herwig/UnderlyingEvent/MPIHandler:PtOfQCDProc 10.0',
		),

       		parameterSets = cms.vstring(
			'pdfCTEQ6L1', 	
			'basicSetup', 
			'MPICut',
#
			'herwigppUE_EE_3C_Base',	
			'herwigppUE_EE_3C_7000GeV', 
#
			'lheDefaults',
				#without this: error no subprocess is defined
				#with this: MPIHandler: You need to specify the pt cutoff used to in the LesHouches file for QCD2to2?->Segmentation violation
			'lheDefaultPDFs'	#nothing changes including this
		),
        	generator = cms.string('ThePEG')

	)

)
process.ProductionFilterSequence = cms.Sequence(process.generator)
# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.endjob_step,process.RAWSIMoutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from Configuration.GenProduction.rivet_customize_Herwigpp25_UE_EE_3C_QCD_7TeV
#from Configuration.GenProduction.rivet_customize_Herwigpp25_UE_EE_3C_QCD_7TeV import customise 

def customise(process):
        process.load('GeneratorInterface.RivetInterface.rivetAnalyzer_cfi')
        process.rivetAnalyzer.AnalysisNames = cms.vstring('CMS_2011_S9086218','CMS_QCD_11_004') 	
	#process.rivetAnalyzer.CrossSection = cms.double(int(os.getenv('RIVETXS')))		
	#process.rivetAnalyzer.OutputFile = cms.string(os.getenv('OUTPUT'))
        process.generation_step+=process.rivetAnalyzer
        process.schedule.remove(process.RAWSIMoutput_step)
        return(process)

#call to customisation function customise imported from Configuration.GenProduction.rivet_customize_Herwigpp25_UE_EE_3C_QCD_7TeV
process = customise(process)

# End of customisation functions

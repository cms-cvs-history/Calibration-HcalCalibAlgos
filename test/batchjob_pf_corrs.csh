#!/bin/csh
#BSUB -q 1nh
##BSUB -J jfp

echo 'Start'

cmsrel CMSSW_3_1_4
cd CMSSW_3_1_4/src
cmsenv
cvs co Calibration/HcalCalibAlgos
#cp /afs/cern.ch/user/a/andrey/scratch1/CMSSW_3_1_4/src/Calibration/HcalCalibAlgos/plugins/ValidIsoTrkCalib.cc Calibration/HcalCalibAlgos/plugins
scram b
cd Calibration/HcalCalibAlgos/test

set respcorrdir=/afs/cern.ch/user/a/andrey/scratch1/CMSSW_3_1_4/src/Calibration/HcalCalibAlgos/data

# if you want to validate your own calibration, copy it to data/ from your local place: 
cp $respcorrdir/calibConst_IsoTrk_testCone_26.3cm.txt ../data/response_corrections.txt

cat > pfcorrs.py <<@EOF

import FWCore.ParameterSet.Config as cms

process = cms.Process("HcalPFCorrsCulculation")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Calibration.HcalCalibAlgos.HcalCorrPFCalculation_cfi")
process.load("Configuration.StandardSequences.GeometryECALHCAL_cff")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(5000)

process.load("HLTrigger.Timer.timer_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(

'rfio:/castor/cern.ch/user/a/abdullin/pi50_fullproduction_312/pi50_${1}.root'

     )
)

process.options = cms.untracked.PSet(
   wantSummary = cms.untracked.bool(True)
)

process.hcalRecoAnalyzer = cms.EDFilter("HcalCorrPFCalculation",
    outputFile = cms.untracked.string('HcalCorrPF_${1}.root'),
    eventype = cms.untracked.string('single'),
    mc = cms.untracked.string('yes'),
    sign = cms.untracked.string('*'),
    hcalselector = cms.untracked.string('all'),
#    RespcorrAdd = cms.untracked.bool(True),
#    PFcorrAdd = cms.untracked.bool(True),
    ConeRadiusCm = cms.untracked.double(30),
    ecalselector = cms.untracked.string('yes')
)

process.load("CondCore.DBCommon.CondDBSetup_cfi")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_31X_V5::All')
process.prefer("GlobalTag")

process.es_ascii2 = cms.ESSource("HcalTextCalibrations",
    appendToDataLabel = cms.string('recalibrate'),
    input = cms.VPSet(
     cms.PSet(
      object = cms.string('RespCorrs'),
      file = cms.FileInPath('Calibration/HcalCalibAlgos/data/calibConst_IsoTrk_testCone_26.3cm.txt')
             ),
     cms.PSet(
      object = cms.string('PFCorrs'),
      file = cms.FileInPath('Calibration/HcalCalibAlgos/data/HcalPFCorrs_v1.03_mc.txt')
             )
                     )
)


#process.TimerService = cms.Service("TimerService", useCPUtime = cms.untracked.bool(True))
#process.pts = cms.EDFilter("PathTimerInserter")
process.PathTimerService = cms.Service("PathTimerService")
process.p = cms.Path(process.hcalRecoAnalyzer)

#-----------
@EOF

cmsRun pfcorrs.py

set outdir=/afs/cern.ch/user/a/andrey/scratch1/CMSSW_3_1_4/src/Calibration/HcalCalibAlgos/test
#set outdir=/castor/cern.ch/user/a/andrey/pi300_310_pre10


cp HcalCorrPF_*.root $outdir/
#rfcp ValidFile_*.root $outdir/

cd ../../../../../

rm -rf CMSSW*
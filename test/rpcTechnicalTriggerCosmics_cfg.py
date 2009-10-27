import FWCore.ParameterSet.Config as cms
import os

maxevts   = 1000
globaltag = 'STARTUP31X_V2::All'
##globaltag = 'STARTUP3XY_V9::All'
inputfile = '/store/relval/CMSSW_3_1_2/RelValCosmics/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V2-v1/0007/C481562D-9278-DE11-8CA2-000423D9517C.root'

process   = cms.Process("RPCTechnicalTrigger")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories = ['*']
process.MessageLogger.destinations = ['cout']
process.MessageLogger.cout = cms.untracked.PSet(
    	threshold = cms.untracked.string('DEBUG'),
	INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(-1) ) )

#.. Geometry and Global Tags
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

#.. if cosmics: reconstruction sequence for Cosmics
process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

#..............................................................................................................
#.. EventSetup Configuration
#...

useEventSetup = 0
mytag         = 'test5'
database      = 'sqlite'

if database   == 'sqlite':
    dbconnection = 'sqlite_file:/afs/cern.ch/user/a/aosorio/public/rpcTechnicalTrigger/myrbconfig.db'
elif database == 'oraclerpc':
    dbconnection = 'oracle://devdb10/CMS_RPC_COMMISSIONING'
else:
    dbconnection = ''

if useEventSetup >= 1:

    from CondCore.DBCommon.CondDBCommon_cfi import *

    PoolDBESSource = cms.ESSource("PoolDBESSource",
                                  loadAll = cms.bool(True),
                                  toGet = cms.VPSet(cms.PSet( record = cms.string('RBCBoardSpecsRcd'),
                                                              tag = cms.string(mytag+'a')),
                                                    cms.PSet( record = cms.string('TTUBoardSpecsRcd'),
                                                              tag = cms.string(mytag+'b'))),
                                  DBParameters = cms.PSet( messageLevel = cms.untracked.int32(2),
                                                           authenticationPath = cms.untracked.string('')),
                                  messagelevel = cms.untracked.uint32(2),
                                  connect = cms.string(dbconnection) )

    CondDBCommon.connect = cms.string( dbconnection )

#..............................................................................................................

process.load("L1Trigger.RPCTechnicalTrigger.rpcTechnicalTrigger_cfi")

#.. use the provided hardware configuration parameters
process.rpcTechnicalTrigger.UseDatabase   = cms.untracked.int32(0)
process.rpcTechnicalTrigger.UseRPCSimLink = cms.untracked.int32(1)
process.rpcTechnicalTrigger.ConfigFile    = cms.untracked.string("hardware-pseudoconfig.txt")

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('rpcttbits.root'),
                               outputCommands = cms.untracked.vstring('drop *','keep L1GtTechnicalTriggerRecord_*_*_*') )

process.p = cms.Path(process.rpcTechnicalTrigger)

process.e = cms.EndPath(process.out)


import FWCore.ParameterSet.Config as cms
import os

mytag     = 'test1'
debugmode = 1
database  = ''
site      = os.environ.get("SITE")

#........................................................................................
if site == 'Local':
    inputfile = 'file:/opt/CMS/data/PrivateMC/Cosmic08/reco_CosmicMC_BOFF_2110.root'
else:
    inputfile = 'file:/afs/cern.ch/user/a/aosorio/scratch0/data/reco_CosmicMC_BOFF_2110.root'

if database == 'sqlite':
    dbconnection = 'sqlite_file:myrbconfig.db'
else:
    dbconnection = 'oracle://devdb10/CMS_RPC_COMMISSIONING'
#........................................................................................


process   = cms.Process("TestFlow")

process.load("FWCore.MessageService.MessageLogger_cfi")

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")

#.. Real data raw to digi
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

#.. reconstruction sequence for Cosmics
process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

#.. access database hardware configuration objects
process.load("CondCore.DBCommon.CondDBCommon_cfi")
process.PoolDBESSource = cms.ESSource("PoolDBESSource",
                                      loadAll = cms.bool(True),
                                      toGet = cms.VPSet(cms.PSet(
                                      record = cms.string('RBCBoardSpecsRcd'),
                                      tag = cms.string(mytag+'a')),
                                      cms.PSet( record = cms.string('TTUBoardSpecsRcd'),
                                      tag = cms.string(mytag+'b'))),
                                      DBParameters = cms.PSet(
                                      messageLevel = cms.untracked.int32(2),
                                      authenticationPath = cms.untracked.string('')),
                                      messagelevel = cms.untracked.uint32(2),
                                      connect = cms.string(dbconnection) )

process.CondDBCommon.connect = cms.string( dbconnection )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

process.testflow = cms.EDAnalyzer('RPCTechnicalTrigger',
                                  RPCTTDebugMode = cms.untracked.int32(debugmode),
                                  RBCLogicType = cms.untracked.string("ChamberORLogic"),
                                  TTULogicType = cms.untracked.string("TrackingAlg"),
                                  TmpDataFile = cms.untracked.string("testdata.txt") )

process.p = cms.Path(process.testflow)


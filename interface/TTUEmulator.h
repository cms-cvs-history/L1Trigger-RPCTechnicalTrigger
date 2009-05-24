// $Id: TTUEmulator.h,v 1.1 2009/05/16 19:43:30 aosorio Exp $
#ifndef TTUEMULATOR_H 
#define TTUEMULATOR_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/interface/RPCInputSignal.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/TTUConfiguration.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/RPCWheel.h"

#include "CondFormats/RPCObjects/interface/RBCBoardSpecs.h"
#include "CondFormats/RPCObjects/interface/TTUBoardSpecs.h"

#include <map>
#include <bitset>

/** @class TTUEmulator TTUEmulator.h
 *  
 *  This class performs the following tasks [ref 2]:
 *
 *
 *    - find a single or multiple muon tracks
 *    - find length of each track
 *    - produce a wheel level trigger
 *
 *  The default algorithm is implemented is TrackingAlg [ref 2].
 *
 *  ref 2: <EM>"A configurable Tracking Algorithm to detect cosmic muon
 *          tracks for the CMS-RPC based Technical Trigger", R.T.Rajan et al</EM>
 *
 *
 *  @author Andres Osorio
 *
 *  email: aosorio@uniandes.edu.co
 *
 *  @date   2008-10-15
 */

class TTUEmulator {
public: 
  /// Standard constructor
  TTUEmulator( ) { }; 
  
  TTUEmulator( int, int );
  
  TTUEmulator( int, const char *, const char *, int );
  
  TTUEmulator( int, const char *, const char * , const char *, int );
  
  virtual ~TTUEmulator( ); ///< Destructor
  
  bool initialise();
  
  void emulate();
  
  void processtest( RPCInputSignal * );
  
  void processlocal( RPCInputSignal * );
  
  void processglobal( RPCInputSignal * );
  
  void printinfo();
  
  void setSpecifications( const TTUBoardSpecs *, const RBCBoardSpecs *);
  
  int mode() {
    return m_mode;
  };
  
  void setmode(int _mode) {
    m_mode = _mode;
  };
  
  void setSpecs();
  
  int m_maxWheels;
  RPCWheel * m_Wheels;
  std::bitset<2> m_trigger;
  std::map<int, std::bitset<2> > m_triggerBx;
  
protected:
  
private:
  
  int m_id;
  int m_bx;
  int m_mode;
  
  int * m_wheelIds;
  
  std::string m_logtype;
  TTUInput         * m_ttuin;
  TTUConfiguration * m_ttuconf;
  
  bool m_debug;
  
};
#endif // TTUEMULATOR_H

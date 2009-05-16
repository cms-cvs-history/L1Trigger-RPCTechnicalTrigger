// $Id: RBCEmulator.h,v 1.2 2009/05/08 10:24:05 aosorio Exp $
#ifndef RBCEMULATOR_H 
#define RBCEMULATOR_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/interface/LogicTool.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCId.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCInput.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCConfiguration.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/ProcessInputSignal.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/RPCInputSignal.h"

#include "CondFormats/RPCObjects/interface/RBCBoardSpecs.h"

/** @class RBCEmulator RBCEmulator.h
 *  
 *
 *  @author Andres Osorio, Flavio Loddo, Marcello Maggi
 *
 *  email: aosorio@uniandes.edu.co
 *
 *  @date   2008-10-10
 */

class RBCEmulator {
public: 
  /// Standard constructor
  RBCEmulator( ); 
  
  RBCEmulator( const char * ); 

  RBCEmulator( const char * , const char * ); 
  
  RBCEmulator( const char * , const char * , int, int *); 
  
  virtual ~RBCEmulator( ); ///< Destructor

  void setSpecifications( const RBCBoardSpecs * );
    
  bool initialise();
  
  void setid( int , int * );
  
  void emulate();

  void emulate( RBCInput * );
  
  std::bitset<6> * getlayersignal( int _idx ) { return m_layersignal[_idx];};
  
  void printinfo();
  
  void printlayerinfo();

  RBCId          * m_rbcinfo;
  
protected:
  
private:
  
  ProcessInputSignal * m_signal;
  RBCConfiguration   * m_rbcconf;
  RBCInput           * m_input;
  
  std::bitset<6> * m_layersignal[2];
  
  //...
  
  int m_bx;
  
  std::string m_logtype;

  bool m_debug;
    
};
#endif // RBCEMULATOR_H
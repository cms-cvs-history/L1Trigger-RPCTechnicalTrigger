// $Id: $
#ifndef INTERFACE_RBCBASICCONFIG_H 
#define INTERFACE_RBCBASICCONFIG_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCId.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCConfiguration.h" 

/** @class RBCBasicConfig RBCBasicConfig.h interface/RBCBasicConfig.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2008-10-29
 */
class RBCBasicConfig : public RBCConfiguration {
public: 
  /// Standard constructor
  RBCBasicConfig( ) {}; 
  
  RBCBasicConfig( const char *); 

  RBCBasicConfig( const RBCBoardSpecs * , RBCId * );
  
  virtual ~RBCBasicConfig( ); ///< Destructor
  
  bool initialise();

  void preprocess( RBCInput & );
    
protected:
  
private:
  
  RBCId * m_rbcinfo;

  std::vector<int> m_vecmask;
  std::vector<int> m_vecforce;
    
};
#endif // INTERFACE_RBCBASICCONFIG_H
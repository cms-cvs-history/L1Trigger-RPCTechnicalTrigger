// $Id: $
// Include files 


// local
#include "L1Trigger/RPCTechnicalTrigger/src/RPCProcessDigiSignal.h"
#include "L1Trigger/RPCTechnicalTrigger/src/TTUGlobalSignal.h" 

//-----------------------------------------------------------------------------
// Implementation file for class : RPCProcessDigiSignal
//
// 2008-11-23 : Andres Felipe Osorio Oliveros
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RPCProcessDigiSignal::RPCProcessDigiSignal( const edm::ESHandle<RPCGeometry> & rpcGeom, 
                                            const edm::Handle<RPCDigiCollection> & digiColl ) 
{
  
  m_ptr_rpcGeom  = & rpcGeom;
  m_ptr_digiColl = & digiColl;

  m_wmin = dynamic_cast<RPCInputSignal*>( new TTUGlobalSignal( &m_data ) );
  
}
//=============================================================================
// Destructor
//=============================================================================
RPCProcessDigiSignal::~RPCProcessDigiSignal() {

  std::vector<RPCWheelMap*>::iterator itr;
  for(itr = m_wheelmapvec.begin(); itr != m_wheelmapvec.begin(); ++itr)
    delete (*itr);
  m_wheelmapvec.clear();

  if( m_wmin ) delete m_wmin;
  
} 

//=============================================================================
int RPCProcessDigiSignal::next() 
{
  
  //. Generate a Wheel map from Digi collection
  int prev_wheel_id = -10;
  RPCWheelMap * wheelmap = NULL;
  
  for (m_detUnitItr = (*m_ptr_digiColl)->begin(); 
       m_detUnitItr != (*m_ptr_digiColl)->end(); ++m_detUnitItr ) {
    
    m_digiItr = (*m_detUnitItr ).second.first;
    int bx = (*m_digiItr).bx();
    
    const RPCDetId & id  = (*m_detUnitItr).first;
    const RPCRoll * roll = dynamic_cast<const RPCRoll* >( (*m_ptr_rpcGeom)->roll(id));
    
    if((roll->isForward())) {
      std::cout << "RPCProcessDigiSignal: roll is forward" << std::endl;
      continue;
    }
    
    int wheel  = roll->id().ring() + 2;
    int sector = roll->id().sector() - 1;
    int layer  = roll->id().layer();
    
    std::cout << "Bx: "     << bx     << '\t'
              << "Wheel: "  << wheel  << '\t'
              << "Sector: " << sector << '\t'
              << "Layer: "  << layer  << '\n';
    
    if ( wheel != prev_wheel_id ) {
      wheelmap = new RPCWheelMap( wheel );
      m_wheelmapvec.push_back ( wheelmap );
    }
    
    wheelmap->addHit ( bx, sector, layer );
    //...
    prev_wheel_id = wheel;
    
  }

  //.. add up all bunch X info into a single map

  std::vector<RPCWheelMap*>::const_iterator itr;
  itr = m_wheelmapvec.begin();
  while( itr!=m_wheelmapvec.end()){
    (*itr)->contractMaps();
    ++itr;
  }
  
  //... set up now data to be processed
  int wheel      = -10;
  int prev_wheel = -100;
  itr = m_wheelmapvec.begin();
  while( itr!=m_wheelmapvec.end()){
    wheel = (*itr)->wheelid();
    if ( wheel != prev_wheel ) {
      (*itr)->prepareData();
      m_data.insert( std::make_pair( (*itr)->wheelid() * 10000 , (*itr)->m_ttuin ) );
    }
    prev_wheel = wheel;
    ++itr;
  }
  
  //...
  
  return 1;
  
}


// Include files 

 // from Gaudi
#include "GaudiKernel/ToolFactory.h"

// local
#include "TupleTTInfo3.h"

#include <Kernel/GetIDVAlgorithm.h>

#include "Event/Track.h"
#include "Kernel/LHCbID.h"


//-----------------------------------------------------------------------------
// Implementation file for class providing TT information
//
// 2013-05-10 : Thomas Blake
//-----------------------------------------------------------------------------



// Declaration of the Tool Factory
DECLARE_TOOL_FACTORY( TupleTTInfo3 )


//=============================================================================
// Standard constructor, initializes variables
//=============================================================================

TupleTTInfo3::TupleTTInfo3( const std::string& type,
                          const std::string& name,
                          const IInterface* parent )
  : TupleToolBase( type, name, parent )  
{
  declareInterface<IParticleTupleTool>(this);
}

//=============================================================================
// Destructor
//=============================================================================

TupleTTInfo3::~TupleTTInfo3() {} ;

//=============================================================================
// Initialization
//=============================================================================

StatusCode TupleTTInfo3::initialize() {

  StatusCode sc = TupleToolBase::initialize(); // must be executed first
  if ( sc.isFailure() ) return sc;  // error printed already by GaudiAlgorithm
  
  //dva_  = Gaudi::Utils::getIDVAlgorithm ( contextSvc(), this ) ;
  
  //dist_ = dva_ -> distanceCalculator() ;
  //vert_ = dva_ -> vertexFitter() ;
  
  //desc_ = tool<IParticleDescendants>("ParticleDescendants",this);
  
  if ( msgLevel(MSG::DEBUG) ) debug() << "==> Initialize" << endmsg;
  
  return StatusCode::SUCCESS;
}



//=============================================================================
//  Finalize
//=============================================================================
StatusCode TupleTTInfo3::finalize() {

  if ( msgLevel(MSG::DEBUG) ) debug() << "==> Finalize" << endmsg;

  return TupleToolBase::finalize();  // must be called after all other actions
}

//=============================================================================

bool TupleTTInfo3::hasTrack( const LHCb::Particle* P ) const 
{
  return ( P->proto() && P->proto()->track() );
}



StatusCode TupleTTInfo3::fill( const LHCb::Particle* mother, 
                              const LHCb::Particle* P, 
                              const std::string& head, 
                              Tuples::Tuple& tuple )
{
  
  if( !P ) return StatusCode::FAILURE;
  
  const std::string prefix = fullName(head);
  
  bool test = true ;
  
  if ( hasTrack( P ) )
  {
    const LHCb::Track* track = P->proto()->track();
    
    const std::vector< LHCb::LHCbID > idcont = track->lhcbIDs() ;
    const std::vector< const LHCb::Measurement* >  mcont = track->measurements();
    
    unsigned int nTTIDs    = 0;
    unsigned int nTTLayers = 0;
    unsigned int nTTMeasurements = 0;
    
    std::vector< LHCb::LHCbID >::const_iterator iid;
    std::vector< const LHCb::Measurement* >::const_iterator im ;

    unsigned int nOTIDs = 0;
    unsigned int nITIDs = 0;

    bool hitlayer[4];
    
    for ( int ilayer = 0; ilayer < 4; ++ilayer )
    {
      hitlayer[ ilayer ] = false;
    }

    for ( iid = idcont.begin(); iid != idcont.end(); ++iid )
    {
      if ( iid->isTT() ){ 
        nTTIDs++;
        
        LHCb::STChannelID channel = iid->stID();
        
        unsigned int layer = (channel.station()-1)*2 + channel.layer()-1 ;
        
        hitlayer[layer] = true;
      }

      if ( iid->isIT() ) nITIDs++;
      if ( iid->isOT() ) nOTIDs++;
    }
    
    for (  int ilayer = 0; ilayer < 4; ++ilayer )
    {
      if ( hitlayer[ilayer] ) nTTLayers++;
    }
    
    
    for ( im = mcont.begin(); im != mcont.end(); ++im )
    {
      if ( (*im)->type() == LHCb::Measurement::TT ) nTTMeasurements++;
    }

    test &= tuple->column(prefix + "_TT_IDs", nTTIDs );
    test &= tuple->column(prefix + "_TT_Layers", nTTLayers );
    test &= tuple->column(prefix + "_TT_Measurements", nTTMeasurements );
    
    // Position at the TT 

    const LHCb::State& stateOr = track->closestState(6000);
    const LHCb::State* stateTT = track->stateAt( LHCb::State::AtTT );
    
    test &= tuple->column(prefix + "_Origin_"      , stateOr.position() );
    test &= tuple->column(prefix + "_Origin_qOverp", stateOr.qOverP() );
    
    if ( stateTT )
    {
      test &= tuple->column(prefix + "_TT_", stateTT->position() );
    }
    else 
    {
      test &=  tuple->column(prefix + "_TT_X", 0 );
      test &=  tuple->column(prefix + "_TT_Y", 0 );
      test &=  tuple->column(prefix + "_TT_Z", 0 );
    }
    
    test &= tuple->column( prefix + "_TrackFit_MatchChi2", 
                           track->info( LHCb::Track::MatchChi2 , -999 ) );

    test &= tuple->column( prefix + "_TrackFit_FitVeloChi2", 
                           track->info( LHCb::Track::FitVeloChi2 , -999 ) );

    test &= tuple->column( prefix + "_TrackFit_FitVeloNDoF", 
                           track->info( LHCb::Track::FitVeloNDoF , -999 ) );
    
    test &= tuple->column( prefix + "_TrackFit_FitTChi2", 
                           track->info( LHCb::Track::FitTChi2 , -999 ) );

    test &= tuple->column( prefix + "_TrackFit_FitTNDoF", 
                           track->info( LHCb::Track::FitTNDoF , -999 ) );

    test &= tuple->column(prefix + "_IT_IDs", nITIDs );
    
    test &= tuple->column(prefix + "_OT_IDs", nOTIDs );
  }
  
  return StatusCode( test );
}


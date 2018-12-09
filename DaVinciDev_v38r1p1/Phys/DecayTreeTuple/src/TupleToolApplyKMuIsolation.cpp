// Include files

// from Gaudi
#include "GaudiKernel/ToolFactory.h"

// local
#include "TupleToolApplyKMuIsolation.h"

#include <Kernel/GetIDVAlgorithm.h>
#include <Kernel/IDVAlgorithm.h>
#include <Kernel/IDistanceCalculator.h>
#include <Kernel/IVertexFit.h>

#include "GaudiAlg/Tuple.h"
#include "GaudiAlg/TupleObj.h"

#include "Event/Particle.h"
#include "Event/MCParticle.h"
#include "GaudiKernel/DeclareFactoryEntries.h"
#include <functional>
#include "TrackInterfaces/ITrackVertexer.h"
#include "Linker/LinkerTable.h"
#include "Kernel/IPVReFitter.h"
#include "LoKi/ParticleCuts.h"

#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TPluginManager.h"
#include "TStopwatch.h"


#include "TMVA/Reader.h"
//#include "TMVA/Config.h"
//#include "TMVA/Tools.h"


//-----------------------------------------------------------------------------
// Implementation file for class : TupleToolVtxIsoln
//
// @author Mitesh Patel, Patrick Koppenburg
// @date   2008-04-15
//-----------------------------------------------------------------------------

// Declaration of the Tool Factory
// actually acts as a using namespace TupleTool
DECLARE_TOOL_FACTORY( TupleToolApplyKMuIsolation );

using namespace LHCb;
//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TupleToolApplyKMuIsolation::TupleToolApplyKMuIsolation( const std::string& type,
                                      const std::string& name,
                                      const IInterface* parent )
  : TupleToolBase ( type, name , parent )
    , m_dva(0) 
    , m_dist(0)
    , m_pVertexFit(0)
{
  declareInterface<IParticleTupleTool>(this);

  m_inputParticles.push_back("/Event/Phys/StdAllNoPIDsPions");
  m_inputParticles.push_back("/Event/Phys/StdNoPIDsUpPions");
  m_inputParticles.push_back("Phys/StdNoPIDsVeloPions");
  //m_inputParticles.push_back("/Event/Phys/StdNoPIDsVeloElectrons");

  
  //havent removed / added any of this yet
  declareProperty( "MaxDeltaChi2", m_deltaChi2 = 9.0);
  declareProperty( "MaxChi2", m_Chi2 = 9.0);
  declareProperty( "VertexFit", m_typeVertexFit = "default");
  declareProperty("InputParticles", m_inputParticles );;
  declareProperty("OutputSuffix", m_outputSuffix = "" );
  declareProperty("WeightsFile", m_weightsName = "weights.xml" );

}

//=============================================================================

StatusCode TupleToolApplyKMuIsolation::initialize() {
  if( ! TupleToolBase::initialize() ) return StatusCode::FAILURE;
  
  m_dva = Gaudi::Utils::getIDVAlgorithm ( contextSvc() ) ;
  if (0==m_dva) return Error("Couldn't get parent DVAlgorithm", 
                             StatusCode::FAILURE);
  m_dist       = tool<IDistanceCalculator>("LoKi::DistanceCalculator",this);
  m_p2mcAssoc = tool<IParticle2MCAssociator>("DaVinciSmartAssociator", this);
  if( !m_dist ){
    Error("Unable to retrieve the IDistanceCalculator tool");
    return StatusCode::FAILURE;
  }
  m_pvReFitter = tool<IPVReFitter>("AdaptivePVReFitter", this );
  m_pVertexFit= m_dva->vertexFitter();
  //m_pVertexFit= tool<ITrackVertexer>

  if( !m_pVertexFit ){
    Error("Unable to retrieve the IVertexFit tool");
    return StatusCode::FAILURE;
  }
  
  
  
  m_Reader = new TMVA::Reader( "!Silent" );
  /*std::vector<TString> vars ;
  vars.push_back("pt");           // 0
  vars.push_back("ipchi2");                 // 1
  vars.push_back("minipchi2");      // 5
  vars.push_back("opening");           // 8
  vars.push_back("flight");                   // 15
  vars.push_back("trackchi2");                  // 22
  vars.push_back("ghost");                 // 29
  for (unsigned int i = 0 ; i < vars.size() ; i++){
    m_Reader->AddVariable( vars[i],vars[i], "", 'F' );
  }
  m_Reader->AddSpectator( "type", "type", "", 'I' );*/
  
  m_Reader->AddVariable( "pt",&pt);
  m_Reader->AddVariable( "ipchi2",&chi2);
  m_Reader->AddVariable( "minipchi2",&minipchi2);
  m_Reader->AddVariable( "opening",&opening);
  //m_Reader->AddVariable( "dlogfd",&dlogfd);
  m_Reader->AddVariable( "trackchi2",&trackchi2);
  m_Reader->AddVariable( "ghost",&ghostprob);
  m_Reader->AddSpectator( "type",&type);
//  m_Reader->AddVariable( "Track_DELTAFLIGHT",&deltafd);
  //dummy variables
  //m_Reader->AddVariable( "Bplus_PT",&dummy);
  //m_Reader->AddVariable( "Dst_PT",&Dst_PT);
  //m_Reader->AddVariable( "Bplus_ENDVERTEX_CHI2",&vertexchi2);
  //m_Reader->AddVariable( "Dst_ENDVERTEX_CHI2",&dummy);
  //m_Reader->AddVariable( "Dst_FDCHI2_OWNPV",&dummy);
  //m_Reader->AddVariable( "log(1-D_DIRA_OWNPV)",&dummy);
  //m_Reader->AddVariable( "log(1-Bplus_DIRA_OWNPV)",&dummy);
  
  

  
   

  //reader->AddVariable("Bplus_PT",&Bplus_PTf);
  //reader->AddVariable("Dst_PT",&Dst_PTf);
  m_Reader->BookMVA( "BDT method", m_weightsName );
  
    if( !m_Reader ){
    Error("Unable to retrieve the IVertexFit tool");
    return StatusCode::FAILURE;
  }
  return StatusCode::SUCCESS;
}

//=============================================================================

StatusCode TupleToolApplyKMuIsolation::fill( const Particle* mother
                                    , const Particle* P
                                    , const std::string& head
                                    , Tuples::Tuple& tuple )
{
  
  const std::string prefix=fullName(head);
  Assert( P && mother && m_dist
          , "This should not happen, you are inside TupleToolVtxIsoln.cpp :(" );

  
  bool test=true;

  /*
  const LHCb::Vertex* vtx;
  if (P->isBasicParticle()){
    vtx = mother->endVertex(); 
  }
  else{
    vtx = P->endVertex();
    
  }
  debug()<<"vertex for P, ID " <<P->particleID().pid()<<" = " <<vtx<<" at "<<vtx->position()<<  endmsg;
  if( !vtx ){
    Error("Can't retrieve the  vertex for " + prefix );
    return StatusCode::FAILURE;
  }
  */  
  std::vector<const LHCb::Track*> daughtertracks;
  daughtertracks.clear();
  LHCb::Particle::ConstVector source;
  LHCb::Particle::ConstVector target;
  LHCb::Particle::ConstVector finalStates;
  LHCb::Particle::ConstVector parts2Vertex;
  LHCb::Particle::ConstVector parts2VertexD;
  double maxbdt = -2;
  std::vector<const LHCb::Particle*> pvect;
  std::vector<double> Mvect;
  double M_pKpi(0.0), M_ppiK(0.0), M_pKpipipi(0.0);
  double bdt2(-2.), bdt3(-2.), bdt4(-2.);
  const LHCb::Particle* ppro(NULL);
  const LHCb::Particle* tr1(NULL);
  const LHCb::Particle* tr2(NULL);
  const LHCb::Particle* tr3(NULL);
  const LHCb::Particle* tr4(NULL);
  LHCb::MuonPID mupid;
  bool ismu1=false, ismu2=false, ismu3=false, ismu4=false;
  bool b1=false, b2=false, b3 =false, b4 =false;
  double p1x(0), p1y(0), p1z(0), p2x(0), p2y(0), p2z(0);
  double p3x(0), p3y(0), p3z(0), p4x(0), p4y(0), p4z(0);
  double M_Kpi, M_Kpipi;
  double pid1pi(-1000.0), pid1K(-1000.0), pid1p(-1000.0), pid1mu(-1000.0);
  double pid2pi(-1000.0), pid2K(-1000.0), pid2p(-1000.0), pid2mu(-1000.0);
  double pid3pi(-1000.0), pid3K(-1000.0), pid3p(-1000.0), pid3mu(-1000.0);
  double pid4pi(-1000.0), pid4K(-1000.0), pid4p(-1000.0), pid4mu(-1000.0);
  int chtr1(0),chtr2(0),chtr3(0), chtr4(0);
  int tr1_type(0), tr2_type(0), tr3_type(0), tr4_type(0);
  double deltafd;
  vertexchi2 = P->endVertex()->chi2();
  parts2Vertex.clear();
  parts2VertexD.clear();
  
  //   const LHCb::Particle* prefix = P;
  if (P->isBasicParticle()){
    source.push_back(mother);
  }
  else{
    source.push_back(P);
  }
  LHCb::Vertex dv2;

  do {
    target.clear();
    for(LHCb::Particle::ConstVector::const_iterator isource = source.begin(); 
        isource != source.end(); isource++){
      
      if(!((*isource)->daughters().empty())){
        
        LHCb::Particle::ConstVector tmp = (*isource)->daughtersVector();
        
        for( LHCb::Particle::ConstVector::const_iterator itmp = tmp.begin(); 
             itmp!=tmp.end(); itmp++){
          target.push_back(*itmp);
          // Add the final states, i.e. particles with proto and ignoring gammas
          if((*itmp)->proto() && 22 != (*itmp)->particleID().pid()){
	//	if((*itmp)->particleID().abspid() == 413) Dst_PT = (*itmp)->pt();
//		if ((*itmp)->particleID().abspid()  == 2212)
//		{
//		    ppro = (*itmp);
//		}	
		//only add final state proton and muon
//		if ((*itmp)->particleID().abspid()  == 2212 || (*itmp)->particleID().abspid() == 13)
                if ((*itmp)->particleID().abspid() == 13 || (*itmp)->particleID().abspid() == 321)
		{
           	finalStates.push_back(*itmp);
           	daughtertracks.push_back((*itmp)->proto()->track());
		}	
           }
        }
      } // if endVertex
    } // isource
    source = target;
  } while(target.size() > 0);
  if (msgLevel(MSG::DEBUG)) debug() << "Final states size= " <<  finalStates.size()  << endreq;
  //warning() << " D VERTEX CHI2 " << dv2.chi2() << " NDOF " << dv2.nDoF() << endreq;
  //warning() << "DAUGHTER SIZE " << daughtertracks.size() << endreq;
  //default gives best tracks (why would you default to anything less than the best?)  


  

  LHCb::Vertex v;
  //double chi2ndof = 0;//oldvtx->chi2();
  //int ndof = 0;//oldvtx->nDoF();
  
 /* 
    if (P->isBasicParticle()){
    parts2Vertex.push_back(P);
  }
  else{
    parts2Vertex = P->daughtersVector();
    StatusCode sc = m_pVertexFit->fit(v,parts2Vertex);
  }*/
  parts2Vertex = finalStates;
  StatusCode sc = m_pVertexFit->fit(v,parts2Vertex);

  //hack due to lack of programming skill
  //v=new LHCb::Vertex(v2);
  //********Loop through tracks************
  
  //number below am IPCHI2 threshold isnt that useful, will probably remove it 

  
  LHCb::Particle::ConstVector theParts;
    

       
  for(std::vector<std::string>::iterator i = m_inputParticles.begin();
      i !=m_inputParticles.end(); ++i){

    if (!exist<LHCb::Particle::Range>(*i+"/Particles")){
      if (msgLevel(MSG::DEBUG)) debug() << "No particles at " << *i << " !!!!!" << endreq;
      continue;
    }

    LHCb::Particle::Range parts = get<LHCb::Particle::Range>(*i+"/Particles");
    if (msgLevel(MSG::DEBUG)) debug() << "Getting particles from " << *i
                                      << " with " << (parts).size() << " particles" << endreq;
    //warning() << "Getting particles from " << *i
    //                                  << " with " << (parts).size() << " particles" << endreq;
    for(LHCb::Particle::Range::const_iterator iparts = (parts).begin();
        iparts != (parts).end(); ++iparts)
    {
    const LHCb::Particle* part = (*iparts);
    
    
    //if(isTrackInDecay(part->proto()->track(),daughtertracks)) warning() << "FOUND DAUGHTER TRACK" << endreq;
    if(part->proto()->track()->type() < 5 && !isTrackInDecay(part->proto()->track(),daughtertracks)){
    LHCb::Vertex vtxWithExtraTrack;
    parts2Vertex.push_back(*iparts);
    StatusCode sc3 = m_pVertexFit->fit (vtxWithExtraTrack,parts2Vertex);
    parts2Vertex.pop_back();
    opening = getopening(part->proto()->track(),P);
    minipchi2 = getminipchi(part);
    newfdchi2 = getfdchi2(part->proto()->track(),vtxWithExtraTrack);
    oldfdchi2 = getfdchi2(part->proto()->track(),v);
    ghostprob = part->proto()->track()->ghostProbability();
    trackchi2 = part->proto()->track()->chi2PerDoF();
    deltafd = oldfdchi2; - newfdchi2;
    type = part->proto()->track()->type();

    
    if (deltafd > 0) 
    {dlogfd = log(deltafd);}
    else
    {dlogfd = log(-deltafd);}

    if(part->proto()->track()->type() == 1) pt = part->proto()->track()->momentum().z();
    else pt = part->proto()->track()->pt();



    if(ghostprob > 0.5){continue;}


    //warning() << "type " << type << " opening " << opening << " pt " << pt << endreq;

    if(part->proto()->track()->type() == 3 && !(opening > 0.994 )){continue;}
    if(part->proto()->track()->type() == 4 && !(opening > 0.98)){continue;}
    if(part->proto()->track()->type() == 1 && !(opening > 0.98)){continue;}    
    //if(track->info(LHCb::Track::CloneDist, -1.) > 0){continue;}
    StatusCode sc = StatusCode::SUCCESS;
    double tmpip, tmpchi2;
    StatusCode dump = m_dist->distance((const LHCb::Particle *) part,(const LHCb::Vertex *)&v,tmpip,tmpchi2);
    chi2=tmpchi2;
	//StatusCode dump2 = m_dist->distance((const LHCb::Particle *) part,(const LHCb::Vertex *)vd,D_ip,D_chi2);
	    
	    if(chi2 < 50){
	        dummy = 4000;            
		float bdtval = m_Reader->EvaluateMVA( "BDT method" );
            //warning() << "bdtval " << bdtval << " old maxbdt " << maxbdt << endreq;
		if (bdtval > maxbdt) 
		{
		    bdt4 = bdt3;
		    bdt3 = bdt2;
		    bdt2 = maxbdt;
		    tr4 = tr3;
		    tr3 = tr2;
		    tr2 = tr1;
		    maxbdt = bdtval;
		    tr1 = part;
		}
		else if(bdtval > bdt2)
		{
		    bdt4 = bdt3;
		    bdt3 = bdt2;
		    bdt2 = bdtval;
		    tr4 = tr3;
		    tr3 = tr2;
		    tr2 = part;
		}
		else if(bdtval > bdt3)
		{
		    bdt4 = bdt3;
		    bdt3 = bdtval;
		    tr4 = tr3;
		    tr3 = part;		
		}
		else if(bdtval > bdt4)
		{
		    bdt4 = bdt3;
		    tr4 = part;
		}
		    
	        //warning() << "new max bdtval " << maxbdt << endreq;
	    }
	    

    }
  } // end particles loop
 }//end particle types loop

  
  
  if(tr1 != NULL )
  {
      b1 = true;
  p1x = tr1->momentum().px();
  p1y = tr1->momentum().py();
  p1z = tr1->momentum().pz();
      chtr1 = tr1->charge();
  tr1_type = tr1->proto()->track()->type();

  }
  if(tr2 != NULL )
  {
      b2 = true;
  p2x = tr2->momentum().px();
  p2y = tr2->momentum().py();
  p2z = tr2->momentum().pz();
  chtr2 = tr2->charge();
  tr2_type = tr2->proto()->track()->type();
  }
  if(tr3 != NULL )
  {
      b3 = true;
  p3x = tr3->momentum().px();
  p3y = tr3->momentum().py();
  p3z = tr3->momentum().pz();
  chtr3 = tr3->charge();
  tr3_type = tr3->proto()->track()->type();
  }
  if(tr4 != NULL )
  {
      b4 = true;
  p4x = tr4->momentum().px();
  p4y = tr4->momentum().py();
  p4z = tr4->momentum().pz();
  chtr4 = tr4->charge();
  tr4_type = tr4->proto()->track()->type();
  }
  

  if(tr1 != NULL )
  {
  if(tr1->proto() != NULL )
  {
  ismu1 = LoKi::Cuts::ISMUON(tr1);
  pid1K = tr1->proto()->info(LHCb::ProtoParticle::CombDLLk,-1000);
  pid1p = tr1->proto()->info(LHCb::ProtoParticle::CombDLLp,-1000);
  pid1mu = tr1->proto()->info(LHCb::ProtoParticle::CombDLLmu,-1000);
  pid1pi = tr1->proto()->info(LHCb::ProtoParticle::CombDLLpi,-1000);
  }
  }
  if(tr2 != NULL )
  {
  if(tr2->proto() != NULL )
  {
  ismu2 = LoKi::Cuts::ISMUON(tr2);
  pid2K = tr2->proto()->info(LHCb::ProtoParticle::CombDLLk,-1000);
  pid2p = tr2->proto()->info(LHCb::ProtoParticle::CombDLLp,-1000);
  pid2mu = tr2->proto()->info(LHCb::ProtoParticle::CombDLLmu,-1000);
  pid2pi = tr2->proto()->info(LHCb::ProtoParticle::CombDLLpi,-1000);
  }
  }
  if(tr3 != NULL )
  {
  if(tr3->proto() != NULL )
  {
  ismu3 = LoKi::Cuts::ISMUON(tr3);
  pid3K = tr3->proto()->info(LHCb::ProtoParticle::CombDLLk,-1000);
  pid3p = tr3->proto()->info(LHCb::ProtoParticle::CombDLLp,-1000);
  pid3mu = tr3->proto()->info(LHCb::ProtoParticle::CombDLLmu,-1000);
  pid3pi = tr3->proto()->info(LHCb::ProtoParticle::CombDLLpi,-1000);
  }
  }
  if(tr4 != NULL )
  {
  if(tr4->proto() != NULL )
  {
  ismu4 = LoKi::Cuts::ISMUON(tr4);
  pid4K = tr4->proto()->info(LHCb::ProtoParticle::CombDLLk,-1000);
  pid4p = tr4->proto()->info(LHCb::ProtoParticle::CombDLLp,-1000);
  pid4mu = tr4->proto()->info(LHCb::ProtoParticle::CombDLLmu,-1000);
  pid4pi = tr4->proto()->info(LHCb::ProtoParticle::CombDLLpi,-1000);
  }
  }
  
  tuple->column(prefix + "_pmu_ISOLATION_BDT1" + m_outputSuffix,  maxbdt );
  tuple->column(prefix + "_pmu_ISOLATION_BDT2" + m_outputSuffix,  bdt2 );
  tuple->column(prefix + "_pmu_ISOLATION_BDT3" + m_outputSuffix,  bdt3 );
  tuple->column(prefix + "_pmu_ISOLATION_BDT4" + m_outputSuffix,  bdt4 );
//  tuple->column(prefix + "_M_pKpi" + m_outputSuffix,  M_pKpi );
//  tuple->column(prefix + "_M_pKpipipi" + m_outputSuffix,  M_pKpipipi );
//  tuple->column(prefix + "_M_ppiK" + m_outputSuffix,  M_ppiK );
//  tuple->column(prefix + "_M_Kpi" + m_outputSuffix,  M_Kpi );
  tuple->column(prefix + "_pmu_TR1_PX" + m_outputSuffix,  p1x );
  tuple->column(prefix + "_pmu_TR1_PY" + m_outputSuffix,  p1y );
  tuple->column(prefix + "_pmu_TR1_PZ" + m_outputSuffix,  p1z );
  tuple->column(prefix + "_pmu_TR2_PX" + m_outputSuffix,  p2x );
  tuple->column(prefix + "_pmu_TR2_PY" + m_outputSuffix,  p2y );
  tuple->column(prefix + "_pmu_TR2_PZ" + m_outputSuffix,  p2z );
  tuple->column(prefix + "_pmu_TR4_PX" + m_outputSuffix,  p4x );
  tuple->column(prefix + "_pmu_TR4_PY" + m_outputSuffix,  p4y );
  tuple->column(prefix + "_pmu_TR4_PZ" + m_outputSuffix,  p4z );
  tuple->column(prefix + "_pmu_TR3_PX" + m_outputSuffix,  p3x );
  tuple->column(prefix + "_pmu_TR3_PY" + m_outputSuffix,  p3y );
  tuple->column(prefix + "_pmu_TR3_PZ" + m_outputSuffix,  p3z );
  tuple->column(prefix + "_pmu_TR1_isMu" + m_outputSuffix,  ismu1 );
  tuple->column(prefix + "_pmu_TR1_isMu" + m_outputSuffix,  ismu1 );
  tuple->column(prefix + "_pmu_TR3_isMu" + m_outputSuffix,  ismu3 );
  tuple->column(prefix + "_pmu_TR4_isMu" + m_outputSuffix,  ismu4 );
  tuple->column(prefix + "_pmu_TR1_NNULL" + m_outputSuffix,  b1 );
  tuple->column(prefix + "_pmu_TR2_NNULL" + m_outputSuffix,   b2 );
  tuple->column(prefix + "_pmu_TR3_NNULL" + m_outputSuffix,  b3 );
  tuple->column(prefix + "_pmu_TR4_NNULL" + m_outputSuffix,  b4 );

  tuple->column(prefix + "_pmu_TR1_PIDK" + m_outputSuffix,  pid1K );
  tuple->column(prefix + "_pmu_TR1_PIDp" + m_outputSuffix,  pid1p );
  tuple->column(prefix + "_pmu_TR1_PIDmu" + m_outputSuffix,  pid1mu );
  tuple->column(prefix + "_pmu_TR1_PIDpi" + m_outputSuffix,  pid1pi );
	    
  tuple->column(prefix + "_pmu_TR2_PIDK" + m_outputSuffix,  pid2K );
  tuple->column(prefix + "_pmu_TR2_PIDp" + m_outputSuffix,  pid2p );
  tuple->column(prefix + "_pmu_TR2_PIDmu" + m_outputSuffix,  pid2mu );
  tuple->column(prefix + "_pmu_TR2_PIDpi" + m_outputSuffix,  pid2pi );

  tuple->column(prefix + "_pmu_TR3_PIDK" + m_outputSuffix,  pid3K );
  tuple->column(prefix + "_pmu_TR3_PIDp" + m_outputSuffix,  pid3p );
  tuple->column(prefix + "_pmu_TR3_PIDmu" + m_outputSuffix,  pid3mu );
  tuple->column(prefix + "_pmu_TR3_PIDpi" + m_outputSuffix,  pid3pi );

  tuple->column(prefix + "_pmu_TR4_PIDK" + m_outputSuffix,  pid4K );
  tuple->column(prefix + "_pmu_TR4_PIDp" + m_outputSuffix,  pid4p );
  tuple->column(prefix + "_pmu_TR4_PIDmu" + m_outputSuffix,  pid4mu );
  tuple->column(prefix + "_pmu_TR4_PIDpi" + m_outputSuffix,  pid4pi );

  tuple->column(prefix + "_pmu_TR1_CH" + m_outputSuffix,  chtr1 );
  tuple->column(prefix + "_pmu_TR2_CH" + m_outputSuffix,  chtr2 );
  tuple->column(prefix + "_pmu_TR3_CH" + m_outputSuffix,  chtr3 );
  tuple->column(prefix + "_pmu_TR4_CH" + m_outputSuffix,  chtr4 );
  return StatusCode(test);
}

//=========================================================================
//  
//=========================================================================
const Vertex* TupleToolApplyKMuIsolation::originVertex( const Particle* top
                                               , const Particle* P ) const {
  if( top == P || P->isBasicParticle() ) return 0;
  
  const SmartRefVector< LHCb::Particle >& dau = top->daughters ();
  if( dau.empty() ){
    // if (msgLevel(MSG::DEBUG)) debug() << " Particle has no daughters! "  << endreq;
    return 0;
  }
  
  SmartRefVector< LHCb::Particle >::const_iterator it;
  for( it = dau.begin(); dau.end()!=it; ++it ){
    if( P == *it ){ // I found the daughter
      return top->endVertex();
    }
  }
  
  // vertex not yet found, get deeper in the decay:
  for( it = dau.begin(); dau.end()!=it; ++it ){
    if( P != *it && !(*it)->isBasicParticle() ){
      const Vertex* vv = originVertex( *it, P );
      if( vv ) return vv;
    }
  }
  return 0;
}


//=============================================================================
// Check if the track is already in the decay
//=============================================================================
bool TupleToolApplyKMuIsolation::isTrackInDecay(const LHCb::Track* track, std::vector<const LHCb::Track*> daughters){
  bool isInDecay = false;
        //loop over daughters
        for(std::vector<const LHCb::Track*>::iterator it = daughters.begin(); it != daughters.end(); ++it){
        const LHCb::Track* itrack = (*it);
        if(itrack){
         if(itrack == track){
          if ( msgLevel(MSG::DEBUG) ) debug() << "Track is in decay, skipping it" << endmsg;
          isInDecay = true;
          }
         }        
  }//end daughter loop
      
  return isInDecay;
}

//=============================================================================
// MINIPCHI2 for a track
//=============================================================================
double TupleToolApplyKMuIsolation::getminipchi(const LHCb::Particle* track){

double minchi2 = -1 ;
const RecVertex::Range PV = m_dva->primaryVertices();
  if ( !PV.empty() ){
    for ( RecVertex::Range::const_iterator pv = PV.begin() ; pv!=PV.end() ; ++pv){
      double ip, chi2;
      StatusCode test2 = m_dist->distance ( (const LHCb::Particle*)track, *pv, ip, chi2 );
        if ((chi2<minchi2) || (minchi2<0.)) 
        {
	LHCb::RecVertex newPV(**pv);
        StatusCode scfit = m_pvReFitter->remove(track, &newPV);
	LHCb::RecVertex* newPVPtr = (LHCb::RecVertex*)&newPV;
	test2 = m_dist->distance ((LHCb::Particle *)track, (LHCb::VertexBase*) newPVPtr, ip, chi2 );
        minchi2 = chi2 ;       
        } 
    }

}

return minchi2;
}

double TupleToolApplyKMuIsolation::getfdchi2(const LHCb::Track* track, LHCb::Vertex Vtx){

double minchi2 = -1 ;
double fdchi2 = -1;
double fd;
const RecVertex::Range PV = m_dva->primaryVertices();
  if ( !PV.empty() ){
    for ( RecVertex::Range::const_iterator pv = PV.begin() ; pv!=PV.end() ; ++pv){
      double ip, chi2;
      StatusCode test2 = m_dist->distance ( (const LHCb::Track *)track, *pv, ip, chi2 );
        if ((chi2<minchi2) || (minchi2<0.)) 
        {
          minchi2 = chi2 ;
	  StatusCode test2 = m_dist->distance ( *pv, &Vtx, fd, fdchi2 ); 
        } 
    }

}

return fdchi2;
}
double TupleToolApplyKMuIsolation::getM(std::vector<const LHCb::Particle*> pvect ,std::vector<double> Mvect)
    {
	double px(0.), py(0.), pz(0.), E(0.);
	int size = pvect.size();
	for(int i = 0; i < size; i++)
	{
	    px += pvect[i]->momentum().px();
	    py += pvect[i]->momentum().py();
	    pz += pvect[i]->momentum().pz();
	    E += sqrt(Mvect[i] * Mvect[i] + pvect[i]->p() * pvect[i]->p());
	}
	return sqrt(E * E - ( px * px) - ( py * py) - ( pz * pz)  );

    }

//=============================================================================
// Opening angle for a track and particle
//=============================================================================
double TupleToolApplyKMuIsolation::getopening(const LHCb::Track* track,const  LHCb::Particle* P){
    Gaudi::XYZVector A = P->momentum().Vect();
    Gaudi::XYZVector B = track->momentum();
    double cosopening = A.Dot( B ) / std::sqrt( A.Mag2()*B.Mag2() );
    return cosopening;
}

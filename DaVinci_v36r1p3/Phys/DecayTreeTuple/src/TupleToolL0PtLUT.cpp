#include "GaudiKernel/ToolFactory.h"
#include "TupleToolL0PtLUT.h"
#include "Event/RawEvent.h"

#include "GaudiAlg/Tuple.h"
#include "GaudiAlg/TupleObj.h"
#include "Event/L0MuonCandidate.h"

#include "Event/Particle.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

DECLARE_TOOL_FACTORY( TupleToolL0PtLUT );

using namespace LHCb;
using namespace std;


TupleToolL0PtLUT::TupleToolL0PtLUT( const std::string& type,
    const std::string& name,
    const IInterface* parent )
: TupleToolBase ( type, name , parent ), m_map()
{
  declareInterface<IParticleTupleTool>(this);
  declareProperty("LUT", m_map, "map of LUT positions" );
  declareProperty("LUT_loc", m_LUTlocation, "location of LUT txt file" );
}


StatusCode TupleToolL0PtLUT::initialize() 
{
  StatusCode sc = TupleToolBase::initialize();
  if ( sc.isFailure() ) return sc; 

  // Load the LUT map:
  std::string line;
  ifstream LUT_file (m_LUTlocation.c_str());
  info()<<" location of LUT txt file "<<m_LUTlocation<<endmsg;
  if (LUT_file.is_open())
  {
    while ( LUT_file.good()){   
      getline (LUT_file,line);
      istringstream iss(line);
      string sub[2];
      for (int j=0; j<2; j++){iss >> sub[j];}   
      if (sub[0].compare("")!=0){ m_map[sub[0]] = atof(sub[1].c_str());}
      //info() << "map params: " << sub[0] << " " << atof(sub[1].c_str()) <<  endmsg;
    }   
    info() << "LUT map size = " << m_map.size()<< endmsg;
    LUT_file.close();
  }else{
    info()<<"File not found"<<endmsg;
    return StatusCode::FAILURE;
  }
  

  return sc; 
}

StatusCode TupleToolL0PtLUT::fill( const Particle*
                                   , const Particle* P
                                   , const std::string& head
                                   , Tuples::Tuple& tuple )
{
  //info() << "Fill L0 new Pt!" << endmsg;
  const std::string prefix=fullName(head);
  bool test = true;
  double oldL0Pt= -999.0;
  double newL0Pt= -999.0;  

  //std::string location = LHCb::L0MuonCandidateLocation::Default ;
  std::string location = LHCb::L0MuonCandidateLocation::BCSU;
  

  double proto_sw(0);
  std::vector<double> m1(0),m2(0),m3(0),unmatch(0);  
  double msize(0);
  

  //if((P->proto()==0)||(P->proto()->muonPID()==0)||(P->proto()->muonPID()->muonTrack()==0)){
  if((P->proto()==0)||(P->proto()->muonPID()==0)||(P->proto()->muonPID()->muonTrack()==0)){
    proto_sw = 1 ;
    newL0Pt=-1;
    oldL0Pt=-1;
    msize = -1;
    m1.push_back(-1);
    m2.push_back(-1);
    m3.push_back(-1);
    unmatch.push_back(-1);
    test &= tuple->column(prefix+"_newL0Pt", newL0Pt );
    test &= tuple->column(prefix+"_oldL0Pt", oldL0Pt );
    test &= tuple->column(prefix+"_proto_sw", proto_sw );  
    test &= tuple->farray(prefix+"_m1",m1,"N",200);
    test &= tuple->farray(prefix+"_m2",m2,"N",200);
    test &= tuple->farray(prefix+"_m3",m3,"N",200);
    test &= tuple->farray(prefix+"_unmatch",unmatch,"N",200);
    test &= tuple->column(prefix+"_msize", msize );  
    return StatusCode(test);
  }
  
 



  //info() << "L0MuonCandidateLocation = " << location << endmsg;
  if (exist<LHCb::L0MuonCandidates>(location ) ){ 
    LHCb::L0MuonCandidates* cands = get<LHCb::L0MuonCandidates>( location );
    LHCb::L0MuonCandidates::const_iterator itcand;
    int candNum = 0;
    for ( itcand= cands->begin(); itcand<cands->end();++itcand) {
      candNum++;
      //info() << "There are multiple candidates: " << candNum << endmsg;
      int nsame[3]={0,0,0};
      vector<string> m1m2hitstring(3,"");
      

      //+++++++++++++++++++++++++++++++++++++++++++++++++
      for (int istat=0; istat<3; istat++){
        //info() << "istat = " << istat << endmsg;
        int tile = 0;
        std::vector<MuonTileID> muontiles = (*itcand)->muonTileIDs(istat);
        for (std::vector<LHCb::MuonTileID>::iterator hit=muontiles.begin(); hit<muontiles.end(); ++hit) {
          tile++;
          //info() << "Candidate tile: " << tile << endmsg;
          string hitString = (*hit).toString();
          m1m2hitstring[istat] = hitString;
          //info() << "m1m2hitstring[istat] = " << m1m2hitstring[istat] << endmsg;

          
          const LHCb::Track::LHCbIDContainer ids = P->proto()->muonPID()->muonTrack()->lhcbIDs() ;
          int idit = 0;
          for (LHCb::Track::LHCbIDContainer::const_iterator it = ids.begin(); it != ids.end(); it++){
            idit++;
            //info() << "Muon lhcbID hit: " << idit << endmsg;
            LHCb::LHCbID id = (*it);
            if(id.muonID()!=MuonTileID(0xF0000000)){
              //info() << "id.muonID().toString() = " << id.muonID().toString() << endmsg;
              if (id.muonID().toString().compare(hitString)==0){
                nsame[istat]+=1;
                //info() << "nsame[" << istat << "] = " << nsame[istat] << endmsg;
              }
            }
            else{
              // muon's muonID == 0
            }
          } // lhcbIDs
        } // muon tiles
      }// istat pad 1,2,3
      //++++++++++++++++++++++++++++++++++++++++++++++++++      
      
      
      int nstmatch=0;
      if (nsame[0]>0) nstmatch+=1;
      if (nsame[1]>0) nstmatch+=1;
      if (nsame[2]>0) nstmatch+=1;
      

      m1.push_back(nsame[0]);
      m2.push_back(nsame[1]);
      m3.push_back(nsame[2]);
      
      if(nstmatch>1){ unmatch.push_back(0);
      }
      else{
        unmatch.push_back(1);
      }
      
      


      //info() << "nstmatch = " << nstmatch << endmsg; 
      if (nstmatch>1){
        char m1m2[200]; sprintf(m1m2, "%s%s", m1m2hitstring[0].c_str(), m1m2hitstring[1].c_str());
        //info() << "m1m2 = " << m1m2 << endmsg;
        //info() << "Does m_map have entry equal to m1m2: " << m_map.count(m1m2) << endmsg;
        if (m_map.count(m1m2)==1){
          //info() << "m_map[m1m2] = " << m_map[m1m2] << endmsg;
          if (m_map[m1m2]>newL0Pt){
            newL0Pt = m_map[m1m2];
            oldL0Pt = (*itcand)->pt(); 
            
            //break;//break the L0 candidate loop since we have found one already
            //info() << "newL0Pt = " << newL0Pt << endmsg;
            //info() << "oldL0Pt = " << oldL0Pt << endmsg;
          }
          else{
            //newL0Pt=-10;
          }
        }// has entry in LUT
        else{
          newL0Pt=0.0;// Loss due to table
        }
      }// match "if"
      else{
        //newL0Pt=-1;  // nstmatch <=1
      }
      
      
      
    }//loop L0 candidate




    double flagv(0);
    for (std::vector<double>::const_iterator itv=unmatch.begin() ; itv < unmatch.end(); itv++ ){
      if(*itv==1) flagv++;
    }
    if(flagv==unmatch.size()) msize = 1;    
    
    
    test &= tuple->column(prefix+"_newL0Pt", newL0Pt );
    test &= tuple->column(prefix+"_oldL0Pt", oldL0Pt );
    test &= tuple->column(prefix+"_proto_sw", proto_sw );
    test &= tuple->farray(prefix+"_m1",m1,"N",200);
    test &= tuple->farray(prefix+"_m2",m2,"N",200);
    test &= tuple->farray(prefix+"_m3",m3,"N",200);  
    test &= tuple->farray(prefix+"_unmatch",unmatch,"N",200);
    test &= tuple->column(prefix+"_msize", msize );  
    
    return StatusCode(test);
    
    
    
    

  }// if L0 muon exist
  else{ 
    //info() << "No L0 trigger debug!" << endmsg ;
    newL0Pt=-2; // no L0 location
    oldL0Pt=-2; // no L0 location
    m1.push_back(-2);
    m2.push_back(-2);
    m3.push_back(-2);
    unmatch.push_back(-2);
    msize = -2;
    test &= tuple->column(prefix+"_newL0Pt", newL0Pt );
    test &= tuple->column(prefix+"_oldL0Pt", oldL0Pt );
    test &= tuple->column(prefix+"_proto_sw", proto_sw );
    test &= tuple->farray(prefix+"_m1",m1,"N",200);
    test &= tuple->farray(prefix+"_m2",m2,"N",200);
    test &= tuple->farray(prefix+"_m3",m3,"N",200);  
    test &= tuple->farray(prefix+"_unmatch",unmatch,"N",200);
    test &= tuple->column(prefix+"_msize", msize );
    return StatusCode(test);
  }



  

}

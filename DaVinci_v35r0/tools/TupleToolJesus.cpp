// $Id: TupleToolTutorial.cpp,v 1.1 2009-06-11 16:22:29 rlambert Exp $
// Include files

// from Gaudi
#include "GaudiKernel/ToolFactory.h"

// local
#include "TupleToolJesus.h"
#include <Kernel/GetIDVAlgorithm.h>
#include <Kernel/IDistanceCalculator.h>
#include "GaudiAlg/Tuple.h"
#include "GaudiAlg/TupleObj.h"
#include "Kernel/IParticleTransporter.h"

//#include "Phys/LoKiFitters/LifeTimeFitter.h"

#include "Event/Particle.h"
//-----------------------------------------------------------------------------
// Implementation file for class : TupleToolJesus
//
// 2015-02 
//-----------------------------------------------------------------------------

// Declaration of the Tool Factory
// actually acts as a using namespace TupleTool
DECLARE_TOOL_FACTORY( TupleToolJesus )
//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TupleToolJesus::TupleToolJesus( const std::string& type,
                                         const std::string& name,
                                         const IInterface* parent )
: TupleToolBase ( type, name , parent ), taum(1776.82), step(1e-5), m_dva(0), m_dist(0), m_fit(0), m_combiner(0), 
m_transporterName ("ParticleTransporter:PUBLIC"), m_transporter()
{
   declareInterface<IParticleTupleTool>(this);
   declareProperty( "Transporter", m_transporterName );
   //declare properties here!
}

StatusCode TupleToolJesus::initialize()
{
   const StatusCode sc = TupleToolBase::initialize();
   if ( sc.isFailure() ) return sc;

   m_dva = Gaudi::Utils::getIDVAlgorithm ( contextSvc(), this ) ;
   if (!m_dva) std::cout<<"DINOSAUR M_DVA"<<std::endl;
   if (!m_dva) return Error("Couldn't get parent DVAlgorithm");

   m_dist = m_dva->distanceCalculator();
   if (!m_dist) std::cout<<"DINOSAUR M_DIST"<<std::endl;
   if(!m_dist) return Error("unable to retrieve the IDistanceCalculator tool");

   m_fit = m_dva->lifetimeFitter();
   if (!m_fit) std::cout<<"DINOSAUR M_fit"<<std::endl;
   if( !m_fit ) return Error("Unable to retrieve the ILifetimeFitter tool");
   
   m_combiner  = m_dva->particleCombiner();
   if (!m_dist) std::cout<<"DINOSAUR M_combiner"<<std::endl;
   if( !m_combiner ) return Error("Unable to retrieve the particleCombiner tool");

   m_transporter = tool<IParticleTransporter>(m_transporterName, this);
   return sc;
}

//=============================================================================

StatusCode TupleToolJesus::fill( const LHCb::Particle* mother 
      , const LHCb::Particle* P
      , const std::string& head
      , Tuples::Tuple& tuple )
{

   //the fill method is called once per input particle
   //fill some information about the particle here!
   bool test(true);
   int isJesusOK(0);


   //this tuple tool is called for each B 
   if(P->particleID().abspid() == 511)
   {
      LHCb::Particle::ConstVector source;
      std::string pclename;

      LHCb::Particle mu_tau;
      LHCb::Particle mu;
      LHCb::Particle Kst_ex;
      LHCb::Particle B;
      int id;
      //Get Kst+1410 and the second muon from the B daughter
      source = P->daughtersVector();
      LHCb::VertexBase BPV(*(m_dva->bestVertex (P)));
      LHCb::VertexBase BSV;
      B = *P;
      for(LHCb::Particle::ConstVector::const_iterator isource = source.begin(); isource != source.end(); isource++)
      {
         id = (*isource)->particleID().pid();
         if(abs(id) == 13) mu_tau = *(*isource);
         if(abs(id) == 100323)
         {
             Kst_ex = *(*isource);
             BSV = *((*isource)->endVertex());
         }
      }

      if(Kst_ex.particleID().abspid() != 100323)  return Error("Unable to retrieve Kst_ex", StatusCode::FAILURE);
      if(mu_tau.particleID().abspid() != 13)  return Error("Unable to retrieve mu_tau", StatusCode::FAILURE);

      //Get Kst the first  muon from Kst+1410 daughter
      source = Kst_ex.daughtersVector();
      LHCb::Particle Kst;
      for(LHCb::Particle::ConstVector::const_iterator isource = source.begin(); isource != source.end(); isource++)
      {
         id = (*isource)->particleID().pid();
         if(abs(id) == 13) mu = *(*isource);
         if(abs(id) == 313) Kst = *(*isource);
      }

      if(Kst.particleID().abspid() != 313)  return Error("Unable to retrieve Kst", StatusCode::FAILURE);
      if(mu.particleID().abspid() != 13)  return Error("Unable to retrieve mu_tau", StatusCode::FAILURE);

      source = Kst.daughtersVector();
      LHCb::Particle K;
      LHCb::Particle pi;
      for(LHCb::Particle::ConstVector::const_iterator isource = source.begin(); isource != source.end(); isource++)
      {
         id = (*isource)->particleID().pid();
         if(abs(id) == 211) pi = *(*isource);
         if(abs(id) == 321) K = *(*isource);
      }
      if(pi.particleID().abspid() != 211)  return Error("Unable to retrieve pi", StatusCode::FAILURE);
      if(K.particleID().abspid() != 321)  return Error("Unable to retrieve K", StatusCode::FAILURE);

      //set mu and mu tau properly

      LHCb::ParticleID tauID;
      if((mu_tau.particleID()).pid() == 13)   tauID.setPid(15);
      if((mu_tau.particleID()).pid() == -13)   tauID.setPid(-15);
      
      //Reconstruct the tau Decay vertex
      LHCb::Vertex tauSV;
      tauSV.setPosition(getTauDecayVtx(BPV.position(), BSV.position(), Kst_ex.momentum(), mu_tau.referencePoint(), mu_tau.momentum()));
      tauSV.setCovMatrix(getTauDecayVtxCov(BPV.position(), BSV.position(), Kst_ex.momentum(), mu_tau.referencePoint(), mu_tau.momentum(),
             BPV.covMatrix(), BSV.covMatrix(), Kst_ex.momCovMatrix(), mu_tau.covMatrix()));

      //make the tau itself
      LHCb::Particle tau;      
      tau.setParticleID(tauID);
      tau.setMomentum(getTauP(BPV.position(), BSV.position(), Kst_ex.momentum(), tauSV.position()));
      tau.setEndVertex(&tauSV);
      tau.setReferencePoint(BSV.position());
      tau.setPosCovMatrix(BSV.covMatrix());
      tau.setMomCovMatrix(getTauPCov(BPV.position(), BSV.position(), Kst_ex.momentum(), mu_tau.referencePoint(),
       mu_tau.momentum(), BPV.covMatrix(), BSV.covMatrix(), Kst_ex.momCovMatrix(), mu_tau.covMatrix()));
      tau.setPosMomCovMatrix(getTauPBSVCov(BPV.position(), BSV.position(), Kst_ex.momentum(), mu_tau.referencePoint(),
       mu_tau.momentum(), BSV.covMatrix()));
      tau.addToDaughters(&mu_tau);

      //make a corrected B0 with the right momentum information (ie including the neutrini)

      
      LHCb::ParticleID BID;
      if((K.particleID()).pid() == 321) BID.setPid(511);
      if((K.particleID()).pid() == -321) BID.setPid(-511);

      LHCb::Particle::ConstVector Bdaughters;
      Bdaughters.push_back(&mu);
      Bdaughters.push_back(&K);
      Bdaughters.push_back(&tau);
      Bdaughters.push_back(&pi);

      LHCb::Particle Bcor;
      LHCb::Vertex BSVcor;
      m_combiner->combine(Bdaughters, Bcor, BSVcor); 

      //Compute a couple of interesting things

      //std::cout<<"IS THERE A  VERTEX?"<<(tau.endVertex()->position()).x()<<" "<<(tau.endVertex()->position()).y()<<" "<<(tau.endVertex()->position()).z()<<std::endl;
      double holyMass(getHolyMass(BPV.position(), BSV.position(), Kst_ex.momentum(),  mu_tau.referencePoint(), mu_tau.momentum()));
      double holyMassErr(getHolyMassErr(BPV.position(), BSV.position(), Kst_ex.momentum(), mu_tau.referencePoint(),
       mu_tau.momentum(), BPV.covMatrix(), BSV.covMatrix(), Kst_ex.momCovMatrix(), mu_tau.covMatrix()));

      double corMass(getCorMass(BPV.position(), BSV.position(), Kst_ex.momentum()+mu_tau.momentum()));
      double corMassErr(getCorMassErr(BPV.position(), BSV.position(), P->momentum(),
       BPV.covMatrix(), BSV.covMatrix(), P->momCovMatrix()));

      //compute length of fly and decay time of tau

      double tauL;
      double tauLchi2;
      test &= m_dist->distance(&BSV, &tauSV, tauL, tauLchi2);
      if(!test)
      {
          std::cout<<"DINOSAUR 0"<<std::endl;
          test = true;
          isJesusOK = 1;
      }

      double tauTau;
      double tauTauErr;
      double tauTauChi2;

      
      LHCb::Particle transTau;
      test &= m_transporter->transport(&tau, (tauSV.position()).z(), transTau);
      if(!test)
      {
          std::cout<<"DINOSAUR 1"<<std::endl;
          test = true;
          isJesusOK = 1;
      }

      test &= m_fit->fit(BSV, transTau, tauTau, tauTauErr, tauTauChi2);
      if(!test)
      {
          std::cout<<"DINOSAUR 2"<<std::endl;
          test = true;
          isJesusOK = 2;
      }

      double tauTau2;
      tauTau2 = (tauL*taum/(tau.momentum()).P())*1e6/299792158.;

      //compute length of fly and decay time of B

      double BL;
      double BLchi2;
      test &= m_dist->distance(&BPV, &BSV, BL, BLchi2);
      if(!test)
      {
          std::cout<<"DINOSAUR 3"<<std::endl;
          test = true;
          isJesusOK = 3;
      }

      double BTau;
      double BTauErr;
      double BTauChi2;

      test &= m_fit->fit(BPV, Bcor, BTau, BTauErr, BTauChi2);
      if(!test)
      {
          std::cout<<"DINOSAUR 4"<<std::endl;
          test = true;
          isJesusOK = 4;
      }


      //compute the DIRA of the tau
      
      Gaudi::XYZVector p3;
      Gaudi::XYZVector tauLVec(tauSV.position()-BSV.position());
      p3.SetXYZ((tau.momentum()).px(),(tau.momentum()).py(),(tau.momentum()).pz());
      double DIRA(p3.Dot(tauLVec)/sqrt(p3.Mag2() * tauLVec.Mag2()));

      //angle between TauP and BP
      
      Gaudi::XYZVector BLVec(BSV.position() - BPV.position());
      double TauLoF_dot_BLoF(BLVec.Dot(tauLVec)/sqrt(BLVec.Mag2() * tauLVec.Mag2()));


      //Fill the branches relative to tau

      test &= tuple->column(head + "_corMass", corMass);
      test &= tuple->column(head + "_corMassERR", corMassErr);
      test &= tuple->column(head + "_holyMass", holyMass);
      test &= tuple->column(head + "_holyMassERR", holyMassErr);
      test &= tuple->column("Tau_ENDVERTEX_X", (tauSV.position()).x());
      test &= tuple->column("Tau_ENDVERTEX_Y", (tauSV.position()).y());
      test &= tuple->column("Tau_ENDVERTEX_Z", (tauSV.position()).z());
      test &= tuple->column("Tau_ENDVERTEX_XERR", sqrt((tauSV.covMatrix())(0,0)));
      test &= tuple->column("Tau_ENDVERTEX_YERR", sqrt((tauSV.covMatrix())(1,1)));
      test &= tuple->column("Tau_ENDVERTEX_ZERR", sqrt((tauSV.covMatrix())(2,2)));
      test &= tuple->matrix("Tau_ENDVERTEX_COV_", tauSV.covMatrix());
      test &= tuple->column("Tau_P", (tau.momentum()).P());
      test &= tuple->column("Tau_PT", (tau.momentum()).Pt());
      test &= tuple->column("Tau_PX", (tau.momentum()).px());
      test &= tuple->column("Tau_PY", (tau.momentum()).py());
      test &= tuple->column("Tau_PZ", (tau.momentum()).pz());
      test &= tuple->column("Tau_PE", (tau.momentum()).energy());
      test &= tuple->matrix("Tau_P_COV_", tau.momCovMatrix());
      test &= tuple->matrix("Tau_PosMom_COV_", tau.covMatrix());
      test &= tuple->column("Tau_LoF", tauL);
      test &= tuple->column("Tau_LoFCHI2", tauLchi2);
      test &= tuple->column("Tau_Tau_myWay", tauTau2);
      test &= tuple->column("Tau_TAU", tauTau);
      test &= tuple->column("Tau_TAUERR", tauTauErr);
      test &= tuple->column("Tau_TAUCHI2", tauTauChi2);
      test &= tuple->column("Tau_DIRA", DIRA);
      test &= tuple->column("TauLoF_dot_BLoF", TauLoF_dot_BLoF);


      if(!test) std::cout<<"DINOSAUR 5"<<std::endl;

      test &= tuple->column("Jesus_B0_LoF", BL);
      test &= tuple->column("Jesus_B0_LoFCHI2", BLchi2);
      test &= tuple->column("Jesus_B0_TAU", BTau);
      test &= tuple->column("Jesus_B0_TAUERR", BTauErr);
      test &= tuple->column("Jesus_B0_TAUCHI2", BTauChi2);
      test &= tuple->column("Jesus_B0_P", (Bcor.momentum()).P());
      test &= tuple->column("Jesus_B0_PX", (Bcor.momentum()).px());
      test &= tuple->column("Jesus_B0_PY", (Bcor.momentum()).py());
      test &= tuple->column("Jesus_B0_PZ", (Bcor.momentum()).pz());
      test &= tuple->column("Jesus_B0_PE", (Bcor.momentum()).energy());
      test &= tuple->column("Jesus_B0_PT", (Bcor.momentum()).Pt());
      test &= tuple->column("B0_PVSVRho", getRhoDist(BPV.position(), BSV.position()));

      if(!test) std::cout<<"DINOSAUR 6"<<std::endl;

      //Now compute some impact parameters

      double IP;
      double IPchi2;


      test &= m_dist->distance(&tau, &BPV, IP, IPchi2);
      test &= tuple->column("Jesus_Tau_IP_wrt_PV", IP);
      test &= tuple->column("Jesus_Tau_IPCHI2_wrt_PV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 7"<<std::endl;

      test &= m_dist->distance(&tau, &BSV, IP, IPchi2);
      test &= tuple->column("Jesus_Tau_IP_wrt_BSV", IP);
      test &= tuple->column("Jesus_Tau_IPCHI2_wrt_BSV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 8"<<std::endl;

      test &= m_dist->distance(&tau, &tauSV, IP, IPchi2);
      test &= tuple->column("Jesus_Tau_IP_wrt_tauSV", IP);
      test &= tuple->column("Jesus_Tau_IPCHI2_wrt_tauSV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 9"<<std::endl;

      test &= m_dist->distance(&K, &BPV, IP, IPchi2);
      test &= tuple->column("Jesus_K_IP_wrt_PV", IP);
      test &= tuple->column("Jesus_K_IPCHI2_wrt_PV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 10"<<std::endl;

      test &= m_dist->distance(&K, &BSV, IP, IPchi2);
      test &= tuple->column("Jesus_K_IP_wrt_BSV", IP);
      test &= tuple->column("Jesus_K_IPCHI2_wrt_BSV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 11"<<std::endl;

      test &= m_dist->distance(&K, &tauSV, IP, IPchi2);
      test &= tuple->column("Jesus_K_IP_wrt_tauSV", IP);
      test &= tuple->column("Jesus_K_IPCHI2_wrt_tauSV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 12"<<std::endl;

      test &= m_dist->distance(&pi, &BPV, IP, IPchi2);
      test &= tuple->column("Jesus_Pi_IP_wrt_PV", IP);
      test &= tuple->column("Jesus_Pi_IPCHI2_wrt_PV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 13"<<std::endl;

      test &= m_dist->distance(&pi, &BSV, IP, IPchi2);
      test &= tuple->column("Jesus_Pi_IP_wrt_BSV", IP);
      test &= tuple->column("Jesus_Pi_IPCHI2_wrt_BSV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 14"<<std::endl;

      test &= m_dist->distance(&pi, &tauSV, IP, IPchi2);
      test &= tuple->column("Jesus_Pi_IP_wrt_tauSV", IP);
      test &= tuple->column("Jesus_Pi_IPCHI2_wrt_tauSV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 15"<<std::endl;
      
      test &= m_dist->distance(&mu, &BPV, IP, IPchi2);
      test &= tuple->column("Jesus_mu_IP_wrt_PV", IP);
      test &= tuple->column("Jesus_mu_IPCHI2_wrt_PV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 16"<<std::endl;

      test &= m_dist->distance(&mu, &BSV, IP, IPchi2);
      test &= tuple->column("Jesus_mu_IP_wrt_BSV", IP);
      test &= tuple->column("Jesus_mu_IPCHI2_wrt_BSV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 17"<<std::endl;

      test &= m_dist->distance(&mu, &tauSV, IP, IPchi2);
      test &= tuple->column("Jesus_mu_IP_wrt_tauSV", IP);
      test &= tuple->column("Jesus_mu_IPCHI2_wrt_tauSV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 18"<<std::endl;

      test &= m_dist->distance(&mu_tau, &BPV, IP, IPchi2);
      test &= tuple->column("Jesus_mu_Tau_IP_wrt_PV", IP);
      test &= tuple->column("Jesus_mu_Tau_IPCHI2_wrt_PV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 19"<<std::endl;

      test &= m_dist->distance(&mu_tau, &BSV, IP, IPchi2);
      test &= tuple->column("Jesus_mu_Tau_IP_wrt_BSV", IP);
      test &= tuple->column("Jesus_mu_Tau_IPCHI2_wrt_BSV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 20"<<std::endl;

      test &= m_dist->distance(&mu_tau, &tauSV, IP, IPchi2);
      test &= tuple->column("Jesus_mu_Tau_IP_wrt_tauSV", IP);
      test &= tuple->column("Jesus_mu_Tau_IPCHI2_wrt_tauSV", IPchi2);
      if(!test) std::cout<<"DINOSAUR 21"<<std::endl;

      test &= m_dist->distance(&mu_tau, &mu, IP, IPchi2);
      test &= tuple->column("Jesus_DOCA_mu_mu_Tau", IP);
      test &= tuple->column("Jesus_DOCACHI2_mu_mu_Tau", IPchi2);
      if(!test) std::cout<<"DINOSAUR 22"<<std::endl;

      test &= m_dist->distance(&mu_tau, &pi, IP, IPchi2);
      test &= tuple->column("Jesus_DOCA_mu_Tau_Pi", IP);
      test &= tuple->column("Jesus_DOCACHI2_mu_Tau_Pi", IPchi2);
      if(!test) std::cout<<"DINOSAUR 23"<<std::endl;

      test &= m_dist->distance(&mu, &pi, IP, IPchi2);
      test &= tuple->column("Jesus_DOCA_mu_Pi", IP);
      test &= tuple->column("Jesus_DOCACHI2_mu_Pi", IPchi2);
      if(!test) std::cout<<"DINOSAUR 24"<<std::endl;

      test &= m_dist->distance(&mu_tau, &K, IP, IPchi2);
      test &= tuple->column("Jesus_DOCA_mu_Tau_K", IP);
      test &= tuple->column("Jesus_DOCACHI2_mu_Tau_K", IPchi2);
      if(!test) std::cout<<"DINOSAUR 25"<<std::endl;

      test &= m_dist->distance(&mu, &K, IP, IPchi2);
      test &= tuple->column("Jesus_DOCA_mu_K", IP);
      test &= tuple->column("Jesus_DOCACHI2_mu_K", IPchi2);
      if(!test) std::cout<<"DINOSAUR 26"<<std::endl;

      test &= m_dist->distance(&K, &pi, IP, IPchi2);
      test &= tuple->column("Jesus_DOCA_K_pi", IP);
      test &= tuple->column("Jesus_DOCACHI2_K_pi", IPchi2);
      if(!test)
      {
         test = true;
         isJesusOK = 27;
          std::cout<<"DINOSAUR 27"<<std::endl;
      }
      test &= tuple->column("isJesusOK", isJesusOK);

      //some tests
      
      /*
      std::cout<<"Position BSV / endvertex of Bcor / refpoint of Bcor"<<std::endl;
      std::cout<<BSV.position().x()<<" "<<(*(Bcor.endVertex())).position().x()<<" "<<Bcor.referencePoint().x()<<std::endl;
      std::cout<<BSV.position().y()<<" "<<(*(Bcor.endVertex())).position().y()<<" "<<Bcor.referencePoint().y()<<std::endl;
      std::cout<<BSV.position().z()<<" "<<(*(Bcor.endVertex())).position().z()<<" "<<Bcor.referencePoint().z()<<std::endl;
      std::cout<<"momentum Bcor / sum momentum"<<std::endl;
      std::cout<<Bcor.momentum().px()<<" "<<Kst_ex.momentum().px()+tau.momentum().px()<<std::endl;
      std::cout<<Bcor.momentum().py()<<" "<<Kst_ex.momentum().py()+tau.momentum().py()<<std::endl;
      std::cout<<Bcor.momentum().pz()<<" "<<Kst_ex.momentum().pz()+tau.momentum().pz()<<std::endl;
      std::cout<<"BSV err / edvertex Bcor err"<<std::endl;
      std::cout<<BSV.covMatrix()(0,0)<<" "<<Bcor.posCovMatrix()(0,0)<<std::endl;
      std::cout<<BSV.covMatrix()(1,1)<<" "<<Bcor.posCovMatrix()(1,1)<<std::endl;
      std::cout<<BSV.covMatrix()(2,2)<<" "<<Bcor.posCovMatrix()(2,2)<<std::endl;
      */

   }

   if(!P)
   {
      std::cout<<"DINOSAUR FINAL"<<std::endl;
      return StatusCode::FAILURE;
   }

   return StatusCode(test);
}


double getRhoDist(Gaudi::XYZPoint A, Gaudi::XYZPoint B)
{
   Gaudi::XYZVector vec(B-A);
   return sqrt(vec.x()*vec.x()+vec.y()*vec.y());
}

Gaudi::XYZPoint TupleToolJesus::getTauDecayVtx(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP)
{
   Gaudi::XYZVector tmp; //just here to stock temporary stuff
   Gaudi::XYZVector LB; //NORMALISED vector, line of flight of B  
   LB = BSV-BPV;
   LB = LB.Unit();

   Gaudi::XYZVector tauPT3;
   Gaudi::XYZVector XP3;
   XP3.SetXYZ(XP.px(), XP.py(), XP.pz());
   tauPT3 =  (LB.Dot(XP3))*LB - XP3;

   double a,b,c,d; //4 coords of plan equation containing tauPT and LB
   tmp = LB.Cross(tauPT3.Unit());
   tmp = tmp.Unit();
   a = tmp.x();
   b = tmp.y();
   c = tmp.z();
   d = -a*BSV.x()-b*BSV.y()-c*BSV.z();

   //now will comput intersection of that plan and the muon LoF
   double lambda; //lambda of the LoF equation
   Gaudi::XYZVector muP3;
   muP3.SetXYZ(muP.px(), muP.py(), muP.pz());
   lambda = (-a*muPos.x()-b*muPos.y()-c*muPos.z()-d) / (a*muP3.x()+b*muP3.y()+c*muP3.z());
   tmp =  muPos +( lambda * muP3); //position of the tau vertex, just need to convert it into a Point

   Gaudi::XYZPoint ret;
   ret.SetXYZ(tmp.x(), tmp.y(), tmp.z());
   return ret;
}

Gaudi::LorentzVector TupleToolJesus::getTauP(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP)
{
   return getTauP(BPV, BSV, XP, getTauDecayVtx( BPV,  BSV, XP,  muPos, muP));
}

Gaudi::LorentzVector TupleToolJesus::getTauP(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint tauSV)
{
   Gaudi::XYZVector LB; //NORMALISED vector, line of flight of B  
   LB = BSV-BPV;
   LB = LB.Unit();

   Gaudi::XYZVector tauPT3;
   Gaudi::XYZVector XP3;
   XP3.SetXYZ(XP.px(), XP.py(), XP.pz());
   tauPT3 =  (LB.Dot(XP3))*LB - XP3;

   Gaudi::XYZVector tmp(tauSV-BSV);

   tmp = tmp.Unit();
   double norm(tauPT3.Mag2() / (tmp.Dot(tauPT3)));
   tmp = norm*tmp; //now tmp is set to the tau 3 mmtm

   double Etau(sqrt( taum*taum+tmp.Mag2() ));

   Gaudi::LorentzVector ret;
   ret.SetPxPyPzE(tmp.x(), tmp.y(), tmp.z(), Etau);
   return ret;
}

double TupleToolJesus::getHolyMass(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP)
{
      return (getTauP( BPV, BSV, XP, muPos, muP)+XP).M();
}

double TupleToolJesus::getCorMass(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV,  Gaudi::LorentzVector visP)
{
   Gaudi::XYZVector LB; //NORMALISED vector, line of flight of B  
   LB = BSV-BPV;
   LB = LB.Unit();

   Gaudi::XYZVector visP3;
   visP3.SetXYZ(visP.px(), visP.py(), visP.pz());
   Gaudi::XYZVector missPT;
   missPT =  (LB.Dot(visP3))*LB - visP3;

   return sqrt(visP.M2() + missPT.Mag2())+ sqrt(missPT.Mag2());
}

Gaudi::SymMatrix3x3 TupleToolJesus::getTauDecayVtxCov(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos,
   Gaudi::LorentzVector muP,Gaudi::SymMatrix3x3 covBPV, Gaudi::SymMatrix3x3 covBSV, Gaudi::SymMatrix4x4 covXP, Gaudi::SymMatrix7x7 covMuT)
{   
   double dVkdBPVi[3][3];
   double dVkdBSVi[3][3];
   double dVkdXPi[3][4];
   double dVkdmuTi[3][7];

   Gaudi::XYZPoint vtxup;
   Gaudi::XYZPoint vtxdown;
   Gaudi::XYZVector stock;
//   double sigma;

   for(int i(0); i<3; ++i)
   {
//      sigma = sqrt(covBPV(i,i));
//      if(sigma > step)
      {
         setCoord(BPV, i, getCoord(BPV, i) + step);
         vtxup = getTauDecayVtx(BPV, BSV, XP, muPos, muP);
         setCoord(BPV, i, getCoord(BPV, i) - 2*step);
         vtxdown = getTauDecayVtx(BPV, BSV, XP, muPos, muP);
         setCoord(BPV, i, getCoord(BPV, i) + step);
         stock = (1./(2*step)) * (vtxup-vtxdown);
      }
//      else stock.SetXYZ(0,0,0);


      for(int k(0); k<3; ++k)
      {
         dVkdBPVi[k][i] = getCoord(stock, k);
      }

//      sigma = sqrt(covBSV(i,i));
//      if(sigma > step)
      {
         setCoord(BSV, i, getCoord(BSV, i) + step);
         vtxup = getTauDecayVtx(BPV, BSV, XP, muPos, muP);
         setCoord(BSV, i, getCoord(BSV, i) - 2*step);
         vtxdown = getTauDecayVtx(BPV, BSV, XP, muPos, muP);
         setCoord(BSV, i, getCoord(BSV, i) + step);

         stock = (1./(2*step)) * (vtxup-vtxdown);
      }
//      else stock.SetXYZ(0,0,0);

      for(int k(0); k<3; ++k)
      {
         dVkdBSVi[k][i] = getCoord(stock, k);
      }
   }

   for(int i(0); i<4; ++i)
   {
//      sigma = sqrt(covXP(i,i));
//      if(sigma > step)
      {
         setCoord(XP,i, getCoord(XP,i) + step);
         vtxup = getTauDecayVtx(BPV, BSV, XP, muPos, muP);
         setCoord(XP,i, getCoord(XP,i) - 2*step);
         vtxdown = getTauDecayVtx(BPV, BSV, XP, muPos, muP);
         setCoord(XP,i, getCoord(XP,i) + step);

         stock = (1./(2*step)) * (vtxup-vtxdown);
      }
//      else stock.SetXYZ(0,0,0);

      for(int k(0); k<3; ++k)
      {
         dVkdXPi[k][i] = getCoord(stock, k);
      }
   }

   for(int i(0); i<7; ++i)
   {
//      sigma = sqrt(covMuT(i,i));
//      if(sigma > step)
      {
         setCoord(muPos, muP, i, getCoord(muPos, muP,i) + step);
         vtxup = getTauDecayVtx(BPV, BSV, XP, muPos, muP);
         setCoord(muPos, muP, i, getCoord(muPos, muP,i) - 2*step);
         vtxdown = getTauDecayVtx(BPV, BSV, XP, muPos, muP);
         setCoord(muPos, muP, i, getCoord(muPos, muP,i) + step);

         stock = (1./(2*step)) * (vtxup-vtxdown);
      }
//      else stock.SetXYZ(0,0,0);

      for(int k(0); k<3; ++k)
      {
         dVkdmuTi[k][i] = getCoord(stock, k);
      }
   }

   Gaudi::SymMatrix3x3 covRet;

   double covRetkl(0);
   for(int k(0); k<3; ++k)
   {
      for(int l(k); l<3; ++l)
      {
         for(int i(0); i<3; ++i)
         {
            for(int j(0); j<3; ++j)
            {
               covRetkl += dVkdBSVi[k][i]*dVkdBSVi[l][j]*covBSV(i,j);
               covRetkl += dVkdBPVi[k][i]*dVkdBPVi[l][j]*covBPV(i,j);
            }
         }
         for(int i(0); i<4; ++i)
         {
            for(int j(0); j<4; ++j)
            {
               covRetkl += dVkdXPi[k][i]*dVkdXPi[l][j]*covXP(i,j);
            }
         }
         for(int i(0); i<7; ++i)
         {
            for(int j(0); j<7; ++j)
            {
               covRetkl += dVkdmuTi[k][i]*dVkdmuTi[l][j]*covMuT(i,j);
            }
         }

         covRet(k,l) = covRetkl;
         covRetkl = 0;
      }
   }
   return covRet;
}

double TupleToolJesus::getHolyMassErr(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos,
   Gaudi::LorentzVector muP, Gaudi::SymMatrix3x3 covBPV, Gaudi::SymMatrix3x3 covBSV, Gaudi::SymMatrix4x4 covXP, Gaudi::SymMatrix7x7 covV)
{
   double deltaBSV[3] = {0,0,0};
   double deltaBPV[3] = {0,0,0};
   double deltaXP[4] = {0,0,0,0};
   double deltaV[7] = {0,0,0,0,0,0,0};

   double mPlus, mMinus;
//   double sigma(0);

   for(int i(0); i<3; ++i)
   {
  //    sigma = sqrt(covBPV(i,i));
  //    if(sigma > step)
      {
         setCoord(BPV, i, getCoord(BPV, i) + step);
         mPlus = getHolyMass(BPV, BSV, XP, muPos, muP);
         setCoord(BPV, i, getCoord(BPV, i) -2*step);
         mMinus = getHolyMass(BPV, BSV, XP, muPos, muP);
         deltaBPV[i] = (mPlus-mMinus)/(2*step);
      }

    //  sigma = sqrt(covBSV(i,i));
//      if(sigma > step)
      {
         setCoord(BSV, i, getCoord(BSV, i) + step);
         mPlus = getHolyMass(BPV, BSV, XP, muPos, muP);
         setCoord(BSV, i, getCoord(BSV, i) - 2*step);
         mMinus = getHolyMass(BPV, BSV, XP, muPos, muP);
         setCoord(BSV, i, getCoord(BSV, i) + step);
         deltaBSV[i] = (mPlus-mMinus)/(2*step);
      }
   }

   for(int i(0); i<4; ++i)
   {
  //    sigma = sqrt(covXP(i,i));
  //    if(sigma > step)
      {
         setCoord(XP, i, getCoord(XP,i)+step);
         mPlus = getHolyMass(BPV, BSV, XP, muPos, muP);
         setCoord(XP, i, getCoord(XP,i)-2*step);
         mMinus = getHolyMass(BPV, BSV, XP, muPos, muP);
         setCoord(XP, i, getCoord(XP,i)+step);
         deltaXP[i] = (mPlus-mMinus)/(2*step);
      }
   }

   for(int i(0); i<7; ++i)
   {
//      sigma = sqrt(covV(i,i));
//      if(sigma > step)
      {
         setCoord(muPos, muP, i, getCoord(muPos, muP,i) + step);
         mPlus = getHolyMass(BPV, BSV, XP, muPos, muP);
         setCoord(muPos, muP, i, getCoord(muPos, muP,i) - 2*step);
         mMinus = getHolyMass(BPV, BSV, XP, muPos, muP);
         setCoord(muPos, muP, i, getCoord(muPos, muP,i) + step);
         deltaV[i] = (mPlus-mMinus)/(2*step);
      }
   }

   double err(0);

   for(int i(0); i<3;++i)
   {
      for(int j(0); j<3; ++j)
      {
         err += deltaBPV[i]*deltaBPV[j]*covBPV(i,j);
         err += deltaBSV[i]*deltaBSV[j]*covBSV(i,j);
      }
   }

   for(int i(0); i<4;++i)
   {
      for(int j(0); j<4; ++j)
      {
         err += deltaXP[i]*deltaXP[j]*covXP(i,j);
      }
   }

   for(int i(0); i<7;++i)
   {
      for(int j(0); j<7; ++j)
      {
         err += deltaV[i]*deltaV[j]*covV(i,j);
      }
   }

   return sqrt(err);
}

Gaudi::SymMatrix4x4 TupleToolJesus::getTauPCov(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP,
 Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP, Gaudi::SymMatrix3x3 covBPV, Gaudi::SymMatrix3x3 covBSV, Gaudi::SymMatrix4x4 covXP, Gaudi::SymMatrix7x7 covMuT)   
{   
   double dPkdBPVi[4][3];
   double dPkdBSVi[4][3];
   double dPkdXPi[4][4];
   double dPkdmuTi[4][7];

   Gaudi::LorentzVector Pup;
   Gaudi::LorentzVector Pdown;
   Gaudi::LorentzVector dPdxi;
//   double sigma;

   for(int i(0); i<3; ++i)
   {
  //    sigma = sqrt(covBPV(i,i));
   //   if(sigma > step)
      {

         setCoord(BPV, i, getCoord(BPV, i) + step);
         Pup = getTauP(BPV, BSV, XP, muPos, muP);
         setCoord(BPV, i, getCoord(BPV, i) - 2*step);
         Pdown = getTauP(BPV, BSV, XP, muPos, muP);
         setCoord(BPV, i, getCoord(BPV, i) + step);
         dPdxi = (1./(2*step)) * (Pup-Pdown);
      }
   //   else dPdxi.SetPxPyPzE(0,0,0,0);

      for(int k(0); k<4; ++k)
      {
         dPkdBPVi[k][i] = getCoord(dPdxi, k);
      }


    //  sigma = sqrt(covBSV(i,i));
     // if(sigma > step)
      {

         setCoord(BSV, i, getCoord(BSV, i) + step);
         Pup = getTauP(BPV, BSV, XP, muPos, muP);
         setCoord(BSV, i, getCoord(BSV, i) - 2*step);
         Pdown = getTauP(BPV, BSV, XP, muPos, muP);
         setCoord(BSV, i, getCoord(BSV, i) + step);
         dPdxi = (1./(2.*step)) * (Pup-Pdown);
      }
     // else dPdxi.SetPxPyPzE(0,0,0,0);

      for(int k(0); k<4; ++k)
      {
         dPkdBSVi[k][i] = getCoord(dPdxi, k);
      }
   }

   for(int i(0); i<4; ++i)
   {
   //   sigma = sqrt(covXP(i,i));
   //   if(sigma > step)
      {
         setCoord(XP,i, getCoord(XP,i) + step);
         Pup = getTauP(BPV, BSV, XP, muPos, muP);
         setCoord(XP,i, getCoord(XP,i) - 2*step);
         Pdown = getTauP(BPV, BSV, XP, muPos, muP);
         setCoord(XP,i, getCoord(XP,i) + step);

         dPdxi = (1./(2.*step)) * (Pup-Pdown);
      }
    //  else dPdxi.SetPxPyPzE(0,0,0,0);

      for(int k(0); k<4; ++k)
      {
         dPkdXPi[k][i] = getCoord(dPdxi, k);
      }
   }

   for(int i(0); i<7; ++i)
   {
   //   sigma = sqrt(covMuT(i,i));
   //   if(sigma > step)
      {
         setCoord(muPos, muP, i, getCoord(muPos, muP,i) + step);
         Pup = getTauP(BPV, BSV, XP, muPos, muP);
         setCoord(muPos, muP, i, getCoord(muPos, muP,i) - 2*step);
         Pdown = getTauP(BPV, BSV, XP, muPos, muP);
         setCoord(muPos, muP, i, getCoord(muPos, muP,i) + step);

         dPdxi = (1./(2*step)) * (Pup-Pdown);
      }
  //    else dPdxi.SetPxPyPzE(0,0,0,0);

      for(int k(0); k<4; ++k)
      {
         dPkdmuTi[k][i] = getCoord(dPdxi, k);
      }
   }
   Gaudi::SymMatrix4x4 covRet;

   double covRetkl(0);
   for(int k(0); k<4; ++k)
   {
      for(int l(k); l<4; ++l)
      {
         for(int i(0); i<3; ++i)
         {
            for(int j(0); j<3; ++j)
            {
               covRetkl += dPkdBSVi[k][i]*dPkdBSVi[l][j]*covBSV[i][j];
               covRetkl += dPkdBPVi[k][i]*dPkdBPVi[l][j]*covBPV[i][j];
            }
         }

         for(int i(0); i<4; ++i)
         {
            for(int j(0); j<4; ++j)
            {
               covRetkl += dPkdXPi[k][i]*dPkdXPi[l][j]*covXP(i,j);
            }
         }
         for(int i(0); i<7; ++i)
         {
            for(int j(0); j<7; ++j)
            {
               covRetkl += dPkdmuTi[k][i]*dPkdmuTi[l][j]*covMuT(i,j);
            }
         }

         covRet(k,l) = covRetkl;
         covRetkl = 0;
      }
   }
   return covRet;
}
Gaudi::Matrix4x3 TupleToolJesus::getTauPBSVCov(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos,
      Gaudi::LorentzVector muP, Gaudi::SymMatrix3x3 covBSV)
{
   double dPldBSVi[4][3];
   Gaudi::LorentzVector Pup;
   Gaudi::LorentzVector Pdown;
   Gaudi::LorentzVector dPdBSVi;
 //  double sigma; 

   for(int i(0); i<3; ++i)
   {
   //   sigma = 0.05*covBSV(i,i); 
//      if(sigma > step)
      {
         setCoord(BSV,i, getCoord(BSV,i)+step);
         Pup = getTauP(BPV, BSV, XP, muPos, muP);
         setCoord(BSV,i, getCoord(BSV,i)-2*step);
         Pdown = getTauP(BPV, BSV, XP, muPos, muP);
         setCoord(BSV,i, getCoord(BSV,i)+step);
         dPdBSVi = (Pup-Pdown)/(2.*step);
      }
//      else dPdBSVi.SetPxPyPzE(0,0,0,0);

      for(int l(0); l<4; ++l)
      {
         dPldBSVi[l][i] = getCoord(dPdBSVi, l);
      }
   }

   Gaudi::Matrix4x3 ret;
   double retkl(0);

   for(int l(0); l<4; ++l)
   {
      for(int k(0); k<3; ++k)
      {
         for(int i(0); i<3; ++i)
         {
            retkl += dPldBSVi[l][i]*covBSV(i,k);
         }
         ret(k,l) = retkl;
         retkl = 0;
      }
   }

   return ret;
}

double TupleToolJesus::getCorMassErr(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector visP, Gaudi::SymMatrix3x3 covBPV, Gaudi::SymMatrix3x3 covBSV, Gaudi::SymMatrix4x4 covVisP)
{
   double deltaBSV[3] = {0,0,0};
   double deltaBPV[3] = {0,0,0};
   double deltaVisP[4] = {0,0,0,0};

   double mPlus, mMinus;
   //double sigma;

   for(int i(0); i<3; ++i)
   {
//      sigma = sqrt(covBPV(i,i));
//      if(sigma > step)
      {
         setCoord(BPV, i, getCoord(BPV,i) + step);
         mPlus = getCorMass(BPV, BSV, visP);
         setCoord(BPV, i, getCoord(BPV,i) - 2*step);
         mMinus = getCorMass(BPV, BSV, visP);
         setCoord(BPV, i, getCoord(BPV,i) + step);

         deltaBPV[i] = (mPlus-mMinus)/(2.*step);
      }

//      sigma = sqrt(covBSV(i,i));
//      if(sigma > step)
      {
         setCoord(BSV, i, getCoord(BSV,i) + step);
         mPlus = getCorMass(BPV, BSV, visP);
         setCoord(BSV, i, getCoord(BSV,i) - 2*step);
         mMinus = getCorMass(BPV, BSV, visP);
         setCoord(BSV, i, getCoord(BSV,i) + step);
         deltaBSV[i] = (mPlus-mMinus)/(2.*step);
      }
   }

   for(int i(0); i<4; ++i)
   {
 //     sigma = covVisP(i,i);   
//      if(sigma > step)
      {
         setCoord(visP,i, getCoord(visP,i)+step);
         mPlus = getCorMass(BPV, BSV, visP);
         setCoord(visP,i, getCoord(visP,i)-2*step);
         mMinus = getCorMass(BPV, BSV, visP);
         setCoord(visP,i, getCoord(visP,i)+step);
         deltaVisP[i] = (mPlus-mMinus)/(2.*step);
      }

   }

   double err(0);

   for(int i(0); i<3;++i)
   {
      for(int j(0); j<3; ++j)
      {
         err += deltaBPV[i]*deltaBPV[j]*covBPV(i,j);
         err += deltaBSV[i]*deltaBSV[j]*covBSV(i,j);
      }
   }
   for(int i(0); i<4; ++i)
   {
      for(int j(0); j<4; ++j)
      {
         err += deltaVisP[i]*deltaVisP[j]*covVisP(i,j);
      }
   }

   return sqrt(err);
}



double getCoord(Gaudi::XYZPoint p, int i)
{
   switch(i)
   {
      case 0 :
         return p.x();

      case 1 :
         return p.y();

      case 2 :
         return p.z();

      default :
         std::cerr<<"in TupleToolJesus::getCoord: try to access invalid coordinate"<<std::endl;
   }
   return 0;
}

void setCoord(Gaudi::XYZPoint& p, int i, double a)
{
   switch(i)
   {
      case 0 :
         p.SetX(a);
         break;

      case 1 :
         p.SetY(a);
         break;

      case 2 :
         p.SetZ(a);
         break;

      default :
         std::cerr<<"in TupleToolJesus::setCoord: try to access invalid coordinate"<<std::endl;
         break;
   }
}

double getCoord(Gaudi::XYZVector p, int i)
{
   switch(i)
   {
      case 0 :
         return p.x();

      case 1 :
         return p.y();

      case 2 :
         return p.z();

      default :
         std::cerr<<"in TupleToolJesus::getCoord: try to access invalid coordinate"<<std::endl;
   }
   return 0;
}

void setCoord(Gaudi::XYZVector& p, int i, double a)
{
   switch(i)
   {
      case 0 :
         p.SetX(a);
         break;

      case 1 :
         p.SetY(a);
         break;

      case 2 :
         p.SetZ(a);
         break;

      default :
         std::cerr<<"in TupleToolJesus::setCoord: try to access invalid coordinate"<<std::endl;
         break;
   }
}


double getCoord(Gaudi::LorentzVector p, int i)
{
   switch(i)
   {
      case 0 :
         return p.px();

      case 1 :
         return p.py();

      case 2 :
         return p.pz();

      case 3 : 
         return p.E();

      default :
         std::cerr<<"in TupleToolJesus::getCoord(LorentzVector): try to access invalid coordinate"<<std::endl;
   }
   return 0;
}
void setCoord(Gaudi::LorentzVector& p, int i, double a)
{
   switch(i)
   {
      case 0 :
         p.SetPx(a);
         break;

      case 1 :
         p.SetPy(a);
         break;

      case 2 :
         p.SetPz(a);
         break;

      case 3 :
         p.SetE(a);
         break;

      default :
         std::cerr<<"in TupleToolJesus::setCoord(LorentzVector): try to access invalid coordinate"<<std::endl;
         break;
   }
}

double getCoord(Gaudi::XYZPoint pos, Gaudi::LorentzVector p, int i)
{
   if(i>=0 && i<3) return getCoord(pos, i);
   if(i>=3 && i<7) return getCoord(p, i-3);
   std::cerr<<"in TupleToolJesus::getCoord(Pos, LorentzVector): try to access invalid coordinate"<<std::endl;
   return 0;
}
void setCoord(Gaudi::XYZPoint& pos, Gaudi::LorentzVector& p, int i, double a)
{
   
   if(i>=0 && i<3)
   {
       setCoord(pos, i, a);
       return;
   }
   if(i>=3 && i<7)
   {
       setCoord(p, i-3, a);
       return;
   }
   std::cerr<<"in TupleToolJesus::setCoord(Pos, LorentzVector): try to access invalid coordinate"<<std::endl;
}


// $Id: TupleToolTutorial.cpp,v 1.1 2009-06-11 16:22:29 rlambert Exp $
// Include files

// from Gaudi
#include "GaudiKernel/ToolFactory.h"

// local
#include "TupleToolMisSallyvs2.h"
#include <Kernel/GetIDVAlgorithm.h>
#include <Kernel/IDistanceCalculator.h>
#include "GaudiAlg/Tuple.h"
#include "GaudiAlg/TupleObj.h"
#include "Kernel/IParticleTransporter.h"

//#include "Phys/LoKiFitters/LifeTimeFitter.h"

#include "Event/Particle.h"
//-----------------------------------------------------------------------------
// Implementation file for class : TupleToolMisSallyvs2
//
// 2015-02 
//-----------------------------------------------------------------------------

// Declaration of the Tool Factory
// actually acts as a using namespace TupleTool
DECLARE_TOOL_FACTORY( TupleToolMisSallyvs2 )
//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TupleToolMisSallyvs2::TupleToolMisSallyvs2( const std::string& type,
                                         const std::string& name,
                                         const IInterface* parent )
: TupleToolBase ( type, name , parent ), taum(1776.82), step(1e-5), m_dva(0), m_dist(0), m_fit(0), m_combiner(0), 
m_transporterName ("ParticleTransporter:PUBLIC"), m_transporter()
{
   declareInterface<IParticleTupleTool>(this);
   declareProperty( "Transporter", m_transporterName );
   //declare properties here!
}

StatusCode TupleToolMisSallyvs2::initialize()
{
   const StatusCode sc = TupleToolBase::initialize();
   if ( sc.isFailure() ) return sc;

   m_dva = Gaudi::Utils::misgetIDVAlgorithm ( contextSvc(), this ) ;
   if (!m_dva) std::cout<<"DINOSAUR M_DVA"<<std::endl;
   if (!m_dva) return Error("Couldn't misget parent DVAlgorithm");

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

StatusCode TupleToolMisSallyvs2::fill( const LHCb::Particle* mother 
      , const LHCb::Particle* P
      , const std::string& head
      , Tuples::Tuple& tuple )
{

   //the fill method is called once per input particle
   //fill some information about the particle here!
   bool test(true);
   int isJesusOK(0);
//   std::cout<<"PLEASE WORK"<<std::endl;
//   std::cout<<"Particle id: "<<P->particleID().abspid()<<std::endl;

   //this tuple tool is called for each B 
   if(P->particleID().abspid() == 521)
   {
      LHCb::Particle::ConstVector source;
      std::string pclename;

      LHCb::Particle B;

      LHCb::Particle mu1;
      LHCb::Particle mu2;
      LHCb::Particle mu3;

      int id;
      int count(0);
      source = P->daughtersVector();
      LHCb::VertexBase BPV(*(m_dva->bestVertex (P)));
      LHCb::VertexBase BSV(*(P->endVertex()));

      B = *P;
      for(LHCb::Particle::ConstVector::const_iterator isource = source.begin(); isource != source.end(); isource++)
      {
         id = (*isource)->particleID().pid();

         if((abs(id) == 13) && (count == 1) )
         {
             mu1 = *(*isource);
         }
     
       count++;

      }


   if(P->particleID().abspid() == 443)
   {
      LHCb::Particle::ConstVector source;
      std::string pclename;


      LHCb::Particle mu1;
      LHCb::Particle mu2;
      LHCb::Particle mu3;

      int id;
      int count(0);
//      std::cout<<"PLEASE WORK 2"<<std::endl;    
      //Get Kst+1410 and the second muon from the B daughter
      source = P->daughtersVector();
//      std::cout<<"la"<<std::endl;
//      LHCb::VertexBase BPV(*(m_dva->bestVertex (P)));
//      std::cout<<"la la"<<std::endl;
//      LHCb::VertexBase BSV(*(P->endVertex()));
      //BSV = *((*isource)->endVertex());

//      B = *P;
      //*mother=*P;
      for(LHCb::Particle::ConstVector::const_iterator isource = source.begin(); isource != source.end(); isource++)
      {
         id = (*isource)->particleID().pid();

         if((abs(id) == 13) && (count == 0) )
         {
             mu2 = *(*isource);
         }
         if((abs(id) == 13) && (count == 1) )
         {
             mu3 = *(*isource);
         }
     
       count++;

      }
  
     }   





//      if(Kst_ex.particleID().abspid() != 100323)  return Error("Unable to retrieve Kst_ex", StatusCode::FAILURE);
      if(mu1.particleID().abspid() != 13)  return Error("Unable to retrieve mu_1", StatusCode::FAILURE);
      if(mu2.particleID().abspid() != 13)  return Error("Unable to retrieve mu_2", StatusCode::FAILURE);
      if(mu3.particleID().abspid() != 13)  return Error("Unable to retrieve mu_3", StatusCode::FAILURE);
      //Get Kst the first  muon from Kst+1410 daughter
      LHCb::Particle::ConstVector Bdaughters;
      Bdaughters.push_back(&mu1);
      Bdaughters.push_back(&mu2);
      Bdaughters.push_back(&mu3);

      LHCb::Particle Bcor;
      LHCb::Vertex BSVcor;
      m_combiner->combine(Bdaughters, Bcor, BSVcor); 

      //Compute a couple of interesting things

      //std::cout<<"IS THERE A  VERTEX?"<<(tau.endVertex()->position()).x()<<" "<<(tau.endVertex()->position()).y()<<" "<<(tau.endVertex()->position()).z()<<std::endl;

      double corMass(misgetCorMass(BPV.position(), BSV.position(), mu1.momentum()+mu2.momentum()+mu3.momentum()));
      double corMassErr(misgetCorMassErr(BPV.position(), BSV.position(), P->momentum(), BPV.covMatrix(), BSV.covMatrix(), P->momCovMatrix()));

//      std::cout<<" Corrected Mass: "<<corMass<<std::endl;
//      std::cout<<" Corrected Mass Error: "<<corMassErr<<std::endl;
      //compute length of fly and decay time of tau

      test &= tuple->column(head + "_corMass", corMass);
      test &= tuple->column(head + "_corMassERR", corMassErr);

      if(!test) std::cout<<"DINOSAUR 5"<<std::endl;

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

//double misgetRhoDist(Gaudi::XYZPoint A, Gaudi::XYZPoint B)
//{
//   Gaudi::XYZVector vec(B-A);
//   return sqrt(vec.x()*vec.x()+vec.y()*vec.y());
//}

Gaudi::XYZPoint TupleToolMisSallyvs2::misgetTauDecayVtx(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP)
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

Gaudi::LorentzVector TupleToolMisSallyvs2::misgetTauP(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP)
{
   return misgetTauP(BPV, BSV, XP, misgetTauDecayVtx( BPV,  BSV, XP,  muPos, muP));
}

Gaudi::LorentzVector TupleToolMisSallyvs2::misgetTauP(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint tauSV)
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
   tmp = norm*tmp; //now tmp is misset to the tau 3 mmtm

   double Etau(sqrt( taum*taum+tmp.Mag2() ));

   Gaudi::LorentzVector ret;
   ret.SetPxPyPzE(tmp.x(), tmp.y(), tmp.z(), Etau);
   return ret;
}

double TupleToolMisSallyvs2::misgetHolyMass(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP)
{
      return (misgetTauP( BPV, BSV, XP, muPos, muP)+XP).M();
}

double TupleToolMisSallyvs2::misgetCorMass(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV,  Gaudi::LorentzVector visP)
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

Gaudi::SymMatrix3x3 TupleToolMisSallyvs2::misgetTauDecayVtxCov(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos,
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
         missetCoord(BPV, i, misgetCoord(BPV, i) + step);
         vtxup = misgetTauDecayVtx(BPV, BSV, XP, muPos, muP);
         missetCoord(BPV, i, misgetCoord(BPV, i) - 2*step);
         vtxdown = misgetTauDecayVtx(BPV, BSV, XP, muPos, muP);
         missetCoord(BPV, i, misgetCoord(BPV, i) + step);
         stock = (1./(2*step)) * (vtxup-vtxdown);
      }
//      else stock.SetXYZ(0,0,0);


      for(int k(0); k<3; ++k)
      {
         dVkdBPVi[k][i] = misgetCoord(stock, k);
      }

//      sigma = sqrt(covBSV(i,i));
//      if(sigma > step)
      {
         missetCoord(BSV, i, misgetCoord(BSV, i) + step);
         vtxup = misgetTauDecayVtx(BPV, BSV, XP, muPos, muP);
         missetCoord(BSV, i, misgetCoord(BSV, i) - 2*step);
         vtxdown = misgetTauDecayVtx(BPV, BSV, XP, muPos, muP);
         missetCoord(BSV, i, misgetCoord(BSV, i) + step);

         stock = (1./(2*step)) * (vtxup-vtxdown);
      }
//      else stock.SetXYZ(0,0,0);

      for(int k(0); k<3; ++k)
      {
         dVkdBSVi[k][i] = misgetCoord(stock, k);
      }
   }

   for(int i(0); i<4; ++i)
   {
//      sigma = sqrt(covXP(i,i));
//      if(sigma > step)
      {
         missetCoord(XP,i, misgetCoord(XP,i) + step);
         vtxup = misgetTauDecayVtx(BPV, BSV, XP, muPos, muP);
         missetCoord(XP,i, misgetCoord(XP,i) - 2*step);
         vtxdown = misgetTauDecayVtx(BPV, BSV, XP, muPos, muP);
         missetCoord(XP,i, misgetCoord(XP,i) + step);

         stock = (1./(2*step)) * (vtxup-vtxdown);
      }
//      else stock.SetXYZ(0,0,0);

      for(int k(0); k<3; ++k)
      {
         dVkdXPi[k][i] = misgetCoord(stock, k);
      }
   }

   for(int i(0); i<7; ++i)
   {
//      sigma = sqrt(covMuT(i,i));
//      if(sigma > step)
      {
         missetCoord(muPos, muP, i, misgetCoord(muPos, muP,i) + step);
         vtxup = misgetTauDecayVtx(BPV, BSV, XP, muPos, muP);
         missetCoord(muPos, muP, i, misgetCoord(muPos, muP,i) - 2*step);
         vtxdown = misgetTauDecayVtx(BPV, BSV, XP, muPos, muP);
         missetCoord(muPos, muP, i, misgetCoord(muPos, muP,i) + step);

         stock = (1./(2*step)) * (vtxup-vtxdown);
      }
//      else stock.SetXYZ(0,0,0);

      for(int k(0); k<3; ++k)
      {
         dVkdmuTi[k][i] = misgetCoord(stock, k);
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

double TupleToolMisSallyvs2::misgetHolyMassErr(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos,
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
         missetCoord(BPV, i, misgetCoord(BPV, i) + step);
         mPlus = misgetHolyMass(BPV, BSV, XP, muPos, muP);
         missetCoord(BPV, i, misgetCoord(BPV, i) -2*step);
         mMinus = misgetHolyMass(BPV, BSV, XP, muPos, muP);
         deltaBPV[i] = (mPlus-mMinus)/(2*step);
      }

    //  sigma = sqrt(covBSV(i,i));
//      if(sigma > step)
      {
         missetCoord(BSV, i, misgetCoord(BSV, i) + step);
         mPlus = misgetHolyMass(BPV, BSV, XP, muPos, muP);
         missetCoord(BSV, i, misgetCoord(BSV, i) - 2*step);
         mMinus = misgetHolyMass(BPV, BSV, XP, muPos, muP);
         missetCoord(BSV, i, misgetCoord(BSV, i) + step);
         deltaBSV[i] = (mPlus-mMinus)/(2*step);
      }
   }

   for(int i(0); i<4; ++i)
   {
  //    sigma = sqrt(covXP(i,i));
  //    if(sigma > step)
      {
         missetCoord(XP, i, misgetCoord(XP,i)+step);
         mPlus = misgetHolyMass(BPV, BSV, XP, muPos, muP);
         missetCoord(XP, i, misgetCoord(XP,i)-2*step);
         mMinus = misgetHolyMass(BPV, BSV, XP, muPos, muP);
         missetCoord(XP, i, misgetCoord(XP,i)+step);
         deltaXP[i] = (mPlus-mMinus)/(2*step);
      }
   }

   for(int i(0); i<7; ++i)
   {
//      sigma = sqrt(covV(i,i));
//      if(sigma > step)
      {
         missetCoord(muPos, muP, i, misgetCoord(muPos, muP,i) + step);
         mPlus = misgetHolyMass(BPV, BSV, XP, muPos, muP);
         missetCoord(muPos, muP, i, misgetCoord(muPos, muP,i) - 2*step);
         mMinus = misgetHolyMass(BPV, BSV, XP, muPos, muP);
         missetCoord(muPos, muP, i, misgetCoord(muPos, muP,i) + step);
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

Gaudi::SymMatrix4x4 TupleToolMisSallyvs2::misgetTauPCov(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP,
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

         missetCoord(BPV, i, misgetCoord(BPV, i) + step);
         Pup = misgetTauP(BPV, BSV, XP, muPos, muP);
         missetCoord(BPV, i, misgetCoord(BPV, i) - 2*step);
         Pdown = misgetTauP(BPV, BSV, XP, muPos, muP);
         missetCoord(BPV, i, misgetCoord(BPV, i) + step);
         dPdxi = (1./(2*step)) * (Pup-Pdown);
      }
   //   else dPdxi.SetPxPyPzE(0,0,0,0);

      for(int k(0); k<4; ++k)
      {
         dPkdBPVi[k][i] = misgetCoord(dPdxi, k);
      }


    //  sigma = sqrt(covBSV(i,i));
     // if(sigma > step)
      {

         missetCoord(BSV, i, misgetCoord(BSV, i) + step);
         Pup = misgetTauP(BPV, BSV, XP, muPos, muP);
         missetCoord(BSV, i, misgetCoord(BSV, i) - 2*step);
         Pdown = misgetTauP(BPV, BSV, XP, muPos, muP);
         missetCoord(BSV, i, misgetCoord(BSV, i) + step);
         dPdxi = (1./(2.*step)) * (Pup-Pdown);
      }
     // else dPdxi.SetPxPyPzE(0,0,0,0);

      for(int k(0); k<4; ++k)
      {
         dPkdBSVi[k][i] = misgetCoord(dPdxi, k);
      }
   }

   for(int i(0); i<4; ++i)
   {
   //   sigma = sqrt(covXP(i,i));
   //   if(sigma > step)
      {
         missetCoord(XP,i, misgetCoord(XP,i) + step);
         Pup = misgetTauP(BPV, BSV, XP, muPos, muP);
         missetCoord(XP,i, misgetCoord(XP,i) - 2*step);
         Pdown = misgetTauP(BPV, BSV, XP, muPos, muP);
         missetCoord(XP,i, misgetCoord(XP,i) + step);

         dPdxi = (1./(2.*step)) * (Pup-Pdown);
      }
    //  else dPdxi.SetPxPyPzE(0,0,0,0);

      for(int k(0); k<4; ++k)
      {
         dPkdXPi[k][i] = misgetCoord(dPdxi, k);
      }
   }

   for(int i(0); i<7; ++i)
   {
   //   sigma = sqrt(covMuT(i,i));
   //   if(sigma > step)
      {
         missetCoord(muPos, muP, i, misgetCoord(muPos, muP,i) + step);
         Pup = misgetTauP(BPV, BSV, XP, muPos, muP);
         missetCoord(muPos, muP, i, misgetCoord(muPos, muP,i) - 2*step);
         Pdown = misgetTauP(BPV, BSV, XP, muPos, muP);
         missetCoord(muPos, muP, i, misgetCoord(muPos, muP,i) + step);

         dPdxi = (1./(2*step)) * (Pup-Pdown);
      }
  //    else dPdxi.SetPxPyPzE(0,0,0,0);

      for(int k(0); k<4; ++k)
      {
         dPkdmuTi[k][i] = misgetCoord(dPdxi, k);
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
Gaudi::Matrix4x3 TupleToolMisSallyvs2::misgetTauPBSVCov(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos,
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
         missetCoord(BSV,i, misgetCoord(BSV,i)+step);
         Pup = misgetTauP(BPV, BSV, XP, muPos, muP);
         missetCoord(BSV,i, misgetCoord(BSV,i)-2*step);
         Pdown = misgetTauP(BPV, BSV, XP, muPos, muP);
         missetCoord(BSV,i, misgetCoord(BSV,i)+step);
         dPdBSVi = (Pup-Pdown)/(2.*step);
      }
//      else dPdBSVi.SetPxPyPzE(0,0,0,0);

      for(int l(0); l<4; ++l)
      {
         dPldBSVi[l][i] = misgetCoord(dPdBSVi, l);
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

double TupleToolMisSallyvs2::misgetCorMassErr(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector visP, Gaudi::SymMatrix3x3 covBPV, Gaudi::SymMatrix3x3 covBSV, Gaudi::SymMatrix4x4 covVisP)
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
         missetCoord(BPV, i, misgetCoord(BPV,i) + step);
         mPlus = misgetCorMass(BPV, BSV, visP);
         missetCoord(BPV, i, misgetCoord(BPV,i) - 2*step);
         mMinus = misgetCorMass(BPV, BSV, visP);
         missetCoord(BPV, i, misgetCoord(BPV,i) + step);

         deltaBPV[i] = (mPlus-mMinus)/(2.*step);
      }

//      sigma = sqrt(covBSV(i,i));
//      if(sigma > step)
      {
         missetCoord(BSV, i, misgetCoord(BSV,i) + step);
         mPlus = misgetCorMass(BPV, BSV, visP);
         missetCoord(BSV, i, misgetCoord(BSV,i) - 2*step);
         mMinus = misgetCorMass(BPV, BSV, visP);
         missetCoord(BSV, i, misgetCoord(BSV,i) + step);
         deltaBSV[i] = (mPlus-mMinus)/(2.*step);
      }
   }

   for(int i(0); i<4; ++i)
   {
 //     sigma = covVisP(i,i);   
//      if(sigma > step)
      {
         missetCoord(visP,i, misgetCoord(visP,i)+step);
         mPlus = misgetCorMass(BPV, BSV, visP);
         missetCoord(visP,i, misgetCoord(visP,i)-2*step);
         mMinus = misgetCorMass(BPV, BSV, visP);
         missetCoord(visP,i, misgetCoord(visP,i)+step);
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



double misgetCoord(Gaudi::XYZPoint p, int i)
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
         std::cerr<<"in TupleToolMisSallyvs2::misgetCoord: try to access invalid coordinate"<<std::endl;
   }
   return 0;
}

void missetCoord(Gaudi::XYZPoint& p, int i, double a)
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
         std::cerr<<"in TupleToolMisSallyvs2::missetCoord: try to access invalid coordinate"<<std::endl;
         break;
   }
}

double misgetCoord(Gaudi::XYZVector p, int i)
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
         std::cerr<<"in TupleToolMisSallyvs2::misgetCoord: try to access invalid coordinate"<<std::endl;
   }
   return 0;
}

void missetCoord(Gaudi::XYZVector& p, int i, double a)
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
         std::cerr<<"in TupleToolMisSallyvs2::missetCoord: try to access invalid coordinate"<<std::endl;
         break;
   }
}


double misgetCoord(Gaudi::LorentzVector p, int i)
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
         std::cerr<<"in TupleToolMisSallyvs2::misgetCoord(LorentzVector): try to access invalid coordinate"<<std::endl;
   }
   return 0;
}
void missetCoord(Gaudi::LorentzVector& p, int i, double a)
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
         std::cerr<<"in TupleToolMisSallyvs2::missetCoord(LorentzVector): try to access invalid coordinate"<<std::endl;
         break;
   }
}

double misgetCoord(Gaudi::XYZPoint pos, Gaudi::LorentzVector p, int i)
{
   if(i>=0 && i<3) return misgetCoord(pos, i);
   if(i>=3 && i<7) return misgetCoord(p, i-3);
   std::cerr<<"in TupleToolMisSallyvs2::misgetCoord(Pos, LorentzVector): try to access invalid coordinate"<<std::endl;
   return 0;
}
void missetCoord(Gaudi::XYZPoint& pos, Gaudi::LorentzVector& p, int i, double a)
{
   
   if(i>=0 && i<3)
   {
       missetCoord(pos, i, a);
       return;
   }
   if(i>=3 && i<7)
   {
       missetCoord(p, i-3, a);
       return;
   }
   std::cerr<<"in TupleToolMisSallyvs2::missetCoord(Pos, LorentzVector): try to access invalid coordinate"<<std::endl;
}


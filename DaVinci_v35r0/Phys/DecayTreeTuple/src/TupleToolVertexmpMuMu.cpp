// Include files

// from Gaudi
#include "GaudiKernel/ToolFactory.h"

// local
#include "TupleToolVertexmpMuMu.h"

#include <Kernel/GetIDVAlgorithm.h>
#include <Kernel/IDVAlgorithm.h>
#include <Kernel/IDistanceCalculator.h>
#include <Kernel/IVertexFit.h>
#include <Kernel/ILifetimeFitter.h>
#include "Kernel/IPVReFitter.h"
#include "GaudiAlg/Tuple.h"
#include "GaudiAlg/TupleObj.h"

#include "TROOT.h"
#include "Event/Particle.h"
#include "TLorentzVector.h"
#include "TVector3.h"
//#include<vector>

using namespace std;
using namespace LHCb;

//-----------------------------------------------------------------------------
// Implementation file for class : TupleToolVertexmpMuMu
//
// @author Mitesh Patel, Patrick Koppenburg
// @date   2008-04-15
//-----------------------------------------------------------------------------

// Declaration of the Tool Factory
// actually acts as a using namespace TupleTool
DECLARE_TOOL_FACTORY( TupleToolVertexmpMuMu )

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
  TupleToolVertexmpMuMu::TupleToolVertexmpMuMu( const std::string& type,
                                        const std::string& name,
                                        const IInterface* parent )
    : TupleToolBase ( type, name , parent )
    , m_dva(0)
    , m_dist(0)
    , m_pVertexFit(0)
{
  declareInterface<IParticleTupleTool>(this);
  declareProperty("VertexFitter", m_typeVertexFit = "LoKi::VertexFitter" );
  declareProperty("VertexCov",m_vcov=false);
  declareProperty("MomCov",m_momcov=false);
  declareProperty("MotherID",m_motherid=521);
  declareProperty("XID",m_Xid=13);
}

//=============================================================================

StatusCode TupleToolVertexmpMuMu::initialize()
{
  const StatusCode sc = TupleToolBase::initialize();
  if ( sc.isFailure() ) return sc;

  m_dva = Gaudi::Utils::getIDVAlgorithm ( contextSvc(), this ) ;
  if (!m_dva) return Error("Couldn't get parent DVAlgorithm",
                           StatusCode::FAILURE);

  m_dist = m_dva->distanceCalculator ();
  if( !m_dist ){
    Error("Unable to retrieve the IDistanceCalculator tool");
    return StatusCode::FAILURE;
  }

  //m_pVertexFit= m_dva->vertexFitter();
  m_pVertexFit  = tool<IVertexFit>(m_typeVertexFit,this);
  //m_pVertexFit  = tool<IVertexFit>("OfflineVertexFitter",this);
  if( !m_pVertexFit ){
    Error("Unable to retrieve the IVertexFit tool");
    return StatusCode::FAILURE;
  }
  m_ltfit = tool<ILifetimeFitter>( "PropertimeFitter", this );
  if( !m_ltfit ){
    Error("Unable to retrieve the ILifetimeFitter tool");
    return StatusCode::FAILURE;
  }
  m_pvReFitter = tool<IPVReFitter>("AdaptivePVReFitter", this );

  return sc;
}

//=============================================================================

StatusCode TupleToolVertexmpMuMu::fill( const Particle* mother
                                    , const Particle* P
                                    , const std::string& head
                                    , Tuples::Tuple& tuple )
{

  const std::string prefix=fullName(head);
  Assert( P && mother && m_dist
          , "This should not happen, you are inside TupleToolVertexmpMuMu.cpp :(" );


  bool test=true;
  // --------------------------------------------------

  // find the origin vertex. Either the primary or the origin in the
  // decay
  /*
    const VertexBase* vtx = 0;
    if( mother != P ) vtx = originVertex( mother, P );
    if( !vtx ){
    Error("Can't retrieve the origin vertex for " + prefix );
    return StatusCode::FAILURE;
    }
  */
  const LHCb::Particle* pro_part; 
  const LHCb::Particle* mu_part;
  const LHCb::Particle* mu3_part;
  LHCb::Particle::ConstVector parts2Vertex;
  LHCb::Particle::ConstVector source;
  LHCb::Particle::ConstVector target;
  double mcorr, q2_one, q2_two, mcorrerr, mcorrfullerr;
  std::vector<double> mcorr_errors;
  std::vector<TLorentzVector> nu_slns;
  int count=0;

  if (P->isBasicParticle()){
    source.push_back(mother);
  }
  else{
    source.push_back(P);
  }

  do {
    target.clear();
    for(LHCb::Particle::ConstVector::const_iterator isource = source.begin(); 
        isource != source.end(); isource++){
      
      if(!((*isource)->daughters().empty())){
        
        LHCb::Particle::ConstVector tmp = (*isource)->daughtersVector();
        
        for( LHCb::Particle::ConstVector::const_iterator itmp = tmp.begin(); 
             itmp!=tmp.end(); itmp++){
          target.push_back(*itmp);
//          cout<<"Particle id: "<<(*itmp)->particleID().pid()<<" Wooooohoooooooooooooooooooooooo!"<<endl;
          count++;
//          cout<<count<<endl;
         
                if((*itmp)->proto() && 22 != (*itmp)->particleID().abspid()){
               
                if (((*itmp)->particleID().abspid()  == m_Xid) && count==2)

                {
                parts2Vertex.push_back(*itmp);
                pro_part = (*itmp);
//                cout<<"X_ID part: "<<"ID of particle 2: "<< (*itmp)->particleID().pid()<<endl;
                }
                if (((*itmp)->particleID().abspid() == 13) && count==3)
                {
                parts2Vertex.push_back(*itmp);
                mu_part = (*itmp);
//                cout<<"Mu part: "<<" ID of particle 3: "<< (*itmp)->particleID().pid()<<endl;      
                }
	        }
      }     
      } // if endVertex
    } // isource
    source = target;
  } while(target.size() > 0);

  // vetex selected proton and muon 
  LHCb::Vertex Xmu_vert;
  const LHCb::VertexBase* PV;

  LHCb::Particle *newP = new LHCb::Particle(LHCb::ParticleID(m_motherid));
  StatusCode sc = m_pVertexFit->fit(parts2Vertex,Xmu_vert,*newP);
// StatusCode sc2 = m_pVertexFit->fit(parts2Vertex,Xmu_vert,*newP);

    PV = m_dva->bestVertex ( newP );
    //cout<<"Filling"<<endl;
    fillVertex(&Xmu_vert, prefix +"_mpMuMu_SV", tuple);
    fillVertex(PV, prefix + "_mpMuMu_PV", tuple);
    if(m_momcov)
    {
    const Gaudi::SymMatrix4x4 & mom_cov = newP->momCovMatrix ();
    const Gaudi::Matrix4x3 & posmom_cov = newP->posMomCovMatrix ();
    test &= tuple->matrix( prefix +  "_mpMuMu_MOM_COV_", mom_cov );
    test &= tuple->matrix( prefix +  "_mpMuMu_POSMOM_COV_", posmom_cov );
    }

    Gaudi::LorentzVector LV_newP,LV_mu, LV_XID;
    LV_newP = newP->momentum();
    TLorentzVector TLV_newP(LV_newP.px(),LV_newP.py(),LV_newP.pz(),LV_newP.E());
    // muon LV
    LV_mu = mu_part->momentum();
    TLorentzVector TLV_mu(LV_mu.px(),LV_mu.py(),LV_mu.pz(),LV_mu.E());

    //sally addition
    LV_XID = pro_part->momentum();
    TLorentzVector TLV_pro(LV_XID.px(),LV_XID.py(),LV_XID.pz(),LV_XID.E());

    double LV_invmass, LV_invmasssq;
    LV_invmasssq = (TLV_mu+TLV_pro).M2();
    LV_invmass = (TLV_mu+TLV_pro).M();
    test &= tuple->column(  prefix + "_mpMuMu_INVMASS", LV_invmass);
    test &= tuple->column(  prefix + "_mpMuMu_INVMASSSQ", LV_invmasssq);



    TVector3 TV3_PV(PV->position().X(),PV->position().Y(), PV->position().Z());
    TVector3 TV3_SV(Xmu_vert.position().X(),Xmu_vert.position().Y(), Xmu_vert.position().Z());
    
    TVector3 Mdirn = (TV3_SV - TV3_PV).Unit();

//    mcorr = Mcorr(TLV_newP, Mdirn);
//    mcorr_errors = Mcorr_errors(TV3_SV, TV3_PV, TLV_newP, newP->covMatrix(), PV->covMatrix());
//    nu_slns = recoNu(TLV_newP, Mdirn, 5279.15); 



  //  test &= tuple->column(  prefix + "_mpMuMu_MCORR", mcorr);
  //  if(mcorr_errors.size() ==  2)
  //  {
  //  mcorrerr = mcorr_errors[0];
  //  mcorrfullerr = mcorr_errors[1];
  //  test &= tuple->column(  prefix + "_mpMuMu_MCORRERR", mcorrerr);
  //  test &= tuple->column(  prefix + "_mpMuMu_MCORRFULLERR", mcorrfullerr);
  //  }
  //  else
 //   {
 //   test &= tuple->column(  prefix + "_mpMuMu_MCORRERR", -1000.);
 //   test &= tuple->column(  prefix + "_mpMuMu_MCORRFULLERR", -1000.);
 //   }

 //   if(nu_slns.size() ==  2)
 //   {
 //   q2_one = (nu_slns[0] + TLV_mu).M2();
 //   q2_two = (nu_slns[1] + TLV_mu).M2();

 //   test &= tuple->column(  prefix + "_mpMuMu_Q2SOL1", q2_one);
 //   test &= tuple->column(  prefix + "_mpMuMu_Q2SOL2", q2_two);
 //   }
 //   else
 //   {
 //   test &= tuple->column(  prefix + "_mpMuMu_Q2SOL1", -1000.);
 //   test &= tuple->column(  prefix + "_mpMuMu_Q2SOL2", -1000.);
 //   }
    debug() << "PAST FILL " << endreq;
    //}
    // replaced by V.B. 20.Aug.2k+9: (parts2Vertex,vtxWithExtraTrack);
    // Remove the added track from parts2Vertex

    

  return StatusCode(test);
}

//=========================================================================
//
//=========================================================================
StatusCode TupleToolVertexmpMuMu::fillVertex( const LHCb::VertexBase* vtx,
                                          const std::string& vtx_name,
                                          Tuples::Tuple& tuple ) const
{
  bool test = true ;

  // decay vertex information:
  if ( !vtx )
  {
    Gaudi::XYZPoint pt(-999.,-999.,-999.) ; // arbitrary point
    test &= tuple->column(  vtx_name+"_", pt );
    test &= tuple->column(  vtx_name + "_XERR", -999. );
    test &= tuple->column(  vtx_name + "_YERR", -999. );
    test &= tuple->column(  vtx_name + "_ZERR", -999. );
    test &= tuple->column(  vtx_name + "_CHI2", -999. );
    test &= tuple->column(  vtx_name + "_NDOF", -1 );
    test &= tuple->matrix(  vtx_name + "_COV_", Gaudi::SymMatrix3x3()  );
  }
  else
  {
    test &= tuple->column( vtx_name+"_", vtx->position() );
    test &= tuple->column(  vtx_name + "_CHI2", vtx->chi2() );
    test &= tuple->column(  vtx_name + "_NDOF", vtx->nDoF() );
    if(m_vcov)
    {
    const Gaudi::SymMatrix3x3 & m = vtx->covMatrix ();
    test &= tuple->matrix(  vtx_name + "_COV_", m );
    }
  }
  if (!test) Warning("Error in fillVertex "+vtx_name,1).ignore();
  return StatusCode(test) ;
}


double TupleToolVertexmpMuMu::Mcorr(TLorentzVector Y, TVector3 M_dirn)
{
     double P_T = (Y.Vect()).Perp(M_dirn);
     return  sqrt(Y.M2() + P_T * P_T) + P_T;
}

std::vector<TLorentzVector> TupleToolVertexmpMuMu::recoNu(TLorentzVector Y, TVector3 M_dirn, double mass)
    {
	std::vector<TLorentzVector> p_nu;
	// Get 3 Vector from Y
	TVector3 Y3  = (Y).Vect(); 
	// Construct combined Xmu/Kmu 4 vector in new rotated frame
	TLorentzVector PXmu(Y3.Dot(M_dirn),(Y).Perp(M_dirn),0.0,(Y).E() );
	// Get component of Y3 perpendicular to *M_dirn
	TVector3 Perp_dirn  = ( Y3  - (M_dirn) * Y3.Dot((M_dirn))).Unit();  
	// Calculate neutrino energy in mother rest frame
	double E_nurest = ( mass  * mass  - (Y).M2())/ (2 * mass ); 
	// Calculate Xmu " "
	double E_mpMuMurest = sqrt(E_nurest * E_nurest + (Y).M2());
	double px_rest;

	// Find magnitude of momentum along mother dirn in rest frame

	if( E_nurest * E_nurest  - PXmu.Py() * PXmu.Py() >= 0)
	{
	    px_rest = sqrt( E_nurest * E_nurest  - PXmu.Py() * PXmu.Py() ); 
	}
	else
	{  
	    return p_nu;
	}

	//px_rest = sqrt( E_nurest * E_nurest  - PXmu.Py() * PXmu.Py() ); 
	// quadratic coefficients
	double A = (Y).E() * (Y).E()  - PXmu.Px() * PXmu.Px();
	double B = - 2 * PXmu.Px()  * (E_nurest * E_mpMuMurest + px_rest * px_rest );
	double C =  - (E_nurest * E_mpMuMurest + px_rest * px_rest )*
	    (E_nurest * E_mpMuMurest + px_rest * px_rest ) +  (Y).E() * (Y).E() * PXmu.Py() * PXmu.Py();

	if (B*B < 4*A*C) { 
	    return  p_nu;
	}
	// Two neutrino E/p solutions in Lab Frame
	double p1nu = (- B + sqrt(B*B - 4 * A * C) )/(2*A);
	double p2nu = (- B - sqrt(B*B - 4 * A * C) )/(2*A);

	// reconstruct neutrino 3 vectors and 4 vectors
	TVector3 P_nu_recon_3V1 = (M_dirn) * p1nu  + Perp_dirn * -PXmu.Py(); 
	TVector3 P_nu_recon_3V2 = (M_dirn) * p2nu  + Perp_dirn * -PXmu.Py(); 
	p_nu.push_back(TLorentzVector(P_nu_recon_3V1, sqrt(p1nu*p1nu + PXmu.Py() * PXmu.Py())));
	p_nu.push_back(TLorentzVector(P_nu_recon_3V2, sqrt(p2nu*p2nu + PXmu.Py() * PXmu.Py())));
	return p_nu;
    }

std::vector<double> TupleToolVertexmpMuMu::Mcorr_errors(TVector3 v1, TVector3 v2, TLorentzVector p,  Gaudi::SymMatrix7x7 cov1, Gaudi::SymMatrix3x3 cov2 )
{
    //std::cout << cov1[0][1] << "  "  << cov1[0][2] << "   "  << cov1[1][2] << std::endl;
   // std::cout << cov1[1][0] << "  "  << cov1[2][0] << "   "  << cov1[2][1] << std::endl;
    double x  = v1.Px();
    double y  = v1.Py();
    double z  = v1.Pz();
    double xp  = v2.Px();
    double yp  = v2.Py();
    double zp  = v2.Pz();
    double px = p.Px();
    double py = p.Py();
    double pz = p.Pz();
    double k = p.E();
//     double P_T = (p.Vect()).Perp((v1 - v2));
  //   double M_corr =sqrt(p.M2() + P_T * P_T) + P_T;

double dMcdpx = (2*(1 - pow(x - xp,2)/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	       (px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) - 
	             (2*(x - xp)*(y - yp)*(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/
					               (pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
		           (2*(x - xp)*(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
			             (z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))/
        (2.*sqrt(pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
		         pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
			         pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2))) + 
	   (-2*px + 2*(1 - pow(x - xp,2)/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	           (px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) - 
		         (2*(x - xp)*(y - yp)*(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/
					                   (pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
			       (2*(x - xp)*(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				         (z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))/
	       (2.*sqrt(pow(k,2) - pow(px,2) - pow(py,2) - pow(pz,2) + 
			        pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
				        pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
					        pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2)));

double dMcdpy = (2*(1 - pow(y - yp,2)/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	       (py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) - 
	             (2*(x - xp)*(y - yp)*(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/
					               (pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
		           (2*(y - yp)*(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
			             (z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))/
        (2.*sqrt(pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
		         pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
			         pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2))) + 
	   (-2*py + 2*(1 - pow(y - yp,2)/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	           (py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) - 
		         (2*(x - xp)*(y - yp)*(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/
					                   (pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
			       (2*(y - yp)*(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				         (z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))/
	       (2.*sqrt(pow(k,2) - pow(px,2) - pow(py,2) - pow(pz,2) + 
			        pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
				        pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
					        pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2)));

double dMcdpz = (2*(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	       (1 - pow(z - zp,2)/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) - 
	             (2*(x - xp)*(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
		               (z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
		           (2*(y - yp)*(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
			             (z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))/
        (2.*sqrt(pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
		         pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
			         pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2))) + 
	   (-2*pz + 2*(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	           (1 - pow(z - zp,2)/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) - 
		         (2*(x - xp)*(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
			           (z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
			       (2*(y - yp)*(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				         (z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))/
	       (2.*sqrt(pow(k,2) - pow(px,2) - pow(py,2) - pow(pz,2) + 
			        pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
				        pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
					        pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2)));

double dMcdE = k/sqrt(pow(k,2) - pow(px,2) - pow(py,2) - pow(pz,2) + 
	     pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
	          pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
		       pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2));

double dMcdx = (2*((2*pow(x - xp,2)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) - 
	             (px*(x - xp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
		              (px*(x - xp) + py*(y - yp) + pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	       (px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
	             2*((2*(x - xp)*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) - 
			          (px*(y - yp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
		            (py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
			          2*((2*(x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) - 
				               (px*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				         (pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))))/
        (2.*sqrt(pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
		         pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
			         pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2))) + 
	   (2*((2*pow(x - xp,2)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) - 
	                (px*(x - xp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
			         (px*(x - xp) + py*(y - yp) + pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	           (px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
		         2*((2*(x - xp)*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) - 
			              (px*(y - yp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
			        (py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
				      2*((2*(x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) - 
					           (px*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				             (pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))))/
	       (2.*sqrt(pow(k,2) - pow(px,2) - pow(py,2) - pow(pz,2) + 
			        pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
				        pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
					        pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2)));

double dMcdy = (2*((2*(x - xp)*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) - 
	             (py*(x - xp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	       (px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
	             2*((2*pow(y - yp,2)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) - 
			          (py*(y - yp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
				           (px*(x - xp) + py*(y - yp) + pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
		            (py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
			          2*((2*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) - 
				               (py*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				         (pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))))/
        (2.*sqrt(pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
		         pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
			         pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2))) + 
	   (2*((2*(x - xp)*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) - 
	                (py*(x - xp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	           (px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
		         2*((2*pow(y - yp,2)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) - 
			              (py*(y - yp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
				               (px*(x - xp) + py*(y - yp) + pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
			        (py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
				      2*((2*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) - 
					           (py*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				             (pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))))/
	       (2.*sqrt(pow(k,2) - pow(px,2) - pow(py,2) - pow(pz,2) + 
			        pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
				        pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
					        pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2)));

double dMcdz = (2*(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	       (-((pz*(x - xp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
		         (2*(x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2)) + 
	             2*(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
		            (-((pz*(y - yp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
			              (2*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2)) + 
			          2*(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				         (-((px*(x - xp) + py*(y - yp) + pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) - 
					           (pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) + 
						            (2*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*pow(z - zp,2))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2)))/
        (2.*sqrt(pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
		         pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
			         pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2))) + 
	   (2*(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	           (-((pz*(x - xp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
		             (2*(x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2)) + 
		         2*(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
			        (-((pz*(y - yp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
				          (2*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2)) + 
				      2*(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				             (-((px*(x - xp) + py*(y - yp) + pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) - 
					               (pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) + 
						                (2*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*pow(z - zp,2))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2)))/
	       (2.*sqrt(pow(k,2) - pow(px,2) - pow(py,2) - pow(pz,2) + 
			        pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
				        pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
					        pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2)));

double dMcdxp = (2*((-2*pow(x - xp,2)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) + 
	             (px*(x - xp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) + 
		              (px*(x - xp) + py*(y - yp) + pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	       (px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
	             2*((-2*(x - xp)*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) + 
			          (px*(y - yp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
		            (py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
			          2*((-2*(x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) + 
				               (px*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				         (pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))))/
        (2.*sqrt(pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
		         pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
			         pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2))) + 
	   (2*((-2*pow(x - xp,2)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) + 
	                (px*(x - xp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) + 
			         (px*(x - xp) + py*(y - yp) + pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	           (px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
		         2*((-2*(x - xp)*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) + 
			              (px*(y - yp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
			        (py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
				      2*((-2*(x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) + 
					           (px*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				             (pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))))/
	       (2.*sqrt(pow(k,2) - pow(px,2) - pow(py,2) - pow(pz,2) + 
			        pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
				        pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
					        pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2)));

double dMcdyp = (2*((-2*(x - xp)*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) + 
	             (py*(x - xp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	       (px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
	             2*((-2*pow(y - yp,2)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) + 
			          (py*(y - yp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) + 
				           (px*(x - xp) + py*(y - yp) + pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
		            (py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
			          2*((-2*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) + 
				               (py*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				         (pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))))/
        (2.*sqrt(pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
		         pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
			         pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2))) + 
	   (2*((-2*(x - xp)*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) + 
	                (py*(x - xp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	           (px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
		         2*((-2*pow(y - yp,2)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) + 
			              (py*(y - yp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) + 
				               (px*(x - xp) + py*(y - yp) + pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
			        (py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))) + 
				      2*((-2*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2) + 
					           (py*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				             (pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2))))/
	       (2.*sqrt(pow(k,2) - pow(px,2) - pow(py,2) - pow(pz,2) + 
			        pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
				        pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
					        pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2)));

double dMcdzp = (2*(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	       ((pz*(x - xp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
		         (2*(x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2)) + 
	             2*(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
		            ((pz*(y - yp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
			              (2*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2)) + 
			          2*(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				         ((px*(x - xp) + py*(y - yp) + pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) + 
					           (pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
						            (2*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*pow(z - zp,2))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2)))/
        (2.*sqrt(pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
		         pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
			         pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2))) + 
	   (2*(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
	           ((pz*(x - xp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
		             (2*(x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2)) + 
		         2*(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
			        ((pz*(y - yp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
				          (2*(y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2)) + 
				      2*(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)))*
				             ((px*(x - xp) + py*(y - yp) + pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) + 
					               (pz*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)) - 
						                (2*(px*(x - xp) + py*(y - yp) + pz*(z - zp))*pow(z - zp,2))/pow(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2),2)))/
	       (2.*sqrt(pow(k,2) - pow(px,2) - pow(py,2) - pow(pz,2) + 
			        pow(px - ((x - xp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
				        pow(py - ((y - yp)*(px*(x - xp) + py*(y - yp) + pz*(z - zp)))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2) + 
					        pow(pz - ((px*(x - xp) + py*(y - yp) + pz*(z - zp))*(z - zp))/(pow(x - xp,2) + pow(y - yp,2) + pow(z - zp,2)),2)));

double vertex_errsq = 
	cov1(0,0) * dMcdx * dMcdx + cov1(1,1) * dMcdy * dMcdy  + cov1(2,2) * dMcdz * dMcdz + 
	cov2(0,0) * dMcdxp * dMcdxp + cov2(1,1) * dMcdyp * dMcdyp  + cov2(2,2) * dMcdzp * dMcdzp  + 2.* dMcdx *dMcdy * cov1(0,1)  + 2. * dMcdx * dMcdz * cov1(0,2) + 2. * dMcdy * dMcdz * cov1(1,2)  + 2.* dMcdxp *dMcdyp * cov2(0,1)  + 2. * dMcdxp * dMcdzp * cov2(0,2) + 2. * dMcdyp * dMcdzp * cov2(1,2);

double momentum_errsq =
	  dMcdpx * dMcdpx * cov1(3,3) +   dMcdpy * dMcdpy * cov1(4,4) + dMcdpz * dMcdpz * cov1(5,5) + dMcdE * dMcdE * cov1(6,6) + 
        // mom v mom cross terms
	+  2. * dMcdpx * dMcdpy * cov1(3,4) +   2.* dMcdpx * dMcdpz * cov1(3,5) + 2. * dMcdpx * dMcdE * cov1(3,6) + 2. * dMcdpy * dMcdpz * cov1(4,5) + 2. * dMcdpy * dMcdE * cov1(4,6)         + 2. *  dMcdpz * dMcdE * cov1(5,6) +  
	// mom vs positon terms
	2 * dMcdx * dMcdpx *  cov1(0,3) + 2. * dMcdy * dMcdpx *  cov1(1,3)  + 2. * dMcdz * dMcdpx *  cov1(2,3) +
	 2 *dMcdx * dMcdpy *  cov1(0,4) + 2. * dMcdy * dMcdpy *  cov1(1,4)  + 2. * dMcdz * dMcdpy *  cov1(2,4) +
	2*  dMcdx * dMcdpz *  cov1(0,5) + 2. * dMcdy * dMcdpz *  cov1(1,5)  + 2. * dMcdz * dMcdpz *  cov1(2,5) +
	2*  dMcdx * dMcdE *  cov1(0,6) + 2. * dMcdy * dMcdE *  cov1(1,6)  + 2. * dMcdz * dMcdE *  cov1(2,6) ;

std::vector<double> Mcorr_errors;
Mcorr_errors.push_back( sqrt(vertex_errsq) );
Mcorr_errors.push_back( sqrt(vertex_errsq + momentum_errsq) );

return Mcorr_errors;
}

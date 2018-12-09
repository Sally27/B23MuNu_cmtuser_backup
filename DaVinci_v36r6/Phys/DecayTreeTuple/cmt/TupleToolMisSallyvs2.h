#ifndef TUPLETOOLMISSALLYVS2_H
#define TUPLETOOLMISSALLYVS2_H 1

// Include files
// from Gaudi
#include "GaudiAlg/GaudiTool.h"
#include<cmath>
#include "Kernel/IParticleTupleTool.h"            // Interface
#include "Kernel/IDVAlgorithm.h"
#include <Kernel/ILifetimeFitter.h>
#include <Kernel/GetIDVAlgorithm.h>
#include "DecayTreeTupleBase/TupleToolBase.h"
#include "LoKi/LoKi.h"


/** @class TupleToolMisSallyvs2 TupleToolMisSallyvs2.h jborel/TupleToolMisSallyvs2.h
 *
 *
 * \sa DecayTreeTuple
 *
 *  @author Rob Lambert
 *  @date   2009-06-09
 */

//forward declaration otherwise it complains
class IDistanceCalculator;
class IDVAlgorithm;
class ILifetimeFitter;

class TupleToolMisSallyvs2 : public TupleToolBase, virtual public IParticleTupleTool {

public:
  /// Standard constructor
  TupleToolMisSallyvs2( const std::string& type,
		    const std::string& name,
		    const IInterface* parent);

  virtual ~TupleToolMisSallyvs2(){}; ///< Destructor

  virtual StatusCode fill( const LHCb::Particle*
			   , const LHCb::Particle*
			   , const std::string&
			   , Tuples::Tuple& );

  virtual StatusCode initialize();

private:

double step; //used in the estimation of the derivatives
IDVAlgorithm* m_dva;
const IDistanceCalculator* m_dist;
const ILifetimeFitter* m_fit;
const IParticleCombiner* m_combiner;
IParticleTransporter* m_transporter;
std::string m_transporterName;


double taum;
Gaudi::XYZPoint misgetTauDecayVtx(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP);
Gaudi::LorentzVector misgetTauP(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP);
Gaudi::LorentzVector misgetTauP(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint tauSV);
double misgetHolyMass(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP);
double misgetCorMass(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV,  Gaudi::LorentzVector visP);


Gaudi::SymMatrix3x3 misgetTauDecayVtxCov(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP, Gaudi::SymMatrix3x3 covBPV, Gaudi::SymMatrix3x3 covBSV, Gaudi::SymMatrix4x4 covXP, Gaudi::SymMatrix7x7 covMuT);
double misgetHolyMassErr(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP,
    Gaudi::SymMatrix3x3 covBPV, Gaudi::SymMatrix3x3 covBSV, Gaudi::SymMatrix4x4 covXP, Gaudi::SymMatrix7x7 covmuPosP);
Gaudi::SymMatrix4x4 misgetTauPCov(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP,
   Gaudi::SymMatrix3x3 BPVCov, Gaudi::SymMatrix3x3 BSVCov, Gaudi::SymMatrix4x4 XPCov, Gaudi::SymMatrix7x7 PosCov);
Gaudi::Matrix4x3 misgetTauPBSVCov(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP, 
   Gaudi::SymMatrix3x3 covBSV);
double misgetCorMassErr(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector visP, Gaudi::SymMatrix3x3 covBPV,
    Gaudi::SymMatrix3x3 covBSV, Gaudi::SymMatrix4x4 covVisP);
};

double misgetRhoDist(Gaudi::XYZPoint A, Gaudi::XYZPoint B);
double misgetCoord(Gaudi::XYZPoint p, int i);
void missetCoord(Gaudi::XYZPoint& p, int i, double a);

double misgetCoord(Gaudi::XYZVector p, int i);
void missetCoord(Gaudi::XYZVector& p, int i, double a);

double misgetCoord(Gaudi::LorentzVector p, int i);
void missetCoord(Gaudi::LorentzVector& p, int i, double a);

double misgetCoord(Gaudi::XYZPoint pos, Gaudi::LorentzVector p, int i);
void missetCoord(Gaudi::XYZPoint& pos, Gaudi::LorentzVector& p, int i, double a);

#endif

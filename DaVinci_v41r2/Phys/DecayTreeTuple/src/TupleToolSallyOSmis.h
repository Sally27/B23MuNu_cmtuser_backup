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


/** @class TupleToolSallyOSmis TupleToolSallyOSmis.h jborel/TupleToolSallyOSmis.h
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

class TupleToolSallyOSmis : public TupleToolBase, virtual public IParticleTupleTool {

public:
  /// Standard constructor
  TupleToolSallyOSmis( const std::string& type,
		    const std::string& name,
		    const IInterface* parent);

  virtual ~TupleToolSallyOSmis(){}; ///< Destructor

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
Gaudi::XYZPoint getTauDecayVtx(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP);
Gaudi::LorentzVector getTauP(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP);
Gaudi::LorentzVector getTauP(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint tauSV);
double getHolyMass(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP);
double getCorMass(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV,  Gaudi::LorentzVector visP);


Gaudi::SymMatrix3x3 getTauDecayVtxCov(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP, Gaudi::SymMatrix3x3 covBPV, Gaudi::SymMatrix3x3 covBSV, Gaudi::SymMatrix4x4 covXP, Gaudi::SymMatrix7x7 covMuT);
double getHolyMassErr(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP,
    Gaudi::SymMatrix3x3 covBPV, Gaudi::SymMatrix3x3 covBSV, Gaudi::SymMatrix4x4 covXP, Gaudi::SymMatrix7x7 covmuPosP);
Gaudi::SymMatrix4x4 getTauPCov(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP,
   Gaudi::SymMatrix3x3 BPVCov, Gaudi::SymMatrix3x3 BSVCov, Gaudi::SymMatrix4x4 XPCov, Gaudi::SymMatrix7x7 PosCov);
Gaudi::Matrix4x3 getTauPBSVCov(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector XP, Gaudi::XYZPoint muPos, Gaudi::LorentzVector muP, 
   Gaudi::SymMatrix3x3 covBSV);
double getCorMassErr(Gaudi::XYZPoint BPV, Gaudi::XYZPoint BSV, Gaudi::LorentzVector visP, Gaudi::SymMatrix3x3 covBPV,
    Gaudi::SymMatrix3x3 covBSV, Gaudi::SymMatrix4x4 covVisP);


double getRhoDist(Gaudi::XYZPoint A, Gaudi::XYZPoint B);
double getCoord(Gaudi::XYZPoint p, int i);
void setCoord(Gaudi::XYZPoint& p, int i, double a);

double getCoord(Gaudi::XYZVector p, int i);
void setCoord(Gaudi::XYZVector& p, int i, double a);

double getCoord(Gaudi::LorentzVector p, int i);
void setCoord(Gaudi::LorentzVector& p, int i, double a);

double getCoord(Gaudi::XYZPoint pos, Gaudi::LorentzVector p, int i);
void setCoord(Gaudi::XYZPoint& pos, Gaudi::LorentzVector& p, int i, double a);



};

//double getRhoDist(Gaudi::XYZPoint A, Gaudi::XYZPoint B);
//double getCoord(Gaudi::XYZPoint p, int i);
//void setCoord(Gaudi::XYZPoint& p, int i, double a);

//double getCoord(Gaudi::XYZVector p, int i);
//void setCoord(Gaudi::XYZVector& p, int i, double a);

//double getCoord(Gaudi::LorentzVector p, int i);
//void setCoord(Gaudi::LorentzVector& p, int i, double a);

//double getCoord(Gaudi::XYZPoint pos, Gaudi::LorentzVector p, int i);
//void setCoord(Gaudi::XYZPoint& pos, Gaudi::LorentzVector& p, int i, double a);

#endif

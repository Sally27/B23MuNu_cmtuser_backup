// $Id: TupleToolSwimmingInfo.h,v 1.4 2010-03-04 14:02:03 xieyu Exp $
#ifndef VVGRA_TUPLETOOLSWIMMINGINFO_H
#define VVGRA_TUPLETOOLSWIMMINGINFO_H 1

// Include files
// from Gaudi
#include "DecayTreeTupleBase/TupleToolBase.h"
#include "Kernel/IParticleTupleTool.h"            // Interface
#include "Relations/Relations.h"
#include "Event/SwimmingReport.h"
#include "Event/TurningPoint.h"

/** @class TupleToolSwimmingInfo TupleToolSwimmingInfo.h
 *
 *  authors : V.V. Gligorov & R. Aaij
 *
 *  Tool to save swimming information
 *
 *  @data   2011-10-15
 */
class TupleToolSwimmingInfo : public TupleToolBase, virtual public IParticleTupleTool {
public:
  /// Standard constructor
  TupleToolSwimmingInfo( const std::string& type,
                const std::string& name,
                const IInterface* parent);

  virtual ~TupleToolSwimmingInfo(){}; ///< Destructor

  virtual StatusCode fill( const LHCb::Particle*, const LHCb::Particle*
                           , const std::string&, Tuples::Tuple& );

private:
  std::string m_swimRelTableLoc;
  std::string m_swimRepsStage;  
  bool m_useExtraLoc;
  std::string m_extraLoc; 

  typedef LHCb::Relation2D<LHCb::Particle, LHCb::SwimmingReport> P2TPRelation;

  typedef std::vector<LHCb::TurningPoint> tPoints; 
};
#endif // VVGRA_TUPLETOOLSWIMMINGINFO_H

#ifndef TUPLETOOLL0PTLUT_H
#define TUPLETOOLL0PTLUT_H 1

// Include files
// from Gaudi
#include "DecayTreeTupleBase/TupleToolBase.h"
#include "Kernel/IParticleTupleTool.h"            // Interface
#include "MuonDet/DeMuonDetector.h"
#include "GaudiKernel/VectorMap.h"
class TupleToolL0PtLUT : public TupleToolBase, virtual public IParticleTupleTool {
public:
  /// Standard constructor
  TupleToolL0PtLUT( const std::string& type,
                const std::string& name,
                const IInterface* parent);

  virtual ~TupleToolL0PtLUT(){}; ///< Destructor

  virtual StatusCode fill( const LHCb::Particle*, const LHCb::Particle*
                           , const std::string&, Tuples::Tuple& );

  virtual StatusCode initialize(); 
  
  std::map< std::string, double > m_map;
  std::string m_LUTlocation;

private:

};
#endif // TUPLETOOLL0PTLUT_H

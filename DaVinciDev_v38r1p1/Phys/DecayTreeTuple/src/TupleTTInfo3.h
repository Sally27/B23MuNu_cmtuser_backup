#ifndef TUPLETTINFO_H
#define TUPLETTINFO_H 1

// Include files 
// from DaVinci.

#include "DecayTreeTupleBase/TupleToolBase.h"
#include "Kernel/IParticleTupleTool.h"
//#include "Kernel/IDVAlgorithm.h"
//#include "Kernel/IParticleDescendants.h"
//#include "Kernel/IDistanceCalculator.h"
//#include "Kernel/IVertexFit.h"


#include <map> 

/** @class TupleTupleTTInfo3 TupleTupleTTInfo3.h
 *  
 *
 *  @author Thomas Blake
 *  @date   2013-05-10
 */

class TupleTTInfo3 : public TupleToolBase, virtual public IParticleTupleTool 
{
public: 
  /// Standard constructor
    
  TupleTTInfo3( const std::string& type,
               const std::string& name,
               const IInterface* parent );
  
  virtual ~TupleTTInfo3( ); ///< Destructor

  virtual StatusCode initialize();    ///< Algorithm initialization
  
  virtual StatusCode finalize  ();    ///< Algorithm finalization
  
  virtual StatusCode fill( const LHCb::Particle*, 
                           const LHCb::Particle*, 
                           const std::string&, 
                           Tuples::Tuple& );
  
protected:

  bool hasTrack( const LHCb::Particle* P ) const ;  
};
#endif // BUKMMFIT_H

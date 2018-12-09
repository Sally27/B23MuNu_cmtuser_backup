// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dOdOdIx86_64mIslc6mIgcc48mIoptdIdictdIPIDPerfToolsdIPIDPerfToolsDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/home/hep/ss4314/cmtuser/Urania_v4r0/PIDCalib/PIDPerfTools/dict/PIDPerfToolsDict.h"

// Header files passed via #pragma extra_include

namespace {
  void TriggerDictionaryInitialization_PIDPerfToolsDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/hep/ss4314/cmtuser/Urania_v4r0/PIDCalib/PIDPerfTools",
"/home/hep/ss4314/cmtuser/Urania_v4r0/PIDCalib/PIDPerfTools/src",
"/home/hep/ss4314/cmtuser/Urania_v4r0/InstallArea/x86_64-slc6-gcc48-opt/include",
"/cvmfs/lhcb.cern.ch/lib/lhcb/URANIA/URANIA_v4r0/InstallArea/x86_64-slc6-gcc48-opt/include",
"/cvmfs/lhcb.cern.ch/lib/lhcb/GAUDI/GAUDI_v26r4/InstallArea/x86_64-slc6-gcc48-opt/include",
"/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCGCMT/LCGCMT_79/LCG_Settings/../../../LCG_79/ROOT/6.04.02/x86_64-slc6-gcc48-opt/include",
"/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCGCMT/LCGCMT_79/LCG_Settings/../../../LCG_79/ROOT/6.04.02/x86_64-slc6-gcc48-opt/include",
"/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCGCMT/LCGCMT_79/LCG_Settings/../../../LCG_79/Boost/1.55.0_python2.7/x86_64-slc6-gcc48-opt/include/boost-1_55",
"/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCGCMT/LCGCMT_79/LCG_Settings/../../../LCG_79/xrootd/3.3.6/x86_64-slc6-gcc48-opt/include",
"/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCGCMT/LCGCMT_79/LCG_Platforms/src",
"/cvmfs/lhcb.cern.ch/lib/lcg/releases/ROOT/6.04.02-a6f71/x86_64-slc6-gcc48-opt/include",
"/home/hep/ss4314/cmtuser/Urania_v4r0/PIDCalib/PIDPerfTools/cmt/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/TrackDataSet.h")))  TrackDataSet;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/GenericDataSet.h")))  GenericDataSet;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/TrackDataSet.h")))  DataBinCuts;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/TrackDataSet.h")))  PIDResult;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/TrackDataSet.h")))  PIDTable;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/TrackDataSet.h")))  PIDCrossTable;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/TrkPIDParams.h")))  TrkPIDParams;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/MultiTrackCalibTool.h")))  MultiTrackCalibTool;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$string")))  allocator;
}
template <class T> class __attribute__((annotate("$clingAutoload$PIDPerfTools/TrackDataSet.h")))  PerfCalculator;

template <class T> class __attribute__((annotate("$clingAutoload$PIDPerfTools/WeightDataSetTool.h")))  WeightDataSetTool;

class __attribute__((annotate("$clingAutoload$PIDPerfTools/TrackDataSet.h")))  RooBinning;
namespace std{template <class _CharT> struct __attribute__((annotate("$clingAutoload$string")))  char_traits;
}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#ifdef __MINGW32__
  #undef __MINGW32__
#endif

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef _GNU_SOURCE
  #define _GNU_SOURCE 1
#endif
#ifndef GAUDI_V20_COMPAT
  #define GAUDI_V20_COMPAT 1
#endif
#ifndef BOOST_FILESYSTEM_VERSION
  #define BOOST_FILESYSTEM_VERSION 3
#endif
#ifndef BOOST_SPIRIT_USE_PHOENIX_V3
  #define BOOST_SPIRIT_USE_PHOENIX_V3 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// $Id: $
#ifndef DICT_PIDPERFTOOLSDICT_H 
#define DICT_PIDPERFTOOLSDICT_H 1
// Include files

/** @file PIDPerfToolsDict.h dict/PIDPerfToolsDict.h
 *  
 *
 *  @author Andrew POWELL
 *  @date   2010-10-08
 */

#include "PIDPerfTools/TrackDataSet.h"
//#include "PIDPerfTools/EvtTrackDataSet.h"
//#include "PIDPerfTools/RICHTrackDataSet.h"
//#include "PIDPerfTools/MUONTrackDataSet.h"
//#include "PIDPerfTools/PIDTrackDataSet.h"
//#include "PIDPerfTools/LHCbPIDTrackDataSet.h"
#include "PIDPerfTools/GenericDataSet.h"
#include "PIDPerfTools/DataBinCuts.h"
#include "PIDPerfTools/PerfCalculator.h"
#include "PIDPerfTools/PIDResult.h"
#include "PIDPerfTools/PerfCalculator.h"
#include "PIDPerfTools/MultiPerfCalculator.h"
#include "PIDPerfTools/PIDTable.h"
#include "PIDPerfTools/PIDCrossTable.h"
#include "PIDPerfTools/TrkPIDParams.h"
#include "PIDPerfTools/MultiTrackCalibTool.h"
#include "PIDPerfTools/WeightDataSetTool.h"

namespace
{
  struct _Instantiations 
  {
    PerfCalculator<TrackDataSet>                    a;
    //    PerfCalculator<EvtTrackDataSet>                 b;
    //PerfCalculator<RICHTrackDataSet>                c;
    //PerfCalculator<MUONTrackDataSet>                d;
    //PerfCalculator<PIDTrackDataSet>                 e;
    //PerfCalculator<LHCbPIDTrackDataSet>             ee;
    PerfCalculator<GenericDataSet>                  eee;
    std::pair<std::string, RooBinning*>             f;
    std::list<std::pair<std::string, RooBinning*> > g;
    std::vector<RooBinning*>                        h;
    PIDResult::Container                            i;
    std::vector<std::string>                        j;
    WeightDataSetTool<TrackDataSet>                 k;
    //    WeightDataSetTool<EvtTrackDataSet>              l;
    //WeightDataSetTool<RICHTrackDataSet>             m;
    //WeightDataSetTool<MUONTrackDataSet>             n;
    //WeightDataSetTool<PIDTrackDataSet>              o;
    std::pair<std::string, std::string>             r;
    std::vector<std::pair<std::string, std::string> > s;
  };
}

#endif // DICT_PIDPERFTOOLSDICT_H

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"", payloadCode, "@",
"DataBinCuts", payloadCode, "@",
"GenericDataSet", payloadCode, "@",
"MultiTrackCalibTool", payloadCode, "@",
"PIDCrossTable", payloadCode, "@",
"PIDResult", payloadCode, "@",
"PIDTable", payloadCode, "@",
"PerfCalculator<GenericDataSet>", payloadCode, "@",
"PerfCalculator<TrackDataSet>", payloadCode, "@",
"TrackDataSet", payloadCode, "@",
"TrkPIDParams", payloadCode, "@",
"WeightDataSetTool<TrackDataSet>", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("PIDPerfToolsDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_PIDPerfToolsDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_PIDPerfToolsDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_PIDPerfToolsDict() {
  TriggerDictionaryInitialization_PIDPerfToolsDict_Impl();
}

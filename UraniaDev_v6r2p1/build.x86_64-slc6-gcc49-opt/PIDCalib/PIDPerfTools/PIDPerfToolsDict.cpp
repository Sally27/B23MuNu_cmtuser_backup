// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME PIDPerfToolsDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
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
#include "/home/hep/ss4314/cmtuser/UraniaDev_v6r2p1/PIDCalib/PIDPerfTools/dict/PIDPerfToolsDict.h"

// Header files passed via #pragma extra_include

namespace {
  void TriggerDictionaryInitialization_PIDPerfToolsDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/hep/ss4314/cmtuser/UraniaDev_v6r2p1/PIDCalib/PIDPerfTools",
"/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_87/ROOT/6.08.02/x86_64-slc6-gcc49-opt/include",
"/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_87/Boost/1.62.0/x86_64-slc6-gcc49-opt/include/boost-1_62",
"/home/hep/ss4314/cmtuser/UraniaDev_v6r2p1/build.x86_64-slc6-gcc49-opt/include",
"/cvmfs/lhcb.cern.ch/lib/lhcb/URANIA/URANIA_v6r2p1/InstallArea/x86_64-slc6-gcc49-opt/include",
"/cvmfs/lhcb.cern.ch/lib/lcg/releases/ROOT/6.08.02-99084/x86_64-slc6-gcc49-opt/include",
"/home/hep/ss4314/cmtuser/UraniaDev_v6r2p1/build.x86_64-slc6-gcc49-opt/PIDCalib/PIDPerfTools/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "PIDPerfToolsDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace std{template <class _CharT> struct __attribute__((annotate("$clingAutoload$bits/char_traits.h")))  __attribute__((annotate("$clingAutoload$string")))  char_traits;
}
namespace std{template <typename > class __attribute__((annotate("$clingAutoload$bits/memoryfwd.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$PIDPerfTools/PerfCalculator.h")))  __attribute__((annotate("$clingAutoload$PIDPerfTools/TrackDataSet.h")))  PIDResult;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/DataBinCuts.h")))  __attribute__((annotate("$clingAutoload$PIDPerfTools/TrackDataSet.h")))  DataBinCuts;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/PIDTable.h")))  __attribute__((annotate("$clingAutoload$PIDPerfTools/TrackDataSet.h")))  PIDTable;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/PIDCrossTable.h")))  __attribute__((annotate("$clingAutoload$PIDPerfTools/TrackDataSet.h")))  PIDCrossTable;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/TrackDataSet.h")))  TrackDataSet;
template <class T> class __attribute__((annotate("$clingAutoload$PIDPerfTools/PerfCalculator.h")))  __attribute__((annotate("$clingAutoload$PIDPerfTools/TrackDataSet.h")))  PerfCalculator;

class __attribute__((annotate("$clingAutoload$PIDPerfTools/GenericDataSet.h")))  GenericDataSet;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/TrkPIDParams.h")))  TrkPIDParams;
class __attribute__((annotate("$clingAutoload$PIDPerfTools/MultiTrackCalibTool.h")))  MultiTrackCalibTool;
template <class T> class __attribute__((annotate("$clingAutoload$PIDPerfTools/WeightDataSetTool.h")))  WeightDataSetTool;

)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "PIDPerfToolsDict dictionary payload"
#ifdef __MINGW32__
  #undef __MINGW32__
#endif
#ifdef _Instantiations
  #undef _Instantiations
#endif

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef _Instantiations
  #define _Instantiations PIDPerfTools_Instantiations
#endif
#ifndef _GNU_SOURCE
  #define _GNU_SOURCE 1
#endif
#ifndef unix
  #define unix 1
#endif
#ifndef f2cFortran
  #define f2cFortran 1
#endif
#ifndef linux
  #define linux 1
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
#ifndef PACKAGE_NAME
  #define PACKAGE_NAME "PIDPerfTools"
#endif
#ifndef PACKAGE_VERSION
  #define PACKAGE_VERSION "v8r2"
#endif
#ifndef NDEBUG
  #define NDEBUG 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#ifndef DICT_PIDPERFTOOLSDICT_H
#define DICT_PIDPERFTOOLSDICT_H 1
// Include files

/** @file PIDPerfToolsDict.h dict/PIDPerfToolsDict.h
 *
 *
 *  @author Andrew POWELL
 *  @date   2010-10-08
 */

#if defined(__clang__) || defined(__CLING__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winconsistent-missing-override"
#elif defined(__GNUC__) && __GNUC__ >= 5
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#endif

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

#if defined(__clang__) || defined(__CLING__)
#pragma clang diagnostic pop
#elif defined(__GNUC__) && __GNUC__ >= 5
#pragma GCC diagnostic pop
#endif

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

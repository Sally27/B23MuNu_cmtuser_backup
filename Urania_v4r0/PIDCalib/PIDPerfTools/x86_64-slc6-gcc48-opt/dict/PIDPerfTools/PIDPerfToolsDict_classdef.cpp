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

namespace ROOT {
   static void *new_TrackDataSet(void *p = 0);
   static void *newArray_TrackDataSet(Long_t size, void *p);
   static void delete_TrackDataSet(void *p);
   static void deleteArray_TrackDataSet(void *p);
   static void destruct_TrackDataSet(void *p);
   static void streamer_TrackDataSet(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TrackDataSet*)
   {
      ::TrackDataSet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TrackDataSet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TrackDataSet", ::TrackDataSet::Class_Version(), "PIDPerfTools/TrackDataSet.h", 25,
                  typeid(::TrackDataSet), DefineBehavior(ptr, ptr),
                  &::TrackDataSet::Dictionary, isa_proxy, 16,
                  sizeof(::TrackDataSet) );
      instance.SetNew(&new_TrackDataSet);
      instance.SetNewArray(&newArray_TrackDataSet);
      instance.SetDelete(&delete_TrackDataSet);
      instance.SetDeleteArray(&deleteArray_TrackDataSet);
      instance.SetDestructor(&destruct_TrackDataSet);
      instance.SetStreamerFunc(&streamer_TrackDataSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TrackDataSet*)
   {
      return GenerateInitInstanceLocal((::TrackDataSet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TrackDataSet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GenericDataSet(void *p = 0);
   static void *newArray_GenericDataSet(Long_t size, void *p);
   static void delete_GenericDataSet(void *p);
   static void deleteArray_GenericDataSet(void *p);
   static void destruct_GenericDataSet(void *p);
   static void streamer_GenericDataSet(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GenericDataSet*)
   {
      ::GenericDataSet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GenericDataSet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GenericDataSet", ::GenericDataSet::Class_Version(), "PIDPerfTools/GenericDataSet.h", 32,
                  typeid(::GenericDataSet), DefineBehavior(ptr, ptr),
                  &::GenericDataSet::Dictionary, isa_proxy, 16,
                  sizeof(::GenericDataSet) );
      instance.SetNew(&new_GenericDataSet);
      instance.SetNewArray(&newArray_GenericDataSet);
      instance.SetDelete(&delete_GenericDataSet);
      instance.SetDeleteArray(&deleteArray_GenericDataSet);
      instance.SetDestructor(&destruct_GenericDataSet);
      instance.SetStreamerFunc(&streamer_GenericDataSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GenericDataSet*)
   {
      return GenerateInitInstanceLocal((::GenericDataSet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::GenericDataSet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_DataBinCuts(void *p = 0);
   static void *newArray_DataBinCuts(Long_t size, void *p);
   static void delete_DataBinCuts(void *p);
   static void deleteArray_DataBinCuts(void *p);
   static void destruct_DataBinCuts(void *p);
   static void streamer_DataBinCuts(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DataBinCuts*)
   {
      ::DataBinCuts *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::DataBinCuts >(0);
      static ::ROOT::TGenericClassInfo 
         instance("DataBinCuts", ::DataBinCuts::Class_Version(), "PIDPerfTools/DataBinCuts.h", 22,
                  typeid(::DataBinCuts), DefineBehavior(ptr, ptr),
                  &::DataBinCuts::Dictionary, isa_proxy, 16,
                  sizeof(::DataBinCuts) );
      instance.SetNew(&new_DataBinCuts);
      instance.SetNewArray(&newArray_DataBinCuts);
      instance.SetDelete(&delete_DataBinCuts);
      instance.SetDeleteArray(&deleteArray_DataBinCuts);
      instance.SetDestructor(&destruct_DataBinCuts);
      instance.SetStreamerFunc(&streamer_DataBinCuts);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DataBinCuts*)
   {
      return GenerateInitInstanceLocal((::DataBinCuts*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::DataBinCuts*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *PIDResult_Dictionary();
   static void PIDResult_TClassManip(TClass*);
   static void *new_PIDResult(void *p = 0);
   static void *newArray_PIDResult(Long_t size, void *p);
   static void delete_PIDResult(void *p);
   static void deleteArray_PIDResult(void *p);
   static void destruct_PIDResult(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PIDResult*)
   {
      ::PIDResult *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::PIDResult));
      static ::ROOT::TGenericClassInfo 
         instance("PIDResult", "PIDPerfTools/PIDResult.h", 15,
                  typeid(::PIDResult), DefineBehavior(ptr, ptr),
                  &PIDResult_Dictionary, isa_proxy, 0,
                  sizeof(::PIDResult) );
      instance.SetNew(&new_PIDResult);
      instance.SetNewArray(&newArray_PIDResult);
      instance.SetDelete(&delete_PIDResult);
      instance.SetDeleteArray(&deleteArray_PIDResult);
      instance.SetDestructor(&destruct_PIDResult);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PIDResult*)
   {
      return GenerateInitInstanceLocal((::PIDResult*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PIDResult*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *PIDResult_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::PIDResult*)0x0)->GetClass();
      PIDResult_TClassManip(theClass);
   return theClass;
   }

   static void PIDResult_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *PIDTable_Dictionary();
   static void PIDTable_TClassManip(TClass*);
   static void *new_PIDTable(void *p = 0);
   static void *newArray_PIDTable(Long_t size, void *p);
   static void delete_PIDTable(void *p);
   static void deleteArray_PIDTable(void *p);
   static void destruct_PIDTable(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PIDTable*)
   {
      ::PIDTable *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::PIDTable));
      static ::ROOT::TGenericClassInfo 
         instance("PIDTable", "PIDPerfTools/PIDTable.h", 25,
                  typeid(::PIDTable), DefineBehavior(ptr, ptr),
                  &PIDTable_Dictionary, isa_proxy, 0,
                  sizeof(::PIDTable) );
      instance.SetNew(&new_PIDTable);
      instance.SetNewArray(&newArray_PIDTable);
      instance.SetDelete(&delete_PIDTable);
      instance.SetDeleteArray(&deleteArray_PIDTable);
      instance.SetDestructor(&destruct_PIDTable);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PIDTable*)
   {
      return GenerateInitInstanceLocal((::PIDTable*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PIDTable*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *PIDTable_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::PIDTable*)0x0)->GetClass();
      PIDTable_TClassManip(theClass);
   return theClass;
   }

   static void PIDTable_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *PIDCrossTable_Dictionary();
   static void PIDCrossTable_TClassManip(TClass*);
   static void *new_PIDCrossTable(void *p = 0);
   static void *newArray_PIDCrossTable(Long_t size, void *p);
   static void delete_PIDCrossTable(void *p);
   static void deleteArray_PIDCrossTable(void *p);
   static void destruct_PIDCrossTable(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PIDCrossTable*)
   {
      ::PIDCrossTable *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::PIDCrossTable));
      static ::ROOT::TGenericClassInfo 
         instance("PIDCrossTable", "PIDPerfTools/PIDCrossTable.h", 21,
                  typeid(::PIDCrossTable), DefineBehavior(ptr, ptr),
                  &PIDCrossTable_Dictionary, isa_proxy, 0,
                  sizeof(::PIDCrossTable) );
      instance.SetNew(&new_PIDCrossTable);
      instance.SetNewArray(&newArray_PIDCrossTable);
      instance.SetDelete(&delete_PIDCrossTable);
      instance.SetDeleteArray(&deleteArray_PIDCrossTable);
      instance.SetDestructor(&destruct_PIDCrossTable);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PIDCrossTable*)
   {
      return GenerateInitInstanceLocal((::PIDCrossTable*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PIDCrossTable*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *PIDCrossTable_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::PIDCrossTable*)0x0)->GetClass();
      PIDCrossTable_TClassManip(theClass);
   return theClass;
   }

   static void PIDCrossTable_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TrkPIDParams_Dictionary();
   static void TrkPIDParams_TClassManip(TClass*);
   static void *new_TrkPIDParams(void *p = 0);
   static void *newArray_TrkPIDParams(Long_t size, void *p);
   static void delete_TrkPIDParams(void *p);
   static void deleteArray_TrkPIDParams(void *p);
   static void destruct_TrkPIDParams(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TrkPIDParams*)
   {
      ::TrkPIDParams *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TrkPIDParams));
      static ::ROOT::TGenericClassInfo 
         instance("TrkPIDParams", "PIDPerfTools/TrkPIDParams.h", 11,
                  typeid(::TrkPIDParams), DefineBehavior(ptr, ptr),
                  &TrkPIDParams_Dictionary, isa_proxy, 0,
                  sizeof(::TrkPIDParams) );
      instance.SetNew(&new_TrkPIDParams);
      instance.SetNewArray(&newArray_TrkPIDParams);
      instance.SetDelete(&delete_TrkPIDParams);
      instance.SetDeleteArray(&deleteArray_TrkPIDParams);
      instance.SetDestructor(&destruct_TrkPIDParams);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TrkPIDParams*)
   {
      return GenerateInitInstanceLocal((::TrkPIDParams*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TrkPIDParams*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TrkPIDParams_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TrkPIDParams*)0x0)->GetClass();
      TrkPIDParams_TClassManip(theClass);
   return theClass;
   }

   static void TrkPIDParams_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MultiTrackCalibTool_Dictionary();
   static void MultiTrackCalibTool_TClassManip(TClass*);
   static void delete_MultiTrackCalibTool(void *p);
   static void deleteArray_MultiTrackCalibTool(void *p);
   static void destruct_MultiTrackCalibTool(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MultiTrackCalibTool*)
   {
      ::MultiTrackCalibTool *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MultiTrackCalibTool));
      static ::ROOT::TGenericClassInfo 
         instance("MultiTrackCalibTool", "PIDPerfTools/MultiTrackCalibTool.h", 23,
                  typeid(::MultiTrackCalibTool), DefineBehavior(ptr, ptr),
                  &MultiTrackCalibTool_Dictionary, isa_proxy, 0,
                  sizeof(::MultiTrackCalibTool) );
      instance.SetDelete(&delete_MultiTrackCalibTool);
      instance.SetDeleteArray(&deleteArray_MultiTrackCalibTool);
      instance.SetDestructor(&destruct_MultiTrackCalibTool);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MultiTrackCalibTool*)
   {
      return GenerateInitInstanceLocal((::MultiTrackCalibTool*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MultiTrackCalibTool*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MultiTrackCalibTool_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MultiTrackCalibTool*)0x0)->GetClass();
      MultiTrackCalibTool_TClassManip(theClass);
   return theClass;
   }

   static void MultiTrackCalibTool_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *PerfCalculatorlEGenericDataSetgR_Dictionary();
   static void PerfCalculatorlEGenericDataSetgR_TClassManip(TClass*);
   static void *new_PerfCalculatorlEGenericDataSetgR(void *p = 0);
   static void *newArray_PerfCalculatorlEGenericDataSetgR(Long_t size, void *p);
   static void delete_PerfCalculatorlEGenericDataSetgR(void *p);
   static void deleteArray_PerfCalculatorlEGenericDataSetgR(void *p);
   static void destruct_PerfCalculatorlEGenericDataSetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PerfCalculator<GenericDataSet>*)
   {
      ::PerfCalculator<GenericDataSet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::PerfCalculator<GenericDataSet>));
      static ::ROOT::TGenericClassInfo 
         instance("PerfCalculator<GenericDataSet>", "PIDPerfTools/PerfCalculator.h", 28,
                  typeid(::PerfCalculator<GenericDataSet>), DefineBehavior(ptr, ptr),
                  &PerfCalculatorlEGenericDataSetgR_Dictionary, isa_proxy, 0,
                  sizeof(::PerfCalculator<GenericDataSet>) );
      instance.SetNew(&new_PerfCalculatorlEGenericDataSetgR);
      instance.SetNewArray(&newArray_PerfCalculatorlEGenericDataSetgR);
      instance.SetDelete(&delete_PerfCalculatorlEGenericDataSetgR);
      instance.SetDeleteArray(&deleteArray_PerfCalculatorlEGenericDataSetgR);
      instance.SetDestructor(&destruct_PerfCalculatorlEGenericDataSetgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PerfCalculator<GenericDataSet>*)
   {
      return GenerateInitInstanceLocal((::PerfCalculator<GenericDataSet>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PerfCalculator<GenericDataSet>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *PerfCalculatorlEGenericDataSetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::PerfCalculator<GenericDataSet>*)0x0)->GetClass();
      PerfCalculatorlEGenericDataSetgR_TClassManip(theClass);
   return theClass;
   }

   static void PerfCalculatorlEGenericDataSetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *PerfCalculatorlETrackDataSetgR_Dictionary();
   static void PerfCalculatorlETrackDataSetgR_TClassManip(TClass*);
   static void *new_PerfCalculatorlETrackDataSetgR(void *p = 0);
   static void *newArray_PerfCalculatorlETrackDataSetgR(Long_t size, void *p);
   static void delete_PerfCalculatorlETrackDataSetgR(void *p);
   static void deleteArray_PerfCalculatorlETrackDataSetgR(void *p);
   static void destruct_PerfCalculatorlETrackDataSetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PerfCalculator<TrackDataSet>*)
   {
      ::PerfCalculator<TrackDataSet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::PerfCalculator<TrackDataSet>));
      static ::ROOT::TGenericClassInfo 
         instance("PerfCalculator<TrackDataSet>", "PIDPerfTools/PerfCalculator.h", 28,
                  typeid(::PerfCalculator<TrackDataSet>), DefineBehavior(ptr, ptr),
                  &PerfCalculatorlETrackDataSetgR_Dictionary, isa_proxy, 0,
                  sizeof(::PerfCalculator<TrackDataSet>) );
      instance.SetNew(&new_PerfCalculatorlETrackDataSetgR);
      instance.SetNewArray(&newArray_PerfCalculatorlETrackDataSetgR);
      instance.SetDelete(&delete_PerfCalculatorlETrackDataSetgR);
      instance.SetDeleteArray(&deleteArray_PerfCalculatorlETrackDataSetgR);
      instance.SetDestructor(&destruct_PerfCalculatorlETrackDataSetgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PerfCalculator<TrackDataSet>*)
   {
      return GenerateInitInstanceLocal((::PerfCalculator<TrackDataSet>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PerfCalculator<TrackDataSet>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *PerfCalculatorlETrackDataSetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::PerfCalculator<TrackDataSet>*)0x0)->GetClass();
      PerfCalculatorlETrackDataSetgR_TClassManip(theClass);
   return theClass;
   }

   static void PerfCalculatorlETrackDataSetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *WeightDataSetToollETrackDataSetgR_Dictionary();
   static void WeightDataSetToollETrackDataSetgR_TClassManip(TClass*);
   static void *new_WeightDataSetToollETrackDataSetgR(void *p = 0);
   static void *newArray_WeightDataSetToollETrackDataSetgR(Long_t size, void *p);
   static void delete_WeightDataSetToollETrackDataSetgR(void *p);
   static void deleteArray_WeightDataSetToollETrackDataSetgR(void *p);
   static void destruct_WeightDataSetToollETrackDataSetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WeightDataSetTool<TrackDataSet>*)
   {
      ::WeightDataSetTool<TrackDataSet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::WeightDataSetTool<TrackDataSet>));
      static ::ROOT::TGenericClassInfo 
         instance("WeightDataSetTool<TrackDataSet>", "PIDPerfTools/WeightDataSetTool.h", 21,
                  typeid(::WeightDataSetTool<TrackDataSet>), DefineBehavior(ptr, ptr),
                  &WeightDataSetToollETrackDataSetgR_Dictionary, isa_proxy, 0,
                  sizeof(::WeightDataSetTool<TrackDataSet>) );
      instance.SetNew(&new_WeightDataSetToollETrackDataSetgR);
      instance.SetNewArray(&newArray_WeightDataSetToollETrackDataSetgR);
      instance.SetDelete(&delete_WeightDataSetToollETrackDataSetgR);
      instance.SetDeleteArray(&deleteArray_WeightDataSetToollETrackDataSetgR);
      instance.SetDestructor(&destruct_WeightDataSetToollETrackDataSetgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WeightDataSetTool<TrackDataSet>*)
   {
      return GenerateInitInstanceLocal((::WeightDataSetTool<TrackDataSet>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::WeightDataSetTool<TrackDataSet>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *WeightDataSetToollETrackDataSetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::WeightDataSetTool<TrackDataSet>*)0x0)->GetClass();
      WeightDataSetToollETrackDataSetgR_TClassManip(theClass);
   return theClass;
   }

   static void WeightDataSetToollETrackDataSetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *pairlEstringcORooBinningmUgR_Dictionary();
   static void pairlEstringcORooBinningmUgR_TClassManip(TClass*);
   static void *new_pairlEstringcORooBinningmUgR(void *p = 0);
   static void *newArray_pairlEstringcORooBinningmUgR(Long_t size, void *p);
   static void delete_pairlEstringcORooBinningmUgR(void *p);
   static void deleteArray_pairlEstringcORooBinningmUgR(void *p);
   static void destruct_pairlEstringcORooBinningmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const pair<string,RooBinning*>*)
   {
      pair<string,RooBinning*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(pair<string,RooBinning*>));
      static ::ROOT::TGenericClassInfo 
         instance("pair<string,RooBinning*>", "string", 96,
                  typeid(pair<string,RooBinning*>), DefineBehavior(ptr, ptr),
                  &pairlEstringcORooBinningmUgR_Dictionary, isa_proxy, 0,
                  sizeof(pair<string,RooBinning*>) );
      instance.SetNew(&new_pairlEstringcORooBinningmUgR);
      instance.SetNewArray(&newArray_pairlEstringcORooBinningmUgR);
      instance.SetDelete(&delete_pairlEstringcORooBinningmUgR);
      instance.SetDeleteArray(&deleteArray_pairlEstringcORooBinningmUgR);
      instance.SetDestructor(&destruct_pairlEstringcORooBinningmUgR);

      ::ROOT::AddClassAlternate("pair<string,RooBinning*>","pair<std::string,RooBinning*>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const pair<string,RooBinning*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *pairlEstringcORooBinningmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const pair<string,RooBinning*>*)0x0)->GetClass();
      pairlEstringcORooBinningmUgR_TClassManip(theClass);
   return theClass;
   }

   static void pairlEstringcORooBinningmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *pairlEstringcOstringgR_Dictionary();
   static void pairlEstringcOstringgR_TClassManip(TClass*);
   static void *new_pairlEstringcOstringgR(void *p = 0);
   static void *newArray_pairlEstringcOstringgR(Long_t size, void *p);
   static void delete_pairlEstringcOstringgR(void *p);
   static void deleteArray_pairlEstringcOstringgR(void *p);
   static void destruct_pairlEstringcOstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const pair<string,string>*)
   {
      pair<string,string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(pair<string,string>));
      static ::ROOT::TGenericClassInfo 
         instance("pair<string,string>", "string", 96,
                  typeid(pair<string,string>), DefineBehavior(ptr, ptr),
                  &pairlEstringcOstringgR_Dictionary, isa_proxy, 0,
                  sizeof(pair<string,string>) );
      instance.SetNew(&new_pairlEstringcOstringgR);
      instance.SetNewArray(&newArray_pairlEstringcOstringgR);
      instance.SetDelete(&delete_pairlEstringcOstringgR);
      instance.SetDeleteArray(&deleteArray_pairlEstringcOstringgR);
      instance.SetDestructor(&destruct_pairlEstringcOstringgR);

      ::ROOT::AddClassAlternate("pair<string,string>","pair<std::string,std::string>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const pair<string,string>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *pairlEstringcOstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const pair<string,string>*)0x0)->GetClass();
      pairlEstringcOstringgR_TClassManip(theClass);
   return theClass;
   }

   static void pairlEstringcOstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

#include "TInterpreter.h"
//______________________________________________________________________________
atomic_TClass_ptr TrackDataSet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TrackDataSet::Class_Name()
{
   return "TrackDataSet";
}

//______________________________________________________________________________
const char *TrackDataSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TrackDataSet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TrackDataSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TrackDataSet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TrackDataSet::Dictionary()
{
   gInterpreter->EnableAutoLoading();
   gInterpreter->AutoLoad("TrackDataSet");
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TrackDataSet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TrackDataSet::Class()
{
   Dictionary();
   return fgIsA;
}

#include "TInterpreter.h"
//______________________________________________________________________________
atomic_TClass_ptr GenericDataSet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GenericDataSet::Class_Name()
{
   return "GenericDataSet";
}

//______________________________________________________________________________
const char *GenericDataSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GenericDataSet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GenericDataSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GenericDataSet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GenericDataSet::Dictionary()
{
   gInterpreter->EnableAutoLoading();
   gInterpreter->AutoLoad("GenericDataSet");
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GenericDataSet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GenericDataSet::Class()
{
   Dictionary();
   return fgIsA;
}

#include "TInterpreter.h"
//______________________________________________________________________________
atomic_TClass_ptr DataBinCuts::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *DataBinCuts::Class_Name()
{
   return "DataBinCuts";
}

//______________________________________________________________________________
const char *DataBinCuts::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DataBinCuts*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int DataBinCuts::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DataBinCuts*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *DataBinCuts::Dictionary()
{
   gInterpreter->EnableAutoLoading();
   gInterpreter->AutoLoad("DataBinCuts");
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DataBinCuts*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *DataBinCuts::Class()
{
   Dictionary();
   return fgIsA;
}

//______________________________________________________________________________
void TrackDataSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class TrackDataSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TrackDataSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(TrackDataSet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TrackDataSet(void *p) {
      return  p ? new(p) ::TrackDataSet : new ::TrackDataSet;
   }
   static void *newArray_TrackDataSet(Long_t nElements, void *p) {
      return p ? new(p) ::TrackDataSet[nElements] : new ::TrackDataSet[nElements];
   }
   // Wrapper around operator delete
   static void delete_TrackDataSet(void *p) {
      delete ((::TrackDataSet*)p);
   }
   static void deleteArray_TrackDataSet(void *p) {
      delete [] ((::TrackDataSet*)p);
   }
   static void destruct_TrackDataSet(void *p) {
      typedef ::TrackDataSet current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TrackDataSet(TBuffer &buf, void *obj) {
      ((::TrackDataSet*)obj)->::TrackDataSet::Streamer(buf);
   }
} // end of namespace ROOT for class ::TrackDataSet

//______________________________________________________________________________
void GenericDataSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class GenericDataSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GenericDataSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(GenericDataSet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GenericDataSet(void *p) {
      return  p ? new(p) ::GenericDataSet : new ::GenericDataSet;
   }
   static void *newArray_GenericDataSet(Long_t nElements, void *p) {
      return p ? new(p) ::GenericDataSet[nElements] : new ::GenericDataSet[nElements];
   }
   // Wrapper around operator delete
   static void delete_GenericDataSet(void *p) {
      delete ((::GenericDataSet*)p);
   }
   static void deleteArray_GenericDataSet(void *p) {
      delete [] ((::GenericDataSet*)p);
   }
   static void destruct_GenericDataSet(void *p) {
      typedef ::GenericDataSet current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_GenericDataSet(TBuffer &buf, void *obj) {
      ((::GenericDataSet*)obj)->::GenericDataSet::Streamer(buf);
   }
} // end of namespace ROOT for class ::GenericDataSet

//______________________________________________________________________________
void DataBinCuts::Streamer(TBuffer &R__b)
{
   // Stream an object of class DataBinCuts.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(DataBinCuts::Class(),this);
   } else {
      R__b.WriteClassBuffer(DataBinCuts::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_DataBinCuts(void *p) {
      return  p ? new(p) ::DataBinCuts : new ::DataBinCuts;
   }
   static void *newArray_DataBinCuts(Long_t nElements, void *p) {
      return p ? new(p) ::DataBinCuts[nElements] : new ::DataBinCuts[nElements];
   }
   // Wrapper around operator delete
   static void delete_DataBinCuts(void *p) {
      delete ((::DataBinCuts*)p);
   }
   static void deleteArray_DataBinCuts(void *p) {
      delete [] ((::DataBinCuts*)p);
   }
   static void destruct_DataBinCuts(void *p) {
      typedef ::DataBinCuts current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_DataBinCuts(TBuffer &buf, void *obj) {
      ((::DataBinCuts*)obj)->::DataBinCuts::Streamer(buf);
   }
} // end of namespace ROOT for class ::DataBinCuts

namespace ROOT {
   // Wrappers around operator new
   static void *new_PIDResult(void *p) {
      return  p ? new(p) ::PIDResult : new ::PIDResult;
   }
   static void *newArray_PIDResult(Long_t nElements, void *p) {
      return p ? new(p) ::PIDResult[nElements] : new ::PIDResult[nElements];
   }
   // Wrapper around operator delete
   static void delete_PIDResult(void *p) {
      delete ((::PIDResult*)p);
   }
   static void deleteArray_PIDResult(void *p) {
      delete [] ((::PIDResult*)p);
   }
   static void destruct_PIDResult(void *p) {
      typedef ::PIDResult current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PIDResult

namespace ROOT {
   // Wrappers around operator new
   static void *new_PIDTable(void *p) {
      return  p ? new(p) ::PIDTable : new ::PIDTable;
   }
   static void *newArray_PIDTable(Long_t nElements, void *p) {
      return p ? new(p) ::PIDTable[nElements] : new ::PIDTable[nElements];
   }
   // Wrapper around operator delete
   static void delete_PIDTable(void *p) {
      delete ((::PIDTable*)p);
   }
   static void deleteArray_PIDTable(void *p) {
      delete [] ((::PIDTable*)p);
   }
   static void destruct_PIDTable(void *p) {
      typedef ::PIDTable current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PIDTable

namespace ROOT {
   // Wrappers around operator new
   static void *new_PIDCrossTable(void *p) {
      return  p ? new(p) ::PIDCrossTable : new ::PIDCrossTable;
   }
   static void *newArray_PIDCrossTable(Long_t nElements, void *p) {
      return p ? new(p) ::PIDCrossTable[nElements] : new ::PIDCrossTable[nElements];
   }
   // Wrapper around operator delete
   static void delete_PIDCrossTable(void *p) {
      delete ((::PIDCrossTable*)p);
   }
   static void deleteArray_PIDCrossTable(void *p) {
      delete [] ((::PIDCrossTable*)p);
   }
   static void destruct_PIDCrossTable(void *p) {
      typedef ::PIDCrossTable current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PIDCrossTable

namespace ROOT {
   // Wrappers around operator new
   static void *new_TrkPIDParams(void *p) {
      return  p ? new(p) ::TrkPIDParams : new ::TrkPIDParams;
   }
   static void *newArray_TrkPIDParams(Long_t nElements, void *p) {
      return p ? new(p) ::TrkPIDParams[nElements] : new ::TrkPIDParams[nElements];
   }
   // Wrapper around operator delete
   static void delete_TrkPIDParams(void *p) {
      delete ((::TrkPIDParams*)p);
   }
   static void deleteArray_TrkPIDParams(void *p) {
      delete [] ((::TrkPIDParams*)p);
   }
   static void destruct_TrkPIDParams(void *p) {
      typedef ::TrkPIDParams current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TrkPIDParams

namespace ROOT {
   // Wrapper around operator delete
   static void delete_MultiTrackCalibTool(void *p) {
      delete ((::MultiTrackCalibTool*)p);
   }
   static void deleteArray_MultiTrackCalibTool(void *p) {
      delete [] ((::MultiTrackCalibTool*)p);
   }
   static void destruct_MultiTrackCalibTool(void *p) {
      typedef ::MultiTrackCalibTool current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MultiTrackCalibTool

namespace ROOT {
   // Wrappers around operator new
   static void *new_PerfCalculatorlEGenericDataSetgR(void *p) {
      return  p ? new(p) ::PerfCalculator<GenericDataSet> : new ::PerfCalculator<GenericDataSet>;
   }
   static void *newArray_PerfCalculatorlEGenericDataSetgR(Long_t nElements, void *p) {
      return p ? new(p) ::PerfCalculator<GenericDataSet>[nElements] : new ::PerfCalculator<GenericDataSet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_PerfCalculatorlEGenericDataSetgR(void *p) {
      delete ((::PerfCalculator<GenericDataSet>*)p);
   }
   static void deleteArray_PerfCalculatorlEGenericDataSetgR(void *p) {
      delete [] ((::PerfCalculator<GenericDataSet>*)p);
   }
   static void destruct_PerfCalculatorlEGenericDataSetgR(void *p) {
      typedef ::PerfCalculator<GenericDataSet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PerfCalculator<GenericDataSet>

namespace ROOT {
   // Wrappers around operator new
   static void *new_PerfCalculatorlETrackDataSetgR(void *p) {
      return  p ? new(p) ::PerfCalculator<TrackDataSet> : new ::PerfCalculator<TrackDataSet>;
   }
   static void *newArray_PerfCalculatorlETrackDataSetgR(Long_t nElements, void *p) {
      return p ? new(p) ::PerfCalculator<TrackDataSet>[nElements] : new ::PerfCalculator<TrackDataSet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_PerfCalculatorlETrackDataSetgR(void *p) {
      delete ((::PerfCalculator<TrackDataSet>*)p);
   }
   static void deleteArray_PerfCalculatorlETrackDataSetgR(void *p) {
      delete [] ((::PerfCalculator<TrackDataSet>*)p);
   }
   static void destruct_PerfCalculatorlETrackDataSetgR(void *p) {
      typedef ::PerfCalculator<TrackDataSet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PerfCalculator<TrackDataSet>

namespace ROOT {
   // Wrappers around operator new
   static void *new_WeightDataSetToollETrackDataSetgR(void *p) {
      return  p ? new(p) ::WeightDataSetTool<TrackDataSet> : new ::WeightDataSetTool<TrackDataSet>;
   }
   static void *newArray_WeightDataSetToollETrackDataSetgR(Long_t nElements, void *p) {
      return p ? new(p) ::WeightDataSetTool<TrackDataSet>[nElements] : new ::WeightDataSetTool<TrackDataSet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_WeightDataSetToollETrackDataSetgR(void *p) {
      delete ((::WeightDataSetTool<TrackDataSet>*)p);
   }
   static void deleteArray_WeightDataSetToollETrackDataSetgR(void *p) {
      delete [] ((::WeightDataSetTool<TrackDataSet>*)p);
   }
   static void destruct_WeightDataSetToollETrackDataSetgR(void *p) {
      typedef ::WeightDataSetTool<TrackDataSet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::WeightDataSetTool<TrackDataSet>

namespace ROOT {
   // Wrappers around operator new
   static void *new_pairlEstringcORooBinningmUgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) pair<string,RooBinning*> : new pair<string,RooBinning*>;
   }
   static void *newArray_pairlEstringcORooBinningmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) pair<string,RooBinning*>[nElements] : new pair<string,RooBinning*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_pairlEstringcORooBinningmUgR(void *p) {
      delete ((pair<string,RooBinning*>*)p);
   }
   static void deleteArray_pairlEstringcORooBinningmUgR(void *p) {
      delete [] ((pair<string,RooBinning*>*)p);
   }
   static void destruct_pairlEstringcORooBinningmUgR(void *p) {
      typedef pair<string,RooBinning*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class pair<string,RooBinning*>

namespace ROOT {
   // Wrappers around operator new
   static void *new_pairlEstringcOstringgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) pair<string,string> : new pair<string,string>;
   }
   static void *newArray_pairlEstringcOstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) pair<string,string>[nElements] : new pair<string,string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_pairlEstringcOstringgR(void *p) {
      delete ((pair<string,string>*)p);
   }
   static void deleteArray_pairlEstringcOstringgR(void *p) {
      delete [] ((pair<string,string>*)p);
   }
   static void destruct_pairlEstringcOstringgR(void *p) {
      typedef pair<string,string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class pair<string,string>

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = 0);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "vector", 210,
                  typeid(vector<string>), DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<string>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<string>*)0x0)->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete ((vector<string>*)p);
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] ((vector<string>*)p);
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<string>

namespace ROOT {
   static TClass *vectorlEpairlEstringcOstringgRsPgR_Dictionary();
   static void vectorlEpairlEstringcOstringgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEpairlEstringcOstringgRsPgR(void *p = 0);
   static void *newArray_vectorlEpairlEstringcOstringgRsPgR(Long_t size, void *p);
   static void delete_vectorlEpairlEstringcOstringgRsPgR(void *p);
   static void deleteArray_vectorlEpairlEstringcOstringgRsPgR(void *p);
   static void destruct_vectorlEpairlEstringcOstringgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<pair<string,string> >*)
   {
      vector<pair<string,string> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<pair<string,string> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<pair<string,string> >", -2, "vector", 210,
                  typeid(vector<pair<string,string> >), DefineBehavior(ptr, ptr),
                  &vectorlEpairlEstringcOstringgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<pair<string,string> >) );
      instance.SetNew(&new_vectorlEpairlEstringcOstringgRsPgR);
      instance.SetNewArray(&newArray_vectorlEpairlEstringcOstringgRsPgR);
      instance.SetDelete(&delete_vectorlEpairlEstringcOstringgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEpairlEstringcOstringgRsPgR);
      instance.SetDestructor(&destruct_vectorlEpairlEstringcOstringgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<pair<string,string> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<pair<string,string> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEpairlEstringcOstringgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<pair<string,string> >*)0x0)->GetClass();
      vectorlEpairlEstringcOstringgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEpairlEstringcOstringgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEpairlEstringcOstringgRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<pair<string,string> > : new vector<pair<string,string> >;
   }
   static void *newArray_vectorlEpairlEstringcOstringgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<pair<string,string> >[nElements] : new vector<pair<string,string> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEpairlEstringcOstringgRsPgR(void *p) {
      delete ((vector<pair<string,string> >*)p);
   }
   static void deleteArray_vectorlEpairlEstringcOstringgRsPgR(void *p) {
      delete [] ((vector<pair<string,string> >*)p);
   }
   static void destruct_vectorlEpairlEstringcOstringgRsPgR(void *p) {
      typedef vector<pair<string,string> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<pair<string,string> >

namespace ROOT {
   static TClass *vectorlERooBinningmUgR_Dictionary();
   static void vectorlERooBinningmUgR_TClassManip(TClass*);
   static void *new_vectorlERooBinningmUgR(void *p = 0);
   static void *newArray_vectorlERooBinningmUgR(Long_t size, void *p);
   static void delete_vectorlERooBinningmUgR(void *p);
   static void deleteArray_vectorlERooBinningmUgR(void *p);
   static void destruct_vectorlERooBinningmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<RooBinning*>*)
   {
      vector<RooBinning*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<RooBinning*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<RooBinning*>", -2, "vector", 210,
                  typeid(vector<RooBinning*>), DefineBehavior(ptr, ptr),
                  &vectorlERooBinningmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<RooBinning*>) );
      instance.SetNew(&new_vectorlERooBinningmUgR);
      instance.SetNewArray(&newArray_vectorlERooBinningmUgR);
      instance.SetDelete(&delete_vectorlERooBinningmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlERooBinningmUgR);
      instance.SetDestructor(&destruct_vectorlERooBinningmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<RooBinning*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<RooBinning*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlERooBinningmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<RooBinning*>*)0x0)->GetClass();
      vectorlERooBinningmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlERooBinningmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlERooBinningmUgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<RooBinning*> : new vector<RooBinning*>;
   }
   static void *newArray_vectorlERooBinningmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<RooBinning*>[nElements] : new vector<RooBinning*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlERooBinningmUgR(void *p) {
      delete ((vector<RooBinning*>*)p);
   }
   static void deleteArray_vectorlERooBinningmUgR(void *p) {
      delete [] ((vector<RooBinning*>*)p);
   }
   static void destruct_vectorlERooBinningmUgR(void *p) {
      typedef vector<RooBinning*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<RooBinning*>

namespace ROOT {
   static TClass *vectorlEPIDResultgR_Dictionary();
   static void vectorlEPIDResultgR_TClassManip(TClass*);
   static void *new_vectorlEPIDResultgR(void *p = 0);
   static void *newArray_vectorlEPIDResultgR(Long_t size, void *p);
   static void delete_vectorlEPIDResultgR(void *p);
   static void deleteArray_vectorlEPIDResultgR(void *p);
   static void destruct_vectorlEPIDResultgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<PIDResult>*)
   {
      vector<PIDResult> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<PIDResult>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<PIDResult>", -2, "vector", 210,
                  typeid(vector<PIDResult>), DefineBehavior(ptr, ptr),
                  &vectorlEPIDResultgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<PIDResult>) );
      instance.SetNew(&new_vectorlEPIDResultgR);
      instance.SetNewArray(&newArray_vectorlEPIDResultgR);
      instance.SetDelete(&delete_vectorlEPIDResultgR);
      instance.SetDeleteArray(&deleteArray_vectorlEPIDResultgR);
      instance.SetDestructor(&destruct_vectorlEPIDResultgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<PIDResult> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<PIDResult>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPIDResultgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<PIDResult>*)0x0)->GetClass();
      vectorlEPIDResultgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPIDResultgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPIDResultgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<PIDResult> : new vector<PIDResult>;
   }
   static void *newArray_vectorlEPIDResultgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<PIDResult>[nElements] : new vector<PIDResult>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPIDResultgR(void *p) {
      delete ((vector<PIDResult>*)p);
   }
   static void deleteArray_vectorlEPIDResultgR(void *p) {
      delete [] ((vector<PIDResult>*)p);
   }
   static void destruct_vectorlEPIDResultgR(void *p) {
      typedef vector<PIDResult> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<PIDResult>

namespace ROOT {
   static TClass *listlEpairlEstringcORooBinningmUgRsPgR_Dictionary();
   static void listlEpairlEstringcORooBinningmUgRsPgR_TClassManip(TClass*);
   static void *new_listlEpairlEstringcORooBinningmUgRsPgR(void *p = 0);
   static void *newArray_listlEpairlEstringcORooBinningmUgRsPgR(Long_t size, void *p);
   static void delete_listlEpairlEstringcORooBinningmUgRsPgR(void *p);
   static void deleteArray_listlEpairlEstringcORooBinningmUgRsPgR(void *p);
   static void destruct_listlEpairlEstringcORooBinningmUgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const list<pair<string,RooBinning*> >*)
   {
      list<pair<string,RooBinning*> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(list<pair<string,RooBinning*> >));
      static ::ROOT::TGenericClassInfo 
         instance("list<pair<string,RooBinning*> >", -2, "list", 438,
                  typeid(list<pair<string,RooBinning*> >), DefineBehavior(ptr, ptr),
                  &listlEpairlEstringcORooBinningmUgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(list<pair<string,RooBinning*> >) );
      instance.SetNew(&new_listlEpairlEstringcORooBinningmUgRsPgR);
      instance.SetNewArray(&newArray_listlEpairlEstringcORooBinningmUgRsPgR);
      instance.SetDelete(&delete_listlEpairlEstringcORooBinningmUgRsPgR);
      instance.SetDeleteArray(&deleteArray_listlEpairlEstringcORooBinningmUgRsPgR);
      instance.SetDestructor(&destruct_listlEpairlEstringcORooBinningmUgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< list<pair<string,RooBinning*> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const list<pair<string,RooBinning*> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *listlEpairlEstringcORooBinningmUgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const list<pair<string,RooBinning*> >*)0x0)->GetClass();
      listlEpairlEstringcORooBinningmUgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void listlEpairlEstringcORooBinningmUgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_listlEpairlEstringcORooBinningmUgRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) list<pair<string,RooBinning*> > : new list<pair<string,RooBinning*> >;
   }
   static void *newArray_listlEpairlEstringcORooBinningmUgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) list<pair<string,RooBinning*> >[nElements] : new list<pair<string,RooBinning*> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_listlEpairlEstringcORooBinningmUgRsPgR(void *p) {
      delete ((list<pair<string,RooBinning*> >*)p);
   }
   static void deleteArray_listlEpairlEstringcORooBinningmUgRsPgR(void *p) {
      delete [] ((list<pair<string,RooBinning*> >*)p);
   }
   static void destruct_listlEpairlEstringcORooBinningmUgRsPgR(void *p) {
      typedef list<pair<string,RooBinning*> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class list<pair<string,RooBinning*> >


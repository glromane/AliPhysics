#ifndef  __ALIJETCORRELWRITER_H__
#define  __ALIJETCORRELWRITER_H__
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice     */
/* $Id:  $ */

//______________________________________________________
// Class for output (histograms) definition and filling.
//-- Author: Paul Constantin

#include "AliJetCorrelSelector.h"
#include "AliJetCorrelMaker.h"

class AliJetCorrelWriter : public TObject {
  
 public:
  AliJetCorrelWriter();
  ~AliJetCorrelWriter();    
  void Init(AliJetCorrelSelector * const s, AliJetCorrelMaker * const m);
  
  void CreateGeneric(TList* histosContainer);
  void CreateQA(TList *histosContainer);
  void CreateCorrelations(TList* histosContainer);
  
  void FillGlobal(Float_t cent, Float_t zvert);
  void FillSingleHistos(UInt_t cBin, CorrelList_t * const TriggList, UInt_t tIdx,
			CorrelList_t * const AssocList, UInt_t aIdx);
  void FillTrackQA(AliESDtrack * const track, UInt_t idx);
  void FillParentNtuple(CorrelList_t * const ParentList);
  void FillCorrelations(FillType_t fTyp, UInt_t iCorr, UInt_t cBin, UInt_t vBin,
			CorrelParticle_t * const Trigger, CorrelParticle_t * const Associated);
  
  Float_t DeltaPhi(Float_t phi1, Float_t phi2);
  void  ShowStats();
  
 private:
  AliJetCorrelSelector *fSelector;  // user selection object
  AliJetCorrelMaker *fMaker;        // correlation maker object
  TString hname, htit;              // histos name&title
  Bool_t fRecoTrigg;                // is trigger reconstructed
  TRandom2 fRndm;                   // random number generator
  UInt_t fNumReal[kMAXNUMCORREL][kMAXCENTBIN], fNumMix[kMAXNUMCORREL][kMAXCENTBIN]; // counters
  
  // Output Histograms
  TH1F *hBinsCentr, *hBinsZVert, *hCentr, *hZVert;          // binning histos
  TH2F *hTrkITSQA[2], *hTrkTPCQA[2], *hTrkVTXQA[2];         // track QA histos
  TH3F *hTrkProx[2][kMAXCENTBIN];                           // distance at TPC entrance between tracks
  TH3F *hTriggAcc[kMAXNUMCORREL];                           // trigg PhixEta acceptance
  TH3F *hAssocAcc[kMAXNUMCORREL];                           // assoc PhixEta acceptance
  TNtuple *ntuParent;                                       // reconstructed parent ntuple
  TH1F *hTriggPt[kMAXNUMCORREL][kMAXCENTBIN];               // trigg Pt
  TH1F *hAssocPt[kMAXNUMCORREL][kMAXCENTBIN];               // assoc Pt
  TH3F *hReal[kMAXNUMCORREL][kMAXCENTBIN][kMAXVERTBIN][kMAXTRIGBIN][kMAXASSOBIN];  // real DPhixDEtaxPout
  TH3F *hMix[kMAXNUMCORREL][kMAXCENTBIN][kMAXVERTBIN][kMAXTRIGBIN][kMAXASSOBIN];   // mix  DPhixDEtaxPout
  
  // disable (make private) copy constructor and assignment operator:
  AliJetCorrelWriter(const AliJetCorrelWriter&);
  AliJetCorrelWriter& operator=(const AliJetCorrelWriter&);
  
  ClassDef(AliJetCorrelWriter, 1);
};

#endif

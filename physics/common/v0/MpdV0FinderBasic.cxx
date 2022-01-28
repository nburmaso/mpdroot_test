/*
 * MpdV0FinderBasic.cxx
 *
 *  Created on: 16 gru 2021
 *      Author: Daniel Wielanek
 *      E-mail: daniel.wielanek at pw.edu.pl
 *      Warsaw University of Technology, Faculty of Physics
 *      JINR,  Laboratory of High Energy Physics
 */

#include "MpdV0FinderBasic.h"

#include <FairRootManager.h>
#include <TClonesArray.h>

#include "FairLogger.h"
#include "MpdEvent.h"
#include "MpdV0CandidateCut.h"
#include "MpdV0DaughterCut.h"

MpdV0FinderBasic::MpdV0FinderBasic(Int_t pidMom, Int_t pidFirstDau, Int_t pidSecDau)
   : FairTask(), fInit(kFALSE), fWrite(kFALSE), fFirstV0(kFALSE), fPidDauPos(pidSecDau), fPidDauNeg(pidFirstDau),
     fPidV0(pidMom), fFormat(EFormat::kDst), fMpdEvent(nullptr), fMiniEvents(nullptr), fMiniTracks(nullptr),
     fV0s(nullptr), fPositiveDaughterCut(nullptr), fNegativeDaughterCut(nullptr), fCandicateCut(nullptr)
{
}

MpdV0FinderBasic::~MpdV0FinderBasic()
{
   if (fPositiveDaughterCut) delete fPositiveDaughterCut;
   if (fNegativeDaughterCut) delete fNegativeDaughterCut;
   if (fCandicateCut) delete fCandicateCut;
}

MpdV0FinderBasic::MpdV0FinderBasic(const MpdV0FinderBasic &other)
   : FairTask(), fInit(kFALSE), fWrite(other.fWrite), fFirstV0(other.fFirstV0), fPidDauPos(other.fPidDauPos),
     fPidDauNeg(other.fPidDauNeg), fPidV0(other.fPidV0), fFormat(other.fFormat), fMpdEvent(nullptr),
     fMiniEvents(nullptr), fMiniTracks(nullptr), fV0s(nullptr), fPositiveDaughterCut(nullptr),
     fNegativeDaughterCut(nullptr), fCandicateCut(nullptr)
{
   if (other.fPositiveDaughterCut) {
      fPositiveDaughterCut = (MpdV0DaughterCut *)other.fPositiveDaughterCut->Clone();
   }
   if (other.fNegativeDaughterCut) {
      fNegativeDaughterCut = (MpdV0DaughterCut *)other.fNegativeDaughterCut->Clone();
   }
   if (other.fCandicateCut) {
      fCandicateCut = (MpdV0CandidateCut *)other.fCandicateCut->Clone();
   }
}

void MpdV0FinderBasic::Exec(Option_t *option)
{
   if (fFirstV0) fV0s->Clear();
   fPositiveDaughters.clear();
   fNegativeDaughters.clear();
   switch (fFormat) {
   case EFormat::kDst: ExecDst(option); break;
   case EFormat::kMiniDst: ExecMiniDst(option);
   }
}

InitStatus MpdV0FinderBasic::Init()
{
   if (fInit) {
      LOG(ERROR) << "Task already initalized";
      return kSUCCESS;
   }
   FairRootManager *mngr = FairRootManager::Instance();
   fMpdEvent             = (MpdEvent *)mngr->GetObject("MPDEvent.");
   fMiniEvents           = (TClonesArray *)mngr->GetObject("Event");
   fMiniTracks           = (TClonesArray *)mngr->GetObject("Track");
   if (mngr->GetObject("MpdV0")) {
      fFirstV0 = kFALSE;
      fV0s     = (TClonesArray *)mngr->GetObject("MpdV0");
   } else {
      fFirstV0 = kTRUE;
      fV0s     = new TClonesArray("MpdV0Track");
   }

   mngr->Register("MpdV0", "V0", fV0s, fWrite);
   if (!fPositiveDaughterCut) {
      LOG(ERROR) << "Lack cut for first daughter";
      return kFATAL;
   }
   if (!fNegativeDaughterCut) {
      LOG(ERROR) << "Lack cut for second daughter";
      return kFATAL;
   }
   if (!fCandicateCut) {
      LOG(ERROR) << "Lack candicate cut";
      return kFATAL;
   }
   if (fMpdEvent) {
      fFormat = EFormat::kDst;
   } else if (fMiniEvents) {
      fFormat = EFormat::kMiniDst;
   } else {
      LOG(ERROR) << "No MpdEvent/MiniDstEvent in tree";
      return kFATAL;
   }
   fInit = kTRUE;
   return kSUCCESS;
}

void MpdV0FinderBasic::SetPositiveDaughterCut(const MpdV0DaughterCut &cut)
{
   if (fPositiveDaughterCut) delete fPositiveDaughterCut;
   fPositiveDaughterCut = (MpdV0DaughterCut *)cut.Clone();
}

void MpdV0FinderBasic::SetNegativeDaughterCut(const MpdV0DaughterCut &cut)
{
   if (fNegativeDaughterCut) delete fNegativeDaughterCut;
   fNegativeDaughterCut = (MpdV0DaughterCut *)cut.Clone();
}

void MpdV0FinderBasic::SetCandicateCut(const MpdV0CandidateCut &cut)
{
   if (fCandicateCut) delete fCandicateCut;
   fCandicateCut = (MpdV0CandidateCut *)cut.Clone();
}

MpdV0FinderBasic &MpdV0FinderBasic::operator=(const MpdV0FinderBasic &other)
{
   if (this == &other) return *this;
   fFormat     = other.fFormat;
   fMpdEvent   = nullptr;
   fMiniEvents = nullptr;
   fMiniTracks = nullptr;
   if (fV0s) {
      delete fV0s;
      fV0s = nullptr;
   }
   fInit                = kFALSE;
   fWrite               = other.fInit;
   fPositiveDaughterCut = nullptr;
   fNegativeDaughterCut = nullptr;
   fCandicateCut        = nullptr;
   if (other.fPositiveDaughterCut) {
      fPositiveDaughterCut = (MpdV0DaughterCut *)other.fPositiveDaughterCut->Clone();
   }
   if (other.fNegativeDaughterCut) {
      fNegativeDaughterCut = (MpdV0DaughterCut *)other.fNegativeDaughterCut->Clone();
   }
   if (other.fCandicateCut) {
      fCandicateCut = (MpdV0CandidateCut *)other.fCandicateCut->Clone();
   }
   return *this;
}

/*
 * MpdBasicTrackCut.cxx
 *
 *  Created on: 29 wrz 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

#include "MpdBasicTrackCut.h"

#include <TString.h>

#include "MpdDcaMonitor.h"
#include "MpdKinMonitor.h"
#include "MpdTofMonitor.h"
#include "MpdTpcMonitor.h"
#include "NicaStdString.h"
#include "NicaTrackChargeCut.h"
#include "NicaTrackDCACut.h"
#include "NicaTrackEtaCut.h"
#include "NicaTrackPtCut.h"
#include "NicaTrackTpcToFCut.h"

MpdBasicTrackCut::MpdBasicTrackCut()
    : fToFMonitor(nullptr),
      fKinMonitor(nullptr),
      fDCAMonitor(nullptr),
      fTpcMonitor(nullptr) {
  AddCut(NicaTrackDCACut());
  AddCut(NicaTrackEtaCut());
  AddCut(NicaTrackPtCut());
  AddCut(NicaTrackChargeCut());
  AddCut(NicaTrackTpcToFCut());
}

MpdTofMonitor* MpdBasicTrackCut::GetTofMonitor() const { return fToFMonitor; }

MpdKinMonitor* MpdBasicTrackCut::GetKinMonitor() const { return fKinMonitor; }

MpdDcaMonitor* MpdBasicTrackCut::GetDCAMonitor() const { return fDCAMonitor; }

MpdTpcMonitor* MpdBasicTrackCut::GetTpcMonitor() const { return fTpcMonitor; }

NicaTrackDCACut* MpdBasicTrackCut::GetDCACut() const {
  return (NicaTrackDCACut*)CutAt(0);
}

void MpdBasicTrackCut::CreateMonitors(TString opt) {
  if (NicaStd::FindParam(opt, "dca") && fDCAMonitor == nullptr) {
    fDCAMonitor = new MpdDcaMonitor();
    AddRawCutMonitor(fDCAMonitor);
  }
  if (NicaStd::FindParam(opt, "tof") && fToFMonitor == nullptr) {
    fToFMonitor = new MpdTofMonitor();
    AddRawCutMonitor(fToFMonitor);
  }
  if (NicaStd::FindParam(opt, "tpc") && fTpcMonitor == nullptr) {
    fTpcMonitor = new MpdTpcMonitor();
    AddRawCutMonitor(fTpcMonitor);
  }
  if (NicaStd::FindParam(opt, "kin") && fKinMonitor == nullptr) {
    fKinMonitor = new MpdKinMonitor();
    AddRawCutMonitor(fKinMonitor);
  }
}

NicaTrackEtaCut* MpdBasicTrackCut::GetEtaCut() const {
  return (NicaTrackEtaCut*)CutAt(1);
}

NicaTrackPtCut* MpdBasicTrackCut::GetPtCut() const {
  return (NicaTrackPtCut*)CutAt(2);
}

NicaTrackChargeCut* MpdBasicTrackCut::GetChargeCut() const {
  return (NicaTrackChargeCut*)CutAt(3);
}

NicaTrackTpcToFCut* MpdBasicTrackCut::GetTpcTofCut() const {
  return (NicaTrackTpcToFCut*)CutAt(4);
}

MpdBasicTrackCut::~MpdBasicTrackCut() {}

/*
 * NicaMpdMiniDstFullEvent.cxx
 *
 *  Created on: 17 kwi 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "NicaMpdMiniDstFullEvent.h"
#include "NicaMpdMiniDstEvent.h"
#include "NicaMpdMiniDstMcEvent.h"
#include "NicaMpdMiniDstTrack.h"

NicaMpdMiniDstFullEvent::NicaMpdMiniDstFullEvent():NicaComplexEvent(new NicaMpdMiniDstEvent(), new NicaMpdMiniDstMcEvent()) {
}

void NicaMpdMiniDstFullEvent::OnlyPrimary() {
    ((NicaMpdMiniDstEvent*)fRealEvent)->OnlyPrimary();
}

void NicaMpdMiniDstFullEvent::OnlyGlobal() {
    ((NicaMpdMiniDstEvent*)fRealEvent)->OnlyGlobal();
}

void NicaMpdMiniDstFullEvent::Update() {
    fImgEvent->Update();
    fRealEvent->Update();
    NicaEvent::ShallowCopyEvent(fRealEvent);
    fTracks->Clear();
    fTotalTracksNo = fRealEvent->GetTotalTrackNo();
    fTracks->ExpandCreateFast(fTotalTracksNo);
    for(int i=0;i<fTotalTracksNo;i++){
        NicaComplexTrack *track = (NicaComplexTrack*)fTracks->UncheckedAt(i);
        track->SetRealTrack(fRealEvent->GetTrack(i));
        MpdMiniTrack *mpd_track = (MpdMiniTrack*)track->GetRealTrack()->GetTrackPointer();
        Int_t parent_id = mpd_track->mcTrackIndex();
        track->NicaTrack::CopyData(fRealEvent->GetTrack(i));
        track->SetMatchID(parent_id);
        if(parent_id>=0){
            track->SetImgTrack(fImgEvent->GetTrack(parent_id));
        }else{
            track->SetImgTrack(nullptr);
        }
        track->SetID(i);
    }
}

NicaMpdMiniDstFullEvent::~NicaMpdMiniDstFullEvent() {
    // TODO Auto-generated destructor stub
}


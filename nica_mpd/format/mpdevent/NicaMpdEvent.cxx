/*
 * NicaMpdEvent.cxx
 *
 *  Created on: 28 mar 2017
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "MpdTrack.h"
#include "NicaMpdEvent.h"
#include "NicaMpdTrack.h"
#include "NicaMpdEventInterface.h"

NicaMpdEvent::NicaMpdEvent(const NicaMpdEvent& other) :NicaExpEvent(other){
	if(Source()) CreateSource();
	fMode = other.fMode;
}

void NicaMpdEvent::Update() {
	fTracks->Clear();
	NicaMpdEventInterface *interface = (NicaMpdEventInterface*)fSource;
	MpdEvent *event =(MpdEvent*) interface->GetRawEventPointer();
	fVertex->SetXYZT(event->GetPrimaryVerticesX(), event->GetPrimaryVerticesY(),event->GetPrimaryVerticesZ(),0);
	fVertexError->SetXYZT(event->GetPrimaryVerticesXerr(), event->GetPrimaryVerticesYerr(),event->GetPrimaryVerticesZerr(),0);
	fTotalTracksNo = interface->GetTotalTrackNo();
	fRunInfoId = event->GetRunInfoRunId();
	fMagField->SetXYZ(0,0,event->GetRunInfoMagneticFieldZ());
	TClonesArray *prim = event->GetPrimaryTracks();
	TClonesArray *glob = event->GetGlobalTracks();
	switch(fMode){
	case kAllTracks:{
		fTotalTracksNo  = event->GetEventInfoNofPrimaryTracks()
		+event->GetEventInfoNofGlobalTracks();
		fTracks->ExpandCreateFast(fTotalTracksNo);
		int count = 0;
		for(int i=0;i<event->GetEventInfoNofPrimaryTracks();i++){
			NicaMpdTrack *mpd_track = (NicaMpdTrack*)fTracks->ConstructedAt(count++);
			mpd_track->Update((MpdTrack*)prim->UncheckedAt(i));
			mpd_track->SetEvent(this);
		}
		for(int i=0;i<event->GetEventInfoNofGlobalTracks();i++){
			NicaMpdTrack *mpd_track = (NicaMpdTrack*)fTracks->ConstructedAt(count++);
			mpd_track->Update((MpdTrack*)glob->UncheckedAt(i));
			mpd_track->SetEvent(this);
		}

	}break;
	case kPrimaryTracks:{
		fTotalTracksNo  = event->GetEventInfoNofPrimaryTracks();
		fTracks->ExpandCreateFast(fTotalTracksNo);
		for(int i=0;i<event->GetEventInfoNofPrimaryTracks();i++){
			NicaMpdTrack *mpd_track = (NicaMpdTrack*)fTracks->ConstructedAt(i);
			mpd_track->Update((MpdTrack*)prim->UncheckedAt(i));
			mpd_track->SetEvent(this);
		}
	}break;
	case kGlobalTracks:{
		fTotalTracksNo  = event->GetEventInfoNofGlobalTracks();
		fTracks->ExpandCreateFast(fTotalTracksNo);
		for(int i=0;i<event->GetEventInfoNofGlobalTracks();i++){
			NicaMpdTrack *mpd_track = (NicaMpdTrack*)fTracks->ConstructedAt(i);
			mpd_track->Update((MpdTrack*)glob->UncheckedAt(i));
			mpd_track->SetEvent(this);
		}
	}break;
	}
	fTracks->Compress();
	NicaMpdTrack *mpd_track = (NicaMpdTrack*)fTracks->ConstructedAt(0);
}

void NicaMpdEvent::CreateSource() {
	fSource = new NicaMpdEventInterface();
}

TString NicaMpdEvent::GetFormatName() const{
	switch(fMode){
	case kAllTracks:
		return "MpdEvent";
		break;
	case kPrimaryTracks:
		return "MpdEvent+PrimaryTracks";
		break;
	case kGlobalTracks:
		return "MpdEvent+GlobalTracks";
		break;
	default:
		return "";
		break;
	}
}

void NicaMpdEvent::ShallowCopyTracks(NicaEvent* event) {
	fTracks->Clear();
	fTotalTracksNo = event->GetTotalTrackNo();
	fTracks->ExpandCreateFast(fTotalTracksNo);
	NicaMpdEvent *Event = (NicaMpdEvent*)event;
	for(int i=0;i<fTotalTracksNo;i++){
		NicaMpdTrack *from = (NicaMpdTrack*)Event->fTracks->UncheckedAt(i);
		NicaMpdTrack *to = (NicaMpdTrack*)fTracks->UncheckedAt(i);
		*to = *from;
	}
}

void NicaMpdEvent::ShallowCopyEvent(NicaEvent* event) {
	NicaExpEvent::ShallowCopyEvent(event);
}

void NicaMpdEvent::OnlyPrimary() {
	fMode = kPrimaryTracks;
	if(fSource){
		((NicaMpdEventInterface*)fSource)->OnlyPrimary();
	}
}

void NicaMpdEvent::OnlyGlobal() {
	fMode = kGlobalTracks;
	if(fSource){
		((NicaMpdEventInterface*)fSource)->OnlyGlobal();
	}
}

NicaMpdEvent::~NicaMpdEvent() {
}

NicaMpdEvent::NicaMpdEvent() :NicaExpEvent("NicaMpdTrack"){
	fSource = new NicaMpdEventInterface();
	fMode = kAllTracks;
}


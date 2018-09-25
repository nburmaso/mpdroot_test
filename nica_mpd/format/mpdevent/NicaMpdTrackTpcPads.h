/*
 * NicaMpdTrackTpcPads.h
 *
 *  Created on: 2 lip 2018
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef MPDROOT_NICA_MPD_FORMAT_MPDEVENT_NICAMPDTRACKTPCPADS_H_
#define MPDROOT_NICA_MPD_FORMAT_MPDEVENT_NICAMPDTRACKTPCPADS_H_

#include "NicaMpdTrack.h"
#include "NicaTpcSectorGeo.h"

class NicaMpdTrackTpcPads : public NicaMpdTrack{
	Float_t fPaths[53];
	Int_t fPadID[53];
	Short_t fMaxPads;
	Short_t fPadsNo;
	NicaTpcSectorGeo *fSec = NULL;
public:
	NicaMpdTrackTpcPads();
	NicaMpdTrackTpcPads(const NicaMpdTrackTpcPads &other);
	NicaMpdTrackTpcPads &operator=(const NicaMpdTrackTpcPads &other);
	Int_t GetPadsNo()const{return fPadsNo;};
	Int_t GetMaxPadsNo()const{return fMaxPads;};
	Float_t GetPathAt(Int_t lay)const{return fPaths[lay];};
	Float_t GetPhi(Int_t lay)const;
	Float_t GetR(Int_t lay)const;
	Float_t GetZ(Int_t lay)const;
	Int_t GetPadID(Int_t lay)const{return fPadID[lay];};
	virtual void Update(MpdTrack* track);
	virtual void CopyData(NicaTrack *other);
	virtual ~NicaMpdTrackTpcPads();
	ClassDef(NicaMpdTrackTpcPads,1)
};

#endif /* MPDROOT_NICA_MPD_FORMAT_MPDEVENT_NICAMPDTRACKTPCPADS_H_ */
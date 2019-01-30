/*
 * MpdPairDeltaDCA.cxx
 *
 *  Created on: 9 lis 2018
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "MpdPairDeltaDCA.h"
#include "NicaMpdTrack.h"

MpdPairDeltaDCA::MpdPairDeltaDCA() : NicaTwoTrackCut(3){
	SetUnitName("#DeltaDCA_{xy} [cm]",DeltaDCAxy());
	SetUnitName("#DeltaDCA_{z} [cm]",DeltaDCAz());
	SetUnitName("#DeltaDCA [cm]",DeltaDCA());
	SetMinMax(0, 1E+6, DeltaDCAxy());
	SetMinMax(0, 1E+6, DeltaDCAz());
	SetMinMax(0 ,1E+6, DeltaDCA());
}

Bool_t MpdPairDeltaDCA::Pass(NicaTwoTrack* pair) {
	NicaMpdTrack *tr1 = (NicaMpdTrack*)pair->GetTrack1();
	NicaMpdTrack *tr2 = (NicaMpdTrack*)pair->GetTrack2();
	TVector3 *dca1 = tr1->GetDCA();
	TVector3 *dca2 = tr2->GetDCA();
	TVector3 vx1 = tr1->GetEvent()->GetVertex()->Vect();
	TVector3 vx2 = tr2->GetEvent()->GetVertex()->Vect();
	TVector3 deltaDCA = *dca1 - *dca2-vx1+vx2;
	SetValue(deltaDCA.Pt(),DeltaDCAxy());
	SetValue(TMath::Abs(deltaDCA.Z()),DeltaDCAz());
	SetValue(deltaDCA.Mag(),DeltaDCA());
	return Validate();
}

MpdPairDeltaDCA::~MpdPairDeltaDCA() {
}


/*
 * MpdNicaCutsLinkDef.h
 *
 *  Created on: 10 kwi 2017
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef INTERFACES_MPDROOT_CUTS_MPDNICACUTSLINKDEF_H_
#define INTERFACES_MPDROOT_CUTS_MPDNICACUTSLINKDEF_H_

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class MpdTpcProbCut + ;
#pragma link C++ class MpdTrackChargeCut + ;
#pragma link C++ class MpdTrackFirstPointCut + ;
#pragma link C++ class MpdTcpCalibratedCut + ;
#pragma link C++ class MpdPadsEdgeSectorCut + ;
#pragma link C++ class MpdHitsEdgeSectorCut + ;
#pragma link C++ class MpdNSigmaCut + ;
#pragma link C++ class MpdBasicTrackCut + ;

#pragma link C++ class MpdAlicePairQuality + ;
#pragma link C++ class MpdDeltaEtaDeltaPhiStarCut + ;
#pragma link C++ class MpdHelixSep + ;
#pragma link C++ class MpdPairSharedHitsCut + ;
#pragma link C++ class MpdSplittedPairsCut + ;
#pragma link C++ class MpdStarPairQualityCut + ;
#pragma link C++ class MpdPairDeltaDCA + ;

#pragma link C++ class MpdModularTpcPairCut + ;
#pragma link C++ class MpdNominalTpcPairDistanceCut + ;
#pragma link C++ class MpdPairKalmanPadsCuts + ;
#pragma link C++ class MpdPairSharedPadsCut + ;
#pragma link C++ class MpdPairTpcEntranceCut + ;
#pragma link C++ class MpdTpcPairSeparationCut + ;
#pragma link C++ class MpdPairTpcEntranceCut2D + ;

#pragma link C++ class MpdPairTpcEntrySimpleCut + ;
#pragma link C++ class MpdPairTpcSeparationSimpleCut + ;
#pragma link C++ class MpdPairTpcSimpleCut + ;
#pragma link C++ class MpdCylinderTpcPairCut + ;
#pragma link C++ class MpdPairTcpSeparationSimpleNegCut + ;

#pragma link C++ class MpdTpcMonitor + ;
#pragma link C++ class MpdTofMonitor + ;
#pragma link C++ class MpdKinMonitor + ;
#pragma link C++ class MpdDcaMonitor + ;

#endif

#endif /* INTERFACES_MPDROOT_CUTS_MPDNICACUTSLINKDEF_H_ */

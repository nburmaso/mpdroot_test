// This file is a part of the NICA project.
//
// Copyright (C) 2023 JINR

#pragma once

#include "MpdMCTrack.h"

#include <ActsFatras/EventData/Barcode.hpp>
#include <ActsFatras/EventData/Particle.hpp>

#include <TClonesArray.h>
#include <TEfficiency.h>

#include <map>
#include <set>

/// Run hand-made efficiencies and fake rate calculations.
std::map<Int_t, Bool_t> runPerformance(
    TEfficiency *effPt,
    TEfficiency *effEta,
    Int_t &nTruth,
    Int_t &nFake,
    Int_t &nRealTracks,
    std::string inPath,
    std::string outPath,
    Int_t eventNumber,
    const Mpd::Tpc::ProtoTrackContainer &trajectories,
    const Mpd::Tpc::InputHitContainer &hits,
    TClonesArray *mcTracks,
    Int_t measurementsMin,
    Double_t truthMatchProbMin,
    Bool_t onlySelectedTracks,
    std::string outFile);

Int_t calcNumberPriHits(const Mpd::Tpc::InputHitContainer &hits,
                        TClonesArray *mcTracks);

std::vector<Int_t> downloadTrackIds(
    Int_t eventNumber,
    std::string path);

// Pseudorapidity of real particle mcTrack
Double_t eta(MpdMCTrack *mcTrack, TVector3 &v);

// Is track is reconstructed.
Bool_t evalIsReco(const Mpd::Tpc::ProtoTrack &track,
                  const Mpd::Tpc::InputHitContainer &hits,
                  Int_t measurementsMin,
                  Double_t truthMatchProbMin);

// For the reco track calculate
// the number of hits correspoinding to real track with majTrackId
// divided by the lentgh of reco track
Double_t truthProb(const Mpd::Tpc::ProtoTrack &track,
                   const Mpd::Tpc::InputHitContainer &hits,
                   Int_t majTrackId);

/// For reco track return majority trackId
Int_t calcMajTrackId(const ActsExamples::ProtoTrack &track,
                     const Mpd::Tpc::InputHitContainer &hits);

/// Store efficiencies to root file
void saveToRoot(TEfficiency *effPt,
                TEfficiency *effEta,
                std::string fname);

/// Update TEfficiency with Pt and value is reco or not
void updateTEffPt(const std::map<Int_t, Bool_t> &trackIdToRecoMap,
                  TEfficiency *eff,
                  TClonesArray *mcTracks);

/// Update TEfficiency with eta and value is reco or not
void updateTEffEta(const std::map<Int_t, Bool_t> &trackIdToRecoMap,
                   TEfficiency *eff,
                   TClonesArray *mcTracks);

// Creates map trackId -> vector_of_hit_indicies
std::unordered_map<Int_t, Mpd::Tpc::ProtoTrack> calcRealTracks(
    const Mpd::Tpc::InputHitContainer &hits);

// Prints efficiency with map trackId -> is reco or not
// at the input
void printEfficiency(
    std::string prefix,
    const std::map<Int_t, Bool_t> &trackIdToRecoMap);

// Prints TEfficiency
void printEfficiency(std::string prefix,
                     TEfficiency *tEff);

void printEfficiency(
  std::map<Int_t, std::pair<Int_t, Int_t>> trackIdToTruthFakeMap,
  Int_t eventNumber);

void printMcTracks(
    TClonesArray *mcTracks,
    const std::set<Int_t> &trackIds,
    const Mpd::Tpc::InputHitContainer &hits,        // all hits. Not selected
    const std::map<size_t, ActsFatras::Barcode> &trackIdToBarcodeMap,
    Bool_t printReco,
    const std::map<Int_t, Bool_t> &trackIdToRecoMap,
    std::string prefix,
    Bool_t allTracks);

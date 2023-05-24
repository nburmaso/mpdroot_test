// This file is a part of the NICA project.
//
// Copyright (C) 2022 JINR

#pragma once

#include "MpdTpcConfig.h"
#include "MpdTpcEventData.h"
#include "MpdTpcInputHit.h"

#include "ActsExamples/EventData/SimParticle.hpp"

#include <Acts/Utilities/Logger.hpp>

#include <map>
#include <ostream>
#include <string>

namespace Mpd::Tpc {

/// Debug information on a single simulation track.
struct Quality {
  /// Maximum relative length among all found tracks.
  Double_t quality;
  /// Percent of points belonging to the original track.
  Double_t accuracy;
  /// Length of the best found track.
  size_t length;
  /// Length of the original track.
  size_t realLength;
  /// Number of found tracks.
  size_t nTracks;
};

/// Maps simulation tracks to the recognition statistics.
using Statistics = std::map<int, Quality>;

/// @brief Provides an API for the tracker.
class Runner final {
public:
  Runner(const BaseTpcSectorGeo &secGeo,
         const std::string &jsonFile,
         Acts::Logging::Level level = Acts::Logging::DEBUG):
      Runner(secGeo, "" /* No import */, jsonFile, level) {}

  Runner(const BaseTpcSectorGeo &secGeo,
         const std::string &rootFile,
         const std::string &jsonFile,
         Acts::Logging::Level level = Acts::Logging::DEBUG):
      m_logger(Acts::getDefaultLogger("Runner", level)),
      m_level(level),
      m_config(secGeo, rootFile, jsonFile, m_level) {}

  void execute(
      const InputHitContainer &hits,
      const ActsExamples::SimParticleContainer &inputParticles,
      const ActsExamples::IndexMultimap<ActsFatras::Barcode> &hitsToParticles,
      ActsExamples::CKFPerformanceWriter *perfWriter,
      ActsExamples::AlgorithmContext &context,
      std::string outPath);

  const Config &config() const { return m_config; }

  size_t getTracksNumber(const ActsExamples::AlgorithmContext &context) const;
  Statistics getStatistics(const ActsExamples::AlgorithmContext &context) const;

private:

  // Logging.
  void logInput(const ActsExamples::AlgorithmContext &context) const;
  void logOutput(const ActsExamples::AlgorithmContext &context) const;

  void logHit(const std::string &prefix,
              size_t hitId,
              const InputHit &hit) const;
  void logHits(const std::string &prefix,
               const InputHitContainer &hits) const;

  void logTrack(const std::string &prefix,
                size_t trackId,
                const ProtoTrack &track) const;
  void logTracks(const std::string &prefix,
                 const ProtoTrackContainer &tracks) const;

  void logParam(const std::string &prefix,
                size_t trackId,
                const TrackParameters &param) const;
  void logParams(const std::string &prefix,
                 const TrackParametersContainer &params) const;

  // Collecting statistics.
  void checkTrack(const InputHitContainer &hits,
                  size_t trackId,
                  const ProtoTrack &track,
                  Statistics &statistics) const;
  void checkTracks(const InputHitContainer &hits,
                   const ProtoTrackContainer &tracks,
                   Statistics &statistics) const;

  const Acts::Logger &logger() const { return *m_logger; }

  std::unique_ptr<const Acts::Logger> m_logger;
  Acts::Logging::Level m_level;

  Config m_config;
};

} // namespace Mpd::Tpc
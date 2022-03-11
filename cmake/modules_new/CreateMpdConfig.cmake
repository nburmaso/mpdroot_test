function(GENERATE_MPDCONFIG)
message( "${BASE_INCLUDE_DIRECTORIES}" )
    file( WRITE ${CMAKE_BINARY_DIR}/mpd-config "#!/bin/bash\n" )
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "mpdlibs=\"\\\n" )
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-L${FAIRROOT_LIBRARY_DIR} -lBase -lEventDisplay -lFairDataMatch -lFairTools \\\n" )
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lGeane -lGen -lGeoBase -lMbsAPI -lParBase -lTrkBase \n" )
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-L${CMAKE_BINARY_DIR}/lib -lbmd -lCluster -lCpc \\\n" )
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lEmc -lEtof -lEventDisplay -lFfd -lHADGEN \\\n" )
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lKalman -lLHETrack -lMCStack -lMpdBase -lMpdDst \\\n" )
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lMpdFemto -lMpdField \\\n" )
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lMpdGeneralGenerator \\\n" )
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lMpdGen -lMpdPid -lPassive -lStrawECT \\\n" )
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lStrawendcap -lSts -lTHadgen \\\n" )
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lTof -ltpc -lTShieldGenerator \\\n" )
    if ( EXISTS "${CMAKE_SOURCE_DIR}/nicaroot/CMakeLists.txt" )
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lTShield -lZdc\\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lNicaFeatures -lNicaDataFormat\\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lNicaCut -lNicaAna\\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lNicaFemto -lNicaFlow\\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lNicaGen -lNicaFluct\\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lNicapdCuts -lNicaMpdFormat\\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lNicaMpdHelper -lNicaSpectra\"\n")
    else()
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-lTShield -lZdc\"\n")
    endif()
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "mpdheads=\"\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I$ENV{SIMPATH}/include \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${BASE_INCLUDE_DIRECTORIES} \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/core/mpdBase \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/core/mpdDst \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/core/mpdField \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/core/mpdPid \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/detectors/bbc \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/detectors/bmd \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/detectors/emc \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/detectors/etof \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/detectors/ffd \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/detectors/sts \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/detectors/tof \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/detectors/tpc \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/detectors/zdc \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/eventdisplay \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/generators \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/kalman \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/lhetrack \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/passive \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/physics \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/physics/femto \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/shield_pack \\\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/simulation/mcStack \\\n")
    if( EXISTS "${CMAKE_SOURCE_DIR}/nicaroot/CMakeLists.txt" )
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/base \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/base/chains \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/base/on_the_fly \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/femto/ana \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/femto/base \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/femto/corrfit \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/femto/corrfit/fittingfunctions \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/femto/corrfit/mapgenerators \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/femto/imaging \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/femto/weights \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/flow \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/fluctuations \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/spectra \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/analysis/v0s \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/cuts \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/cuts/cutmonitors \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/cuts/eventcuts/ \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/cuts/trackcuts \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/cuts/trackcuts/detector \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/cuts/trackcuts/kinematics \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/cuts/trackcuts/mc \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/cuts/trackcuts/resolution \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/cuts/twotrackcuts/detector \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/cuts/twotrackcuts/kinematics \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/cuts/twotrackcuts/mc \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/dataformat/compound \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/dataformat/detector \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/dataformat/formats/fair \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/dataformat/formats/fairextended \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/dataformat/formats/unigen \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/dataformat/features \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/dataformat/nicagenerators/ \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/dataformat/nicagenerators/readers \\\n")
        file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "-I${CMAKE_SOURCE_DIR}/nicaroot/dataformat/nicagenerators/writers\\n")
    endif()
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "\"\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config "--std=c++11 -g -O0")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config  "if test $# -eq 0; then\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config  "exit 1\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config  "fi\n")

    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config  "case $1 in\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config  " --libs)\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config  "echo $mpdlibs\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config  ";;\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config  "--cflags)\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config  "echo $mpdheads\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config  ";;\n")
    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config  "esac\n")


    file( COPY ${CMAKE_BINARY_DIR}/mpd-config DESTINATION
    ${CMAKE_BINARY_DIR}/bin/
    FILE_PERMISSIONS GROUP_EXECUTE OWNER_EXECUTE WORLD_EXECUTE WORLD_READ GROUP_READ OWNER_READ)
#    file( APPEND ${CMAKE_BINARY_DIR}/bin/mpd-config
#    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config
#    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config
#    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config
#    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config
#    file( APPEND ${CMAKE_BINARY_DIR}/mpd-config
#                file( APPEND ${CMAKE_BINARY_DIR}/config.sh "export URQMD=${URQMD_PATH}\n")
#    endif()
endfunction()

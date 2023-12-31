# Create a library called "libBbc" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/parbase 
${CMAKE_SOURCE_DIR}/base 
${CMAKE_SOURCE_DIR}/mcstack 
${CMAKE_SOURCE_DIR}/fairtools
${CMAKE_SOURCE_DIR}/bbc
)

include_directories(${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories(${LINK_DIRECTORIES})

set(BBC_SRCS
MpdBbcGeo.cxx 
MpdBbcGeoPar.cxx 
MpdBbc.cxx 
MpdBbcContFact.cxx 
MpdBbcHit.cxx 
MpdBbcHitProducer.cxx 
MpdBbcPoint.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h BBC_HEADERS "${BBC_SRCS}")

set(BBC_LINKDEF MpdBbcLinkDef.h)
set(BBC_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/MpdBbcDict.cxx) 

ROOT_GENERATE_DICTIONARY("${BBC_HEADERS}" "${BBC_LINKDEF}" "${BBC_DICTIONARY}" "${INCLUDE_DIRECTORIES}")


set(BBC_SRCS ${BBC_SRCS} ${BBC_DICTIONARY})


add_library(Bbc SHARED ${BBC_SRCS})
target_link_libraries(Bbc ${ROOT_LIBRARIES})
set_target_properties(Bbc PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})

################ install ###################
install(TARGETS Bbc DESTINATION ${CMAKE_BINARY_DIR}/lib)

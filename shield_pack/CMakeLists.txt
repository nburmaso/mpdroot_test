cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
if(NOT DEFINED PROJECT_NAME)
    project (TShield)
    set(NOT_BUILD_GenelalGenerator "TRUE")
endif()

set(TSHIELD_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
include(cmake/TShieldConfig.cmake)

add_subdirectory (hadgen)
add_subdirectory (shield)
add_subdirectory (THadgen)
add_subdirectory (TShield)
add_subdirectory (TShieldGenerator)
if(NOT NOT_BUILD_GenelalGenerator)
    add_subdirectory (MpdGeneralGenerator)
endif()

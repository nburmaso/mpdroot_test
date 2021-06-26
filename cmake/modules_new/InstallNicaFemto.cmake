MACRO(InstallNicaFemto)
set(NICAFEMTO_HASH 0350ba6a6c4548d5a5b880d8698c25446525723c) 
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/nicafemto/CMakeLists.txt")
    execute_process(COMMAND git clone -b master https://git.jinr.ru/nica/nicafemto.git ${CMAKE_SOURCE_DIR}/nicafemto)
    execute_process(COMMAND git reset --hard  ${NICAFEMTO_HASH} WORKING_DIRECTORY  ${CMAKE_SOURCE_DIR}/nicafemto)
endif()
execute_process(COMMAND git fetch WORKING_DIRECTORY  ${CMAKE_SOURCE_DIR}/nicafemto)
    execute_process(COMMAND git reset --hard  ${NICAFEMTO_HASH} WORKING_DIRECTORY  ${CMAKE_SOURCE_DIR}/nicafemto)
        set(NICAFEMTO_SUBDIR_BUILD ON)
        set(NICAFEMTO_CORE "${CMAKE_SOURCE_DIR}/nicafemto")
        add_subdirectory (${CMAKE_SOURCE_DIR}/nicafemto)
        add_subdirectory (${CMAKE_SOURCE_DIR}/nica_mpd)
ENDMACRO(InstallNicaFemto)

cmake_minimum_required(VERSION 3.5)
project(shell)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

add_executable(shell ${SOURCE_FILES})

set(BOOST_ROOT "/home/paniv/Boost/Install")

FIND_PACKAGE(Boost 1.58.0)
FIND_PACKAGE( Boost COMPONENTS filesystem program_options system REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

target_link_libraries( shell ${Boost_LIBRARIES})


if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()


set (MKDIR_SOURCE_FILE my_mkdir.cpp)
add_executable(mkdir ${MKDIR_SOURCE_FILE})
set(CP_SOURCE_FILE my_cp.cpp)
add_executable(cp ${CP_SOURCE_FILE})
set(MV_SOURCE_FILE my_mv.cpp)
add_executable(mv ${MV_SOURCE_FILE})
set(RM_SOURCE_FILE my_rm.cpp)
add_executable(rm ${RM_SOURCE_FILE})
set(LS_SOURCE_FILE my_ls.cpp)
add_executable(ls ${LS_SOURCE_FILE})
target_link_libraries(rm ${Boost_LIBRARIES})
target_link_libraries(mv ${Boost_LIBRARIES})
target_link_libraries(ls ${Boost_LIBRARIES})
target_link_libraries(cp ${Boost_LIBRARIES})
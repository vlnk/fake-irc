cmake_minimum_required(VERSION 2.8.4)
project(irc-simulator)

set (
  CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/"
)

set (
  BOOST_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/library/boost_1_58_0
)

set (
  YAMLCPP_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/library/yaml-cpp
)

#include yaml libraries
#find_package( yamlcpp )

set (
  BOOST_INCLUDE_DIR
  ${BOOST_DIR}
)

set (
  BOOST_LIBRARY_DIR
  ${BOOST_DIR}/libs
)

# find the yaml-cpp include directory
find_path(YAMLCPP_INCLUDE_DIR yaml-cpp/yaml.h
          PATHS ${YAMLCPP_DIR}/include/
)

# find the yaml-cpp library
find_library(YAMLCPP_LIBRARY libyaml-cpp.dylib
             PATHS ${YAMLCPP_DIR}/lib
)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/library/yaml-cpp/lib)

#turn on using solution folders
set_property (
  GLOBAL PROPERTY
  USE_FOLDERS ON
)

## Target
set ( EXECUTABLE_OUTPUT_PATH bin )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

file (
  GLOB_RECURSE
  SOURCE_FILES
  src/*
)

add_executable ( irc-simulator ${SOURCE_FILES} )

## Link libraries
include_directories ( ${BOOST_INCLUDE_DIR} )
include_directories ( ${YAMLCPP_INCLUDE_DIR} )


target_link_libraries ( irc-simulator ${YAMLCPP_LIBRARY} )

install (
  TARGETS irc-simulator
  DESTINATION bin
)

install (
  FILES ${YAMLCPP_LIBRARY}
  DESTINATION lib
)

# build a cpack driven installer package
include ( installrequiredsystemlibraries )
set (
  CPACK_RESOURCE_FILE_LICENSE
  "${CMAKE_CURRENT_SOURCE_DIR}/license.md"
)

include ( cpack )

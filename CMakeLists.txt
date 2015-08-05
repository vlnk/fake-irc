cmake_minimum_required(VERSION 2.8.4)
project(fake-irc)

############################################################
#### INCLUDES
include(ExternalProject)

############################################################
#### MANAGE PROJECT VERSION
set (FAKE_IRC_VERSION_MAJOR 1)
set (FAKE_IRC_VERSION_MINOR 0)
set (FAKE_IRC_VERSION_PATCH 0)
set (FAKE_IRC_VERSION
  "${FAKE_IRC_VERSION_MAJOR}
    .${FAKE_IRC_VERSION_MINOR}
    .${FAKE_IRC_VERSION_PATCH}"
)

configure_file (
  "${PROJECT_SOURCE_DIR}/src/FakeIRCConfig.h.in"
  "${PROJECT_BINARY_DIR}/src/FakeIRCConfig.h"
)

############################################################
#### TURN ON USING SOLUTION FOLDERS
set_property (
  GLOBAL PROPERTY
  USE_FOLDERS ON
)

############################################################
#### SET CONFIGURATION VARS
set( CMAKE_VERBOSE_MAKEFILE off )
set ( EXECUTABLE_OUTPUT_PATH bin )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

############################################################
#### FIND YAML-CPP INCLUDES
set ( YAMLCPP_ROOT ${CMAKE_CURRENT_BINARY_DIR}/../external/yaml-cpp )
set ( YAMLCPP_INCLUDE_DIRS ${YAMLCPP_ROOT}/src/yaml-cpp/include )
find_library(YAMLCPP_LIBRARY
  libyaml-cpp.a
  PATHS ${YAMLCPP_ROOT}
)

############################################################
#### FIND BOOST INCLUDES
find_package(Boost 1.58.0)

if(Boost_FOUND)
  message(STATUS "Found Boost includes: ${Boost_VERSION}")
else()
  message(FATAL_ERROR "Could not find Boost includes!")
endif()

############################################################
#### INCLUDE EXTERNAL DIRECTORIES (BOOST, YAML-CPP)
include_directories( ${Boost_INCLUDE_DIRS} )
include_directories ( ${YAML_CPP_INCLUDE_DIRS} )

############################################################
#### GET PROJECT SOURCES
file (
  GLOB_RECURSE
  SOURCE_FILES
  src/*
)

############################################################
#### CLONE YAML-CPP PROJECT TO EXTERN DIRECTORY
externalproject_add(yaml-cpp
  PREFIX ${YAMLCPP_ROOT}
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
  BINARY_DIR ${YAMLCPP_ROOT}
  INSTALL_DIR ${YAMLCPP_ROOT}
)

############################################################
#### ADD EXECUTABLE
add_executable ( fake-irc ${SOURCE_FILES} )

############################################################
#### LINK LIBRARIES
target_link_libraries( fake-irc ${YAMLCPP_LIBRARY} )

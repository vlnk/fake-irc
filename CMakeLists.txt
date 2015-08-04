cmake_minimum_required(VERSION 2.8.4)
project(fake-irc)

set (FAKE_IRC_VERSION_MAJOR 1)
set (FAKE_IRC_VERSION_MINOR 0)
set (FAKE_IRC_VERSION_PATCH 0)
set (FAKE_IRC_VERSION
  "${FAKE_IRC_VERSION_MAJOR}
    .${FAKE_IRC_VERSION_MINOR}
    .${FAKE_IRC_VERSION_PATCH}"
)

configure_file (
  "${PROJECT_SOURCE_DIR}/FakeIRCConfig.h.in"
  "${PROJECT_BINARY_DIR}/FakeIRCConfig.h"
  )

#turn on using solution folders
set_property (
  GLOBAL PROPERTY
  USE_FOLDERS ON
)

## Target
set ( EXECUTABLE_OUTPUT_PATH bin )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories ("${PROJECT_SOURCE_DIR}/lib" )

file (
  GLOB_RECURSE
  SOURCE_FILES
  src/*
)

add_executable ( fake-irc ${SOURCE_FILES} )

## Link libraries

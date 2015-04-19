CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)
PROJECT(irc-simulator-cpp)

set(
  CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/"
  )

#include yaml libraries
FIND_PACKAGE(YamlCpp)

#turn on using solution folders
set_property( GLOBAL PROPERTY USE_FOLDERS ON)
SET(EXECUTABLE_OUTPUT_PATH bin/)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FILE(
  GLOB_RECURSE
  SOURCE_FILES
  src/*
)

# add Yaml include directories
INCLUDE_DIRECTORIES(${YAMLCPP_INCLUDE_DIR})

ADD_EXECUTABLE(
  irc-simulator-cpp
  ${SOURCE_FILES}
)

# link opencv and YARP libraries
TARGET_LINK_LIBRARIES(
  irc-simulator-cpp
  ${YAMLCPP_LIBRARY}
)

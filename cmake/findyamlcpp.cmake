# Locate yaml-cpp
#
# This module defines
#  YAMLCPP_FOUND, if false, do not try to link to yaml-cpp
#  YAMLCPP_LIBRARY, where to find yaml-cpp
#  YAMLCPP_INCLUDE_DIR, where to find yaml.h
#
# By default, the dynamic libraries of yaml-cpp will be found. To find the static ones instead,
# you must set the YAMLCPP_STATIC_LIBRARY variable to TRUE before calling find_package(YamlCpp ...).
#
# If yaml-cpp is not installed in a standard path, you can use the YAMLCPP_DIR CMake variable
# to tell CMake where yaml-cpp is.

# attempt to find static library first if this is set
if(YAMLCPP_STATIC_LIBRARY)
    set(YAMLCPP_STATIC libyaml-cpp.a)
endif()

# find the yaml-cpp include directory
find_path(YAMLCPP_INCLUDE_DIR yaml-cpp/yaml.h
          PATH_SUFFIXES include
          PATHS ${YAMLCPP_DIR}/include/
)

# find the yaml-cpp library
find_library(YAMLCPP_LIBRARY
             NAMES ${YAMLCPP_STATIC} yaml-cpp
             PATH_SUFFIXES lib64 lib
             PATHS ${YAMLCPP_DIR}/lib
)

# handle the QUIETLY and REQUIRED arguments and set YAMLCPP_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  YAMLCPP DEFAULT_MSG YAMLCPP_INCLUDE_DIR YAMLCPP_LIBRARY
)

# Copy the results to the output variables.

if (YAMLCPP_FOUND)
  set (YAMLCPP_LIBRARIES ${YAMLCPP_LIBRARY})
  set (YAMLCPP_INCLUDE_DIRS ${YAMLCPP_INCLUDE_DIR})
  message(yamlcpp found ${YAMLCPP_INCLUDE_DIR} ${YAMLCPP_LIBRARY})
else (YAMLCPP_FOUND)
  set (YAMLCPP_LIBRARIES)
  set (YAMLCPP_INCLUDE_DIRS)
  message(yamlcpp not found)
endif (YAMLCPP_FOUND)

mark_as_advanced(YAMLCPP_INCLUDE_DIRS YAMLCPP_LIBRARIES)

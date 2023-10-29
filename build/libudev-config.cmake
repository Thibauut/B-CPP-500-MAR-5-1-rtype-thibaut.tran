########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(libudev_FIND_QUIETLY)
    set(libudev_MESSAGE_MODE VERBOSE)
else()
    set(libudev_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/libudevTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${libudev_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(libudev_VERSION_STRING "system")
set(libudev_INCLUDE_DIRS ${libudev_INCLUDE_DIRS_RELEASE} )
set(libudev_INCLUDE_DIR ${libudev_INCLUDE_DIRS_RELEASE} )
set(libudev_LIBRARIES ${libudev_LIBRARIES_RELEASE} )
set(libudev_DEFINITIONS ${libudev_DEFINITIONS_RELEASE} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${libudev_BUILD_MODULES_PATHS_RELEASE} )
    message(${libudev_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()



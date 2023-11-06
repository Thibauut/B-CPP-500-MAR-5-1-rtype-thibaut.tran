########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(SFML_FIND_QUIETLY)
    set(SFML_MESSAGE_MODE VERBOSE)
else()
    set(SFML_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/SFMLTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${sfml_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(SFML_VERSION_STRING "2.5.1")
set(SFML_INCLUDE_DIRS ${sfml_INCLUDE_DIRS_RELEASE} )
set(SFML_INCLUDE_DIR ${sfml_INCLUDE_DIRS_RELEASE} )
set(SFML_LIBRARIES ${sfml_LIBRARIES_RELEASE} )
set(SFML_DEFINITIONS ${sfml_DEFINITIONS_RELEASE} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${sfml_BUILD_MODULES_PATHS_RELEASE} )
    message(${SFML_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()



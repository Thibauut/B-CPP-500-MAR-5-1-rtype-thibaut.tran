# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(libudev_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(libudev_FRAMEWORKS_FOUND_RELEASE "${libudev_FRAMEWORKS_RELEASE}" "${libudev_FRAMEWORK_DIRS_RELEASE}")

set(libudev_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET libudev_DEPS_TARGET)
    add_library(libudev_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET libudev_DEPS_TARGET
             PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${libudev_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${libudev_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:>
             APPEND)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### libudev_DEPS_TARGET to all of them
conan_package_library_targets("${libudev_LIBS_RELEASE}"    # libraries
                              "${libudev_LIB_DIRS_RELEASE}" # package_libdir
                              "${libudev_BIN_DIRS_RELEASE}" # package_bindir
                              "${libudev_LIBRARY_TYPE_RELEASE}"
                              "${libudev_IS_HOST_WINDOWS_RELEASE}"
                              libudev_DEPS_TARGET
                              libudev_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "libudev"    # package_name
                              "${libudev_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${libudev_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET libudev::libudev
                 PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${libudev_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${libudev_LIBRARIES_TARGETS}>
                 APPEND)

    if("${libudev_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET libudev::libudev
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     libudev_DEPS_TARGET
                     APPEND)
    endif()

    set_property(TARGET libudev::libudev
                 PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${libudev_LINKER_FLAGS_RELEASE}> APPEND)
    set_property(TARGET libudev::libudev
                 PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${libudev_INCLUDE_DIRS_RELEASE}> APPEND)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET libudev::libudev
                 PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${libudev_LIB_DIRS_RELEASE}> APPEND)
    set_property(TARGET libudev::libudev
                 PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${libudev_COMPILE_DEFINITIONS_RELEASE}> APPEND)
    set_property(TARGET libudev::libudev
                 PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${libudev_COMPILE_OPTIONS_RELEASE}> APPEND)

########## For the modules (FindXXX)
set(libudev_LIBRARIES_RELEASE libudev::libudev)

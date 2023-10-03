# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(sfml_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(sfml_FRAMEWORKS_FOUND_RELEASE "${sfml_FRAMEWORKS_RELEASE}" "${sfml_FRAMEWORK_DIRS_RELEASE}")

set(sfml_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET sfml_DEPS_TARGET)
    add_library(sfml_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET sfml_DEPS_TARGET
             PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${sfml_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${sfml_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:sfml-system;opengl::opengl;xorg::xorg;libudev::libudev;sfml-window>
             APPEND)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### sfml_DEPS_TARGET to all of them
conan_package_library_targets("${sfml_LIBS_RELEASE}"    # libraries
                              "${sfml_LIB_DIRS_RELEASE}" # package_libdir
                              "${sfml_BIN_DIRS_RELEASE}" # package_bindir
                              "${sfml_LIBRARY_TYPE_RELEASE}"
                              "${sfml_IS_HOST_WINDOWS_RELEASE}"
                              sfml_DEPS_TARGET
                              sfml_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "sfml"    # package_name
                              "${sfml_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${sfml_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## COMPONENTS TARGET PROPERTIES Release ########################################

    ########## COMPONENT sfml-audio #############

        set(sfml_sfml-audio_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(sfml_sfml-audio_FRAMEWORKS_FOUND_RELEASE "${sfml_sfml-audio_FRAMEWORKS_RELEASE}" "${sfml_sfml-audio_FRAMEWORK_DIRS_RELEASE}")

        set(sfml_sfml-audio_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET sfml_sfml-audio_DEPS_TARGET)
            add_library(sfml_sfml-audio_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET sfml_sfml-audio_DEPS_TARGET
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${sfml_sfml-audio_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-audio_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-audio_DEPENDENCIES_RELEASE}>
                     APPEND)

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'sfml_sfml-audio_DEPS_TARGET' to all of them
        conan_package_library_targets("${sfml_sfml-audio_LIBS_RELEASE}"
                              "${sfml_sfml-audio_LIB_DIRS_RELEASE}"
                              "${sfml_sfml-audio_BIN_DIRS_RELEASE}" # package_bindir
                              "${sfml_sfml-audio_LIBRARY_TYPE_RELEASE}"
                              "${sfml_sfml-audio_IS_HOST_WINDOWS_RELEASE}"
                              sfml_sfml-audio_DEPS_TARGET
                              sfml_sfml-audio_LIBRARIES_TARGETS
                              "_RELEASE"
                              "sfml_sfml-audio"
                              "${sfml_sfml-audio_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET sfml-audio
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${sfml_sfml-audio_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-audio_LIBRARIES_TARGETS}>
                     APPEND)

        if("${sfml_sfml-audio_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET sfml-audio
                         PROPERTY INTERFACE_LINK_LIBRARIES
                         sfml_sfml-audio_DEPS_TARGET
                         APPEND)
        endif()

        set_property(TARGET sfml-audio PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${sfml_sfml-audio_LINKER_FLAGS_RELEASE}> APPEND)
        set_property(TARGET sfml-audio PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${sfml_sfml-audio_INCLUDE_DIRS_RELEASE}> APPEND)
        set_property(TARGET sfml-audio PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${sfml_sfml-audio_LIB_DIRS_RELEASE}> APPEND)
        set_property(TARGET sfml-audio PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${sfml_sfml-audio_COMPILE_DEFINITIONS_RELEASE}> APPEND)
        set_property(TARGET sfml-audio PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${sfml_sfml-audio_COMPILE_OPTIONS_RELEASE}> APPEND)

    ########## COMPONENT sfml-network #############

        set(sfml_sfml-network_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(sfml_sfml-network_FRAMEWORKS_FOUND_RELEASE "${sfml_sfml-network_FRAMEWORKS_RELEASE}" "${sfml_sfml-network_FRAMEWORK_DIRS_RELEASE}")

        set(sfml_sfml-network_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET sfml_sfml-network_DEPS_TARGET)
            add_library(sfml_sfml-network_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET sfml_sfml-network_DEPS_TARGET
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${sfml_sfml-network_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-network_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-network_DEPENDENCIES_RELEASE}>
                     APPEND)

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'sfml_sfml-network_DEPS_TARGET' to all of them
        conan_package_library_targets("${sfml_sfml-network_LIBS_RELEASE}"
                              "${sfml_sfml-network_LIB_DIRS_RELEASE}"
                              "${sfml_sfml-network_BIN_DIRS_RELEASE}" # package_bindir
                              "${sfml_sfml-network_LIBRARY_TYPE_RELEASE}"
                              "${sfml_sfml-network_IS_HOST_WINDOWS_RELEASE}"
                              sfml_sfml-network_DEPS_TARGET
                              sfml_sfml-network_LIBRARIES_TARGETS
                              "_RELEASE"
                              "sfml_sfml-network"
                              "${sfml_sfml-network_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET sfml-network
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${sfml_sfml-network_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-network_LIBRARIES_TARGETS}>
                     APPEND)

        if("${sfml_sfml-network_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET sfml-network
                         PROPERTY INTERFACE_LINK_LIBRARIES
                         sfml_sfml-network_DEPS_TARGET
                         APPEND)
        endif()

        set_property(TARGET sfml-network PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${sfml_sfml-network_LINKER_FLAGS_RELEASE}> APPEND)
        set_property(TARGET sfml-network PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${sfml_sfml-network_INCLUDE_DIRS_RELEASE}> APPEND)
        set_property(TARGET sfml-network PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${sfml_sfml-network_LIB_DIRS_RELEASE}> APPEND)
        set_property(TARGET sfml-network PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${sfml_sfml-network_COMPILE_DEFINITIONS_RELEASE}> APPEND)
        set_property(TARGET sfml-network PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${sfml_sfml-network_COMPILE_OPTIONS_RELEASE}> APPEND)

    ########## COMPONENT sfml-graphics #############

        set(sfml_sfml-graphics_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(sfml_sfml-graphics_FRAMEWORKS_FOUND_RELEASE "${sfml_sfml-graphics_FRAMEWORKS_RELEASE}" "${sfml_sfml-graphics_FRAMEWORK_DIRS_RELEASE}")

        set(sfml_sfml-graphics_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET sfml_sfml-graphics_DEPS_TARGET)
            add_library(sfml_sfml-graphics_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET sfml_sfml-graphics_DEPS_TARGET
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${sfml_sfml-graphics_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-graphics_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-graphics_DEPENDENCIES_RELEASE}>
                     APPEND)

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'sfml_sfml-graphics_DEPS_TARGET' to all of them
        conan_package_library_targets("${sfml_sfml-graphics_LIBS_RELEASE}"
                              "${sfml_sfml-graphics_LIB_DIRS_RELEASE}"
                              "${sfml_sfml-graphics_BIN_DIRS_RELEASE}" # package_bindir
                              "${sfml_sfml-graphics_LIBRARY_TYPE_RELEASE}"
                              "${sfml_sfml-graphics_IS_HOST_WINDOWS_RELEASE}"
                              sfml_sfml-graphics_DEPS_TARGET
                              sfml_sfml-graphics_LIBRARIES_TARGETS
                              "_RELEASE"
                              "sfml_sfml-graphics"
                              "${sfml_sfml-graphics_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET sfml-graphics
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${sfml_sfml-graphics_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-graphics_LIBRARIES_TARGETS}>
                     APPEND)

        if("${sfml_sfml-graphics_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET sfml-graphics
                         PROPERTY INTERFACE_LINK_LIBRARIES
                         sfml_sfml-graphics_DEPS_TARGET
                         APPEND)
        endif()

        set_property(TARGET sfml-graphics PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${sfml_sfml-graphics_LINKER_FLAGS_RELEASE}> APPEND)
        set_property(TARGET sfml-graphics PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${sfml_sfml-graphics_INCLUDE_DIRS_RELEASE}> APPEND)
        set_property(TARGET sfml-graphics PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${sfml_sfml-graphics_LIB_DIRS_RELEASE}> APPEND)
        set_property(TARGET sfml-graphics PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${sfml_sfml-graphics_COMPILE_DEFINITIONS_RELEASE}> APPEND)
        set_property(TARGET sfml-graphics PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${sfml_sfml-graphics_COMPILE_OPTIONS_RELEASE}> APPEND)

    ########## COMPONENT sfml-window #############

        set(sfml_sfml-window_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(sfml_sfml-window_FRAMEWORKS_FOUND_RELEASE "${sfml_sfml-window_FRAMEWORKS_RELEASE}" "${sfml_sfml-window_FRAMEWORK_DIRS_RELEASE}")

        set(sfml_sfml-window_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET sfml_sfml-window_DEPS_TARGET)
            add_library(sfml_sfml-window_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET sfml_sfml-window_DEPS_TARGET
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${sfml_sfml-window_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-window_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-window_DEPENDENCIES_RELEASE}>
                     APPEND)

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'sfml_sfml-window_DEPS_TARGET' to all of them
        conan_package_library_targets("${sfml_sfml-window_LIBS_RELEASE}"
                              "${sfml_sfml-window_LIB_DIRS_RELEASE}"
                              "${sfml_sfml-window_BIN_DIRS_RELEASE}" # package_bindir
                              "${sfml_sfml-window_LIBRARY_TYPE_RELEASE}"
                              "${sfml_sfml-window_IS_HOST_WINDOWS_RELEASE}"
                              sfml_sfml-window_DEPS_TARGET
                              sfml_sfml-window_LIBRARIES_TARGETS
                              "_RELEASE"
                              "sfml_sfml-window"
                              "${sfml_sfml-window_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET sfml-window
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${sfml_sfml-window_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-window_LIBRARIES_TARGETS}>
                     APPEND)

        if("${sfml_sfml-window_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET sfml-window
                         PROPERTY INTERFACE_LINK_LIBRARIES
                         sfml_sfml-window_DEPS_TARGET
                         APPEND)
        endif()

        set_property(TARGET sfml-window PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${sfml_sfml-window_LINKER_FLAGS_RELEASE}> APPEND)
        set_property(TARGET sfml-window PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${sfml_sfml-window_INCLUDE_DIRS_RELEASE}> APPEND)
        set_property(TARGET sfml-window PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${sfml_sfml-window_LIB_DIRS_RELEASE}> APPEND)
        set_property(TARGET sfml-window PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${sfml_sfml-window_COMPILE_DEFINITIONS_RELEASE}> APPEND)
        set_property(TARGET sfml-window PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${sfml_sfml-window_COMPILE_OPTIONS_RELEASE}> APPEND)

    ########## COMPONENT sfml-system #############

        set(sfml_sfml-system_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(sfml_sfml-system_FRAMEWORKS_FOUND_RELEASE "${sfml_sfml-system_FRAMEWORKS_RELEASE}" "${sfml_sfml-system_FRAMEWORK_DIRS_RELEASE}")

        set(sfml_sfml-system_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET sfml_sfml-system_DEPS_TARGET)
            add_library(sfml_sfml-system_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET sfml_sfml-system_DEPS_TARGET
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${sfml_sfml-system_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-system_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-system_DEPENDENCIES_RELEASE}>
                     APPEND)

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'sfml_sfml-system_DEPS_TARGET' to all of them
        conan_package_library_targets("${sfml_sfml-system_LIBS_RELEASE}"
                              "${sfml_sfml-system_LIB_DIRS_RELEASE}"
                              "${sfml_sfml-system_BIN_DIRS_RELEASE}" # package_bindir
                              "${sfml_sfml-system_LIBRARY_TYPE_RELEASE}"
                              "${sfml_sfml-system_IS_HOST_WINDOWS_RELEASE}"
                              sfml_sfml-system_DEPS_TARGET
                              sfml_sfml-system_LIBRARIES_TARGETS
                              "_RELEASE"
                              "sfml_sfml-system"
                              "${sfml_sfml-system_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET sfml-system
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${sfml_sfml-system_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${sfml_sfml-system_LIBRARIES_TARGETS}>
                     APPEND)

        if("${sfml_sfml-system_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET sfml-system
                         PROPERTY INTERFACE_LINK_LIBRARIES
                         sfml_sfml-system_DEPS_TARGET
                         APPEND)
        endif()

        set_property(TARGET sfml-system PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${sfml_sfml-system_LINKER_FLAGS_RELEASE}> APPEND)
        set_property(TARGET sfml-system PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${sfml_sfml-system_INCLUDE_DIRS_RELEASE}> APPEND)
        set_property(TARGET sfml-system PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${sfml_sfml-system_LIB_DIRS_RELEASE}> APPEND)
        set_property(TARGET sfml-system PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${sfml_sfml-system_COMPILE_DEFINITIONS_RELEASE}> APPEND)
        set_property(TARGET sfml-system PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${sfml_sfml-system_COMPILE_OPTIONS_RELEASE}> APPEND)

    ########## AGGREGATED GLOBAL TARGET WITH THE COMPONENTS #####################
    set_property(TARGET sfml::sfml PROPERTY INTERFACE_LINK_LIBRARIES sfml-audio APPEND)
    set_property(TARGET sfml::sfml PROPERTY INTERFACE_LINK_LIBRARIES sfml-network APPEND)
    set_property(TARGET sfml::sfml PROPERTY INTERFACE_LINK_LIBRARIES sfml-graphics APPEND)
    set_property(TARGET sfml::sfml PROPERTY INTERFACE_LINK_LIBRARIES sfml-window APPEND)
    set_property(TARGET sfml::sfml PROPERTY INTERFACE_LINK_LIBRARIES sfml-system APPEND)

########## For the modules (FindXXX)
set(sfml_LIBRARIES_RELEASE sfml::sfml)

########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND sfml_COMPONENT_NAMES sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
list(REMOVE_DUPLICATES sfml_COMPONENT_NAMES)
list(APPEND sfml_FIND_DEPENDENCY_NAMES opengl_system libudev xorg)
list(REMOVE_DUPLICATES sfml_FIND_DEPENDENCY_NAMES)
set(opengl_system_FIND_MODE "NO_MODULE")
set(libudev_FIND_MODE "NO_MODULE")
set(xorg_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(sfml_PACKAGE_FOLDER_RELEASE "/home/maokoro/.conan2/p/b/sfml888f9897b2697/p")
set(sfml_BUILD_MODULES_PATHS_RELEASE )


set(sfml_INCLUDE_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/include")
set(sfml_RES_DIRS_RELEASE )
set(sfml_DEFINITIONS_RELEASE )
set(sfml_SHARED_LINK_FLAGS_RELEASE )
set(sfml_EXE_LINK_FLAGS_RELEASE )
set(sfml_OBJECTS_RELEASE )
set(sfml_COMPILE_DEFINITIONS_RELEASE )
set(sfml_COMPILE_OPTIONS_C_RELEASE )
set(sfml_COMPILE_OPTIONS_CXX_RELEASE )
set(sfml_LIB_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/lib")
set(sfml_BIN_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/bin")
set(sfml_LIBRARY_TYPE_RELEASE SHARED)
set(sfml_IS_HOST_WINDOWS_RELEASE 0)
set(sfml_LIBS_RELEASE sfml-audio sfml-network sfml-graphics sfml-window sfml-system)
set(sfml_SYSTEM_LIBS_RELEASE pthread rt)
set(sfml_FRAMEWORK_DIRS_RELEASE )
set(sfml_FRAMEWORKS_RELEASE )
set(sfml_BUILD_DIRS_RELEASE )
set(sfml_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(sfml_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${sfml_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${sfml_COMPILE_OPTIONS_C_RELEASE}>")
set(sfml_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${sfml_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${sfml_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${sfml_EXE_LINK_FLAGS_RELEASE}>")


set(sfml_COMPONENTS_RELEASE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
########### COMPONENT sfml-audio VARIABLES ############################################

set(sfml_sfml-audio_INCLUDE_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/include")
set(sfml_sfml-audio_LIB_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/lib")
set(sfml_sfml-audio_BIN_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/bin")
set(sfml_sfml-audio_LIBRARY_TYPE_RELEASE SHARED)
set(sfml_sfml-audio_IS_HOST_WINDOWS_RELEASE 0)
set(sfml_sfml-audio_RES_DIRS_RELEASE )
set(sfml_sfml-audio_DEFINITIONS_RELEASE )
set(sfml_sfml-audio_OBJECTS_RELEASE )
set(sfml_sfml-audio_COMPILE_DEFINITIONS_RELEASE )
set(sfml_sfml-audio_COMPILE_OPTIONS_C_RELEASE "")
set(sfml_sfml-audio_COMPILE_OPTIONS_CXX_RELEASE "")
set(sfml_sfml-audio_LIBS_RELEASE sfml-audio)
set(sfml_sfml-audio_SYSTEM_LIBS_RELEASE )
set(sfml_sfml-audio_FRAMEWORK_DIRS_RELEASE )
set(sfml_sfml-audio_FRAMEWORKS_RELEASE )
set(sfml_sfml-audio_DEPENDENCIES_RELEASE sfml-system)
set(sfml_sfml-audio_SHARED_LINK_FLAGS_RELEASE )
set(sfml_sfml-audio_EXE_LINK_FLAGS_RELEASE )
set(sfml_sfml-audio_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(sfml_sfml-audio_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${sfml_sfml-audio_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${sfml_sfml-audio_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${sfml_sfml-audio_EXE_LINK_FLAGS_RELEASE}>
)
set(sfml_sfml-audio_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${sfml_sfml-audio_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${sfml_sfml-audio_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT sfml-network VARIABLES ############################################

set(sfml_sfml-network_INCLUDE_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/include")
set(sfml_sfml-network_LIB_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/lib")
set(sfml_sfml-network_BIN_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/bin")
set(sfml_sfml-network_LIBRARY_TYPE_RELEASE SHARED)
set(sfml_sfml-network_IS_HOST_WINDOWS_RELEASE 0)
set(sfml_sfml-network_RES_DIRS_RELEASE )
set(sfml_sfml-network_DEFINITIONS_RELEASE )
set(sfml_sfml-network_OBJECTS_RELEASE )
set(sfml_sfml-network_COMPILE_DEFINITIONS_RELEASE )
set(sfml_sfml-network_COMPILE_OPTIONS_C_RELEASE "")
set(sfml_sfml-network_COMPILE_OPTIONS_CXX_RELEASE "")
set(sfml_sfml-network_LIBS_RELEASE sfml-network)
set(sfml_sfml-network_SYSTEM_LIBS_RELEASE )
set(sfml_sfml-network_FRAMEWORK_DIRS_RELEASE )
set(sfml_sfml-network_FRAMEWORKS_RELEASE )
set(sfml_sfml-network_DEPENDENCIES_RELEASE sfml-system)
set(sfml_sfml-network_SHARED_LINK_FLAGS_RELEASE )
set(sfml_sfml-network_EXE_LINK_FLAGS_RELEASE )
set(sfml_sfml-network_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(sfml_sfml-network_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${sfml_sfml-network_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${sfml_sfml-network_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${sfml_sfml-network_EXE_LINK_FLAGS_RELEASE}>
)
set(sfml_sfml-network_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${sfml_sfml-network_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${sfml_sfml-network_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT sfml-graphics VARIABLES ############################################

set(sfml_sfml-graphics_INCLUDE_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/include")
set(sfml_sfml-graphics_LIB_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/lib")
set(sfml_sfml-graphics_BIN_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/bin")
set(sfml_sfml-graphics_LIBRARY_TYPE_RELEASE SHARED)
set(sfml_sfml-graphics_IS_HOST_WINDOWS_RELEASE 0)
set(sfml_sfml-graphics_RES_DIRS_RELEASE )
set(sfml_sfml-graphics_DEFINITIONS_RELEASE )
set(sfml_sfml-graphics_OBJECTS_RELEASE )
set(sfml_sfml-graphics_COMPILE_DEFINITIONS_RELEASE )
set(sfml_sfml-graphics_COMPILE_OPTIONS_C_RELEASE "")
set(sfml_sfml-graphics_COMPILE_OPTIONS_CXX_RELEASE "")
set(sfml_sfml-graphics_LIBS_RELEASE sfml-graphics)
set(sfml_sfml-graphics_SYSTEM_LIBS_RELEASE )
set(sfml_sfml-graphics_FRAMEWORK_DIRS_RELEASE )
set(sfml_sfml-graphics_FRAMEWORKS_RELEASE )
set(sfml_sfml-graphics_DEPENDENCIES_RELEASE sfml-window)
set(sfml_sfml-graphics_SHARED_LINK_FLAGS_RELEASE )
set(sfml_sfml-graphics_EXE_LINK_FLAGS_RELEASE )
set(sfml_sfml-graphics_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(sfml_sfml-graphics_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${sfml_sfml-graphics_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${sfml_sfml-graphics_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${sfml_sfml-graphics_EXE_LINK_FLAGS_RELEASE}>
)
set(sfml_sfml-graphics_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${sfml_sfml-graphics_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${sfml_sfml-graphics_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT sfml-window VARIABLES ############################################

set(sfml_sfml-window_INCLUDE_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/include")
set(sfml_sfml-window_LIB_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/lib")
set(sfml_sfml-window_BIN_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/bin")
set(sfml_sfml-window_LIBRARY_TYPE_RELEASE SHARED)
set(sfml_sfml-window_IS_HOST_WINDOWS_RELEASE 0)
set(sfml_sfml-window_RES_DIRS_RELEASE )
set(sfml_sfml-window_DEFINITIONS_RELEASE )
set(sfml_sfml-window_OBJECTS_RELEASE )
set(sfml_sfml-window_COMPILE_DEFINITIONS_RELEASE )
set(sfml_sfml-window_COMPILE_OPTIONS_C_RELEASE "")
set(sfml_sfml-window_COMPILE_OPTIONS_CXX_RELEASE "")
set(sfml_sfml-window_LIBS_RELEASE sfml-window)
set(sfml_sfml-window_SYSTEM_LIBS_RELEASE )
set(sfml_sfml-window_FRAMEWORK_DIRS_RELEASE )
set(sfml_sfml-window_FRAMEWORKS_RELEASE )
set(sfml_sfml-window_DEPENDENCIES_RELEASE sfml-system opengl::opengl xorg::xorg libudev::libudev)
set(sfml_sfml-window_SHARED_LINK_FLAGS_RELEASE )
set(sfml_sfml-window_EXE_LINK_FLAGS_RELEASE )
set(sfml_sfml-window_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(sfml_sfml-window_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${sfml_sfml-window_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${sfml_sfml-window_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${sfml_sfml-window_EXE_LINK_FLAGS_RELEASE}>
)
set(sfml_sfml-window_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${sfml_sfml-window_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${sfml_sfml-window_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT sfml-system VARIABLES ############################################

set(sfml_sfml-system_INCLUDE_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/include")
set(sfml_sfml-system_LIB_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/lib")
set(sfml_sfml-system_BIN_DIRS_RELEASE "${sfml_PACKAGE_FOLDER_RELEASE}/bin")
set(sfml_sfml-system_LIBRARY_TYPE_RELEASE SHARED)
set(sfml_sfml-system_IS_HOST_WINDOWS_RELEASE 0)
set(sfml_sfml-system_RES_DIRS_RELEASE )
set(sfml_sfml-system_DEFINITIONS_RELEASE )
set(sfml_sfml-system_OBJECTS_RELEASE )
set(sfml_sfml-system_COMPILE_DEFINITIONS_RELEASE )
set(sfml_sfml-system_COMPILE_OPTIONS_C_RELEASE "")
set(sfml_sfml-system_COMPILE_OPTIONS_CXX_RELEASE "")
set(sfml_sfml-system_LIBS_RELEASE sfml-system)
set(sfml_sfml-system_SYSTEM_LIBS_RELEASE pthread rt)
set(sfml_sfml-system_FRAMEWORK_DIRS_RELEASE )
set(sfml_sfml-system_FRAMEWORKS_RELEASE )
set(sfml_sfml-system_DEPENDENCIES_RELEASE )
set(sfml_sfml-system_SHARED_LINK_FLAGS_RELEASE )
set(sfml_sfml-system_EXE_LINK_FLAGS_RELEASE )
set(sfml_sfml-system_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(sfml_sfml-system_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${sfml_sfml-system_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${sfml_sfml-system_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${sfml_sfml-system_EXE_LINK_FLAGS_RELEASE}>
)
set(sfml_sfml-system_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${sfml_sfml-system_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${sfml_sfml-system_COMPILE_OPTIONS_C_RELEASE}>")
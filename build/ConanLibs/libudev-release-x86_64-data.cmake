########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(libudev_COMPONENT_NAMES "")
set(libudev_FIND_DEPENDENCY_NAMES "")

########### VARIABLES #######################################################################
#############################################################################################
set(libudev_PACKAGE_FOLDER_RELEASE "/home/maokoro/.conan2/p/b/libudde6eccd1b159c/p")
set(libudev_BUILD_MODULES_PATHS_RELEASE )


set(libudev_INCLUDE_DIRS_RELEASE )
set(libudev_RES_DIRS_RELEASE )
set(libudev_DEFINITIONS_RELEASE )
set(libudev_SHARED_LINK_FLAGS_RELEASE )
set(libudev_EXE_LINK_FLAGS_RELEASE )
set(libudev_OBJECTS_RELEASE )
set(libudev_COMPILE_DEFINITIONS_RELEASE )
set(libudev_COMPILE_OPTIONS_C_RELEASE )
set(libudev_COMPILE_OPTIONS_CXX_RELEASE )
set(libudev_LIB_DIRS_RELEASE )
set(libudev_BIN_DIRS_RELEASE "${libudev_PACKAGE_FOLDER_RELEASE}/bin")
set(libudev_LIBRARY_TYPE_RELEASE SHARED)
set(libudev_IS_HOST_WINDOWS_RELEASE 0)
set(libudev_LIBS_RELEASE )
set(libudev_SYSTEM_LIBS_RELEASE udev)
set(libudev_FRAMEWORK_DIRS_RELEASE )
set(libudev_FRAMEWORKS_RELEASE )
set(libudev_BUILD_DIRS_RELEASE )
set(libudev_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(libudev_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libudev_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libudev_COMPILE_OPTIONS_C_RELEASE}>")
set(libudev_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libudev_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libudev_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libudev_EXE_LINK_FLAGS_RELEASE}>")


set(libudev_COMPONENTS_RELEASE )
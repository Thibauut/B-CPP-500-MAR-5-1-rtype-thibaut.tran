#!/bin/sh

# Cleaning Cmake files & conan libs
cd build
rm -rf ./build/
rm -rf ./CMakeFiles/
rm -rf ./ConanLibs/
rm -rf ./cmake_install.cmake
rm -rf ./CMakeCache.txt
rm -rf .CMakeUserPresets.json
rm -rf ./Makefile

# Conan install & Cmake build
conan install .. --build=missing --output-folder=ConanLibs/
cmake -DCMAKE_TOOLCHAIN_FILE=build/ConanLibs/conan_toolchain.cmake -DCMAKE_PREFIX_PATH=/build/ -DCMAKE_BUILD_TYPE=Release ..
cd ..
make -C ./build/ CXX=g++-17
cd build
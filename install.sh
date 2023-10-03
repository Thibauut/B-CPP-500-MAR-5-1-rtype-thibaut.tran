#!/bin/sh

rm -rf ./build/
mkdir -p build
cd build
conan install .. --build=missing --output-folder=.
cmake -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_PREFIX_PATH=build/ -DCMAKE_BUILD_TYPE=Release ..
cd ..
make -C ./build/
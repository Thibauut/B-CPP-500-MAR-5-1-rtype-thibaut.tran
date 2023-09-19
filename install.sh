#!/bin/sh
cmake -S . -B ./build/ && make -C ./build/

# cmake -B . -S . -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake

# git submodule add https://github.com/SFML/SFML.git libs/SFML
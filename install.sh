#!/bin/sh
cmake -S . -B ./build/ && make -C ./build/

# git submodule add https://github.com/SFML/SFML.git libs/SFML
cmake_minimum_required(VERSION 3.25.2)

set(CLIENT r-type_client)
project(${CLIENT} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(libs/SFML)

set(SRC_CLIENT  client/main.cpp
)
set(HPP_CLIENT client/include/menu.hpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${CLIENT} ${SRC_CLIENT} ${HPP_CLIENT})

target_link_libraries(${CLIENT} sfml-graphics sfml-window sfml-system sfml-audio)

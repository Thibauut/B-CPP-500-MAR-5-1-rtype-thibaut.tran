cmake_minimum_required(VERSION 3.22.0)

set(CLIENT pong_client)
project(${CLIENT} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)

find_package(SFML COMPONENTS graphics window system audio network REQUIRED PATHS ${CMAKE_CURRENT_SOURCE_DIR}/build/ConanLibs/)
find_package(Boost REQUIRED COMPONENTS system thread log log_setup PATHS ${CMAKE_CURRENT_SOURCE_DIR}/build/ConanLibs/)
find_package(nlohmann_json REQUIRED PATHS ${CMAKE_CURRENT_SOURCE_DIR}/build/ConanLibs/)

# Client
set(SRC_CLIENT  client/client.cpp
                client/graphical/game.cpp
                ../../GameEngine/Components/test.cpp
                ../../client/network/ConnectionTCP/ConnectionTCP.cpp
                ../../client/network/ThreadHandler/ThreadHandler.cpp
)

add_executable(${CLIENT} ${SRC_CLIENT})

target_link_libraries(${CLIENT} sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(${CLIENT} Boost::system Boost::thread Boost::log Boost::log_setup)
target_link_libraries(${CLIENT} Boost::serialization)
target_link_libraries(${CLIENT} nlohmann_json::nlohmann_json)

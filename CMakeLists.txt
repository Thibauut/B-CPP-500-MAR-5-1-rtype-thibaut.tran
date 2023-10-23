cmake_minimum_required(VERSION 3.22.0)

set(CLIENT r-type_client)
set(SERVER r-type_server)
project(${CLIENT} LANGUAGES CXX)
project(${SERVER} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)

find_package(SFML COMPONENTS graphics window system audio network REQUIRED PATHS ${CMAKE_CURRENT_SOURCE_DIR}/build/ConanLibs/)
find_package(Boost REQUIRED COMPONENTS system thread log log_setup PATHS ${CMAKE_CURRENT_SOURCE_DIR}/build/ConanLibs/)
find_package(nlohmann_json REQUIRED PATHS ${CMAKE_CURRENT_SOURCE_DIR}/build/ConanLibs/)

# Server
set(SRC_SERVER  server/Elements/Map/Map.cpp
                server/LaunchServer.cpp
                server/Server.cpp
                server/Socket/TCP/TCPServer.cpp
                server/Socket/TCP/TCPConnexion.cpp
                server/Socket/TCP/HandleRequest/Parser.cpp
                server/Socket/UDP/UDPServer.cpp
                server/Room/RoomLobby.cpp
                server/Elements/Player/PlayerLobby.cpp
                server/Save/HandleSave.cpp
                GameEngine/Components/test.cpp
)

set(HPP_SERVER server/Includes.hpp
)

# Client
set(SRC_CLIENT  client/main.cpp
                client/network/ThreadHandler/ThreadHandler.cpp
                GameEngine/Components/test.cpp
)

set(HPP_CLIENT client/include/menu.hpp
                client/network/ConnectionTCP/ConnectionTCP.hpp
                client/network/ThreadHandler/ThreadHandler.hpp
)

add_executable(${SERVER} ${SRC_SERVER} ${HPP_SERVER})
add_executable(${CLIENT} ${SRC_CLIENT} ${HPP_CLIENT})

target_link_libraries(${SERVER} sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(${SERVER} Boost::system Boost::thread Boost::log Boost::log_setup)
target_link_libraries(${SERVER} Boost::serialization)
target_link_libraries(${SERVER} nlohmann_json::nlohmann_json)


target_link_libraries(${CLIENT} sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(${CLIENT} Boost::system Boost::thread Boost::log Boost::log_setup)
target_link_libraries(${CLIENT} Boost::serialization)
target_link_libraries(${CLIENT} nlohmann_json::nlohmann_json)

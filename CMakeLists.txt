cmake_minimum_required(VERSION 3.0.0)

set(CLIENT r-type_client)
set(SERVER r-type_server)
project(${CLIENT} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(libs/SFML)
find_package(Boost REQUIRED COMPONENTS system thread log log_setup)
add_subdirectory(libs/boost)
add_subdirectory(libs/json)

# Client
set(SRC_CLIENT  client/main.cpp
                client/network/ConnectionTCP/ConnectionTCP.cpp
                client/network/ThreadHandler/ThreadHandler.cpp

)

set(HPP_CLIENT client/include/menu.hpp
                client/network/ConnectionTCP/ConnectionTCP.hpp
                client/network/ThreadHandler/ThreadHandler.hpp
)


# Server
set(SRC_SERVER  server/LaunchServer.cpp
                server/Server.cpp
                server/Socket/TCP/TCPServer.cpp
                server/Socket/TCP/TCPConnexion.cpp
                server/Socket/TCP/HandleRequest/Parser.cpp
                server/Socket/UDP/UDPServer.cpp
                server/Room/RoomLobby.cpp
                server/Elements/Player/PlayerLobby.cpp
                server/Save/HandleSave.cpp
)

set(HPP_SERVER  server/Server.hpp
                server/Socket/TCP/TCPServer.hpp
                server/Socket/TCP/TCPConnexion.hpp
                server/Socket/TCP/HandleRequest/Parser.hpp
                server/Socket/UDP/UDPServer.hpp
                server/Room/RoomLobby.hpp
                server/Elements/Player/PlayerLobby.hpp
                server/Save/HandleSave.hpp
)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${CLIENT} ${SRC_CLIENT} ${HPP_CLIENT})


add_executable(${SERVER} ${SRC_SERVER} ${HPP_SERVER})

target_link_libraries(${CLIENT} sfml-graphics sfml-window sfml-system sfml-audio sfml-network Boost::system Boost::thread Boost::log Boost::log_setup Threads::Threads)

target_link_libraries(${SERVER} PRIVATE Boost::system Boost::thread Boost::log Boost::log_setup nlohmann_json::nlohmann_json Threads::Threads)

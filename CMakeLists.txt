cmake_minimum_required(VERSION 3.0.0)

set(CLIENT r-type_client)
set(SERVER r-type_server)

project(${CLIENT} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})



add_subdirectory(libs/SFML)

add_subdirectory(libs/boost)
set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR})


#-------------------------- CLIENT
set(SRC_CLIENT  client/main.cpp
)
set(HPP_CLIENT client/include/menu.hpp
)
#--------------------------

#-------------------------- SERVER
set(SRC_SERVER  server/LaunchServer.cpp
server/Server.cpp
server/Socket/TCP/TCPServer.cpp
server/Socket/TCP/TCPConnexion.cpp
server/Room/RoomLobby.cpp
server/Elements/Player/PlayerLobby.cpp
)

set(HPP_SERVER  server/Server.hpp
server/Socket/TCP/TCPServer.hpp
server/Socket/TCP/TCPConnexion.hpp
server/Room/RoomLobby.hpp
server/Elements/Player/PlayerLobby.hpp
)

#--------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${CLIENT} ${SRC_CLIENT} ${HPP_CLIENT})
# add_executable(${SERVER} ${SRC_SERVER} ${HPP_SERVER})
# find_package(Boost REQUIRED COMPONENTS system)
# target_link_libraries(${SERVER} PRIVATE Boost::Asio)

target_link_libraries(${CLIENT} sfml-graphics sfml-window sfml-system sfml-audio)
# target_link_libraries(${CLIENT} PRIVATE Boost::Asio)




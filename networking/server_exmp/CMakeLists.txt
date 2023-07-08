cmake_minimum_required(VERSION 3.4)
project(exmaple-chat)

set(CMAKE_CXX_STANDARD 11)

add_executable(server server.cpp src/net.cpp)
add_executable(client client.cpp src/net.cpp)


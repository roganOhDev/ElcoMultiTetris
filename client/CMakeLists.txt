cmake_minimum_required(VERSION 3.24)
project(client)

set(CMAKE_CXX_STANDARD 17)

add_executable(client main.cpp socket/socketClient.cpp socket/socketClient.h)

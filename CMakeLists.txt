cmake_minimum_required(VERSION 3.29)
project(backend)

set(CMAKE_CXX_STANDARD 26)

include_directories(headers include)

add_executable(backend src/main.cpp
        src/TCPSocket.cpp
        headers/TCPSocket.h
        src/UDPSocket.cpp
        headers/UDPSocket.h
        src/FileManager.cpp
        headers/FileManager.h
        headers/EFTP.h
)

target_link_libraries(backend ws2_32.lib)
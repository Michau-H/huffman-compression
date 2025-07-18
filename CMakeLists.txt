cmake_minimum_required(VERSION 3.26)
project(huffman)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(huffman src/main.cpp
        src/Tree.cpp
        src/Node.cpp
        src/Symbol.cpp
        src/FileReader.cpp
        src/Alfabet.cpp
        src/BitWriter.cpp
        src/BitReader.cpp)